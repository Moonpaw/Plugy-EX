/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Updating server.

=================================================================*/

#include "updateServer.h"
#include "updateClient.h"
#include "infinityStash.h"
#include "newInterfaces.h"
#include "newInterface_CubeListing.h"
#include "extraOptions.h"
#include "windowed.h"
#include "common.h"
#include "savePlayerData.h"
#include <stdio.h>
#include "d2functions.h"
#include <d2constants.h>
#include <updatingConst.h>
#include "modifMemory.h"
#include "error.h"
#include "globalVariable.h"

namespace PlugY {
    bool active_Commands = true;
    bool active_listAllCubeFormula = true;
    bool active_savegame = false;
#define MAX_CMD_SIZE 200
    const char *CMD_PLAYERS = "players set to";
    const char *CMD_SAVE = "/save";
    const char *CMD_SELECTPAGE = "/page";
    const char *CMD_LOCK_MOUSE = "/lockmouse";
    const char *CMD_LOCK_MOUSE2 = "/lock";
    const char *CMD_UNLOCK_MOUSE = "/unlockmouse";
    const char *CMD_UNLOCK_MOUSE2 = "/unlock";
    const char *CMD_RENAME_CHAR = "/renamechar";
    const char *CMD_RENAME_PAGE = "/renamepage";
    const char *CMD_SHORT_RENAME_PAGE = "/rp";
    const char *CMD_SET_INDEX = "/setindex";
    const char *CMD_SET_MAIN_INDEX = "/setmainindex";
    const char *CMD_RESET_INDEX = "/resetindex";
    const char *CMD_INSERT_PAGE = "/insertpage";
    const char *CMD_SHORT_INSERT_PAGE = "/ip";
    const char *CMD_DELETE_PAGE = "/deletepage";
    const char *CMD_SHORT_DELETE_PAGE = "/dp";
    const char *CMD_SWAP_PAGE = "/swappage";
    const char *CMD_SHORT_SWAP_PAGE = "/sp";
    const char *CMD_TOGGLE_PAGE = "/togglepage";
    const char *CMD_SHORT_TOGGLE_PAGE = "/tp";
    const char *CMD_DISPLAY_MANA_LIFE = "/dml";
    const char *CMD_DISPLAY_LIFE_MANA = "/dlm";
    const char *CMD_DISPLAY_LIFE = "/dl";
    const char *CMD_DISPLAY_MANA = "/dm";
    const char *CMD_LISTCUBEFORMULA = "/listcube";

    void savePlayers(Commons::Unit *ptChar) {
        if (active_savegame)
            D2SaveGame(PCGame);
    }

    void maxGold(Commons::Unit *ptChar) {
        log_msg("maxGold\n");
        DWORD maxGold = D2GetMaxGold(ptChar);
        DWORD maxGoldBank = D2GetMaxGoldBank(ptChar);
        DWORD playerGold = D2GetPlayerStat(ptChar, STATS_GOLD, 0);
        DWORD playerGoldBank = D2GetPlayerStat(ptChar, STATS_GOLDBANK, 0);
        if ((playerGold < maxGold) || (playerGoldBank < maxGoldBank)) {
            D2AddPlayerStat(ptChar, STATS_GOLD, maxGold - playerGold, 0);
            D2AddPlayerStat(ptChar, STATS_GOLDBANK, maxGoldBank - playerGoldBank, 0);
        } else {
            D2AddPlayerStat(ptChar, STATS_GOLD, 100000, 0);
        }
        if (active_sharedGold) {
            PCPY->sharedGold = 0xFFFFFFFF;
            updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
        }
    }

    void putGold(Commons::Unit *ptChar, DWORD amount) {
        if (!active_sharedGold) return;
        log_msg("putGold : %d\n", amount);
        DWORD playerGold = D2GetPlayerStat(ptChar, STATS_GOLD, 0);
        DWORD toAdd = 0xFFFFFFFF - PCPY->sharedGold;
        if (playerGold < toAdd)
            toAdd = playerGold;
        if (amount && (toAdd > amount))
            toAdd = amount;
        D2AddPlayerStat(ptChar, STATS_GOLD, 0 - toAdd, 0);
        PCPY->sharedGold += toAdd;
        updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
    }

    void takeGold(Commons::Unit *ptChar, DWORD amount) {
        if (!active_sharedGold) return;
        log_msg("takeGold : %d\n", amount);
        DWORD maxGold = D2GetMaxGold(ptChar) - D2GetPlayerStat(ptChar, STATS_GOLD, 0);
//	DWORD maxGoldBank = D2GetMaxGoldBank(ptChar) - D2GetPlayerStat(ptChar, STATS_GOLDBANK, 0);
        DWORD toAdd = maxGold < PCPY->sharedGold ? maxGold : PCPY->sharedGold;
        if (amount && (toAdd > amount))
            toAdd = amount;
        D2AddPlayerStat(ptChar, STATS_GOLD, toAdd, 0);
        PCPY->sharedGold -= toAdd;
        updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
    }

    void updateSharedGold(DWORD goldAmount) {
        Unit *ptChar = D2GetClientPlayer();
        log_msg("SharedGold = %d\n", goldAmount);
        PCPY->sharedGold = goldAmount;
    }

    bool renamePage(Commons::Unit *ptChar, char *newName) {
        Stash *ptStash = PCPY->currentStash;
        if (!ptStash)
            return 0;
        log_msg("Rename current page on Client : '%s' -> '%s'\n", ptStash->name, newName);
        int len = strlen(newName);
        // trim text
        while (newName[0] == ' ') {
            newName++;
            len--;
        }
        while (len > 0 && newName[len - 1] == ' ') {
            newName[len - 1] = NULL;
            len--;
        }
        // Fix max length
        if (len > 20) {
            newName[20] = NULL;
            len = 20;
        }

        // Check if new name is default name
        char defautText[50];
        wcstombs(defautText, getDefaultStashName(ptChar), 50);
        if (!strcmp(newName, defautText)) {
            newName[0] = NULL;
            len = 0;
        }

        // Check if the name change
        if (newName[0] == NULL && (ptStash->name == NULL || ptStash->name[0] == NULL))
            return 0;
        if (ptStash->name && !strcmp(newName, ptStash->name))
            return 0;

        // Rename the page
        log_msg("Rename current page valid : '%s' (%s)\n", newName, defautText);
        renameCurrentStash(ptChar, newName);
        for (int i = 0; i <= len; i++)
            updateServer(US_PAGENAME + (newName[i] << 8));
        return 0;
    }

    bool renameCharacter(Commons::Unit *ptChar, char *newName) {
        int len = strlen(newName);
        if (len < 2 || len > 15)
            return 0;
        for (int i = 0; i < len; i++) {
            char c = newName[i];
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')))
                return 1;
        }
        log_msg("Rename Character : %s -> %s\n", PCPlayerData->name, newName);

        // Move current save file
        backupSaveFiles(PCPlayerData->name, -1);
        {
            char szCurrentFile[MAX_PATH];
            char szNewFile[MAX_PATH];

            //Get temporary savefile name.
            D2FogGetSavePath(szCurrentFile, MAX_PATH);
            D2FogGetSavePath(szNewFile, MAX_PATH);
            strcat(szCurrentFile, PCPlayerData->name);
            strcat(szNewFile, newName);
            strcat(szCurrentFile, ".");
            strcat(szNewFile, ".");
            int curLen = strlen(szCurrentFile);
            int newLen = strlen(szNewFile);
            strcpy(&szCurrentFile[curLen], "d2s");
            strcpy(&szNewFile[newLen], "d2s");
            if (!MoveFile(szCurrentFile, szNewFile))
                return 0;
            strcpy(&szCurrentFile[curLen], "d2x");
            strcpy(&szNewFile[newLen], "d2x");
            MoveFile(szCurrentFile, szNewFile);
            strcpy(&szCurrentFile[curLen], "key");
            strcpy(&szNewFile[newLen], "key");
            MoveFile(szCurrentFile, szNewFile);
            strcpy(&szCurrentFile[curLen], "ma0");
            strcpy(&szNewFile[newLen], "ma0");
            MoveFile(szCurrentFile, szNewFile);
            strcpy(&szCurrentFile[curLen], "ma1");
            strcpy(&szNewFile[newLen], "ma1");
            MoveFile(szCurrentFile, szNewFile);
            strcpy(&szCurrentFile[curLen], "ma2");
            strcpy(&szNewFile[newLen], "ma2");
            MoveFile(szCurrentFile, szNewFile);
            strcpy(&szCurrentFile[curLen], "ma3");
            strcpy(&szNewFile[newLen], "ma3");
            MoveFile(szCurrentFile, szNewFile);
            strcpy(&szCurrentFile[curLen], "ma4");
            strcpy(&szNewFile[newLen], "ma4");
            MoveFile(szCurrentFile, szNewFile);
            strcpy(&szCurrentFile[curLen], "map");
            strcpy(&szNewFile[newLen], "map");
            MoveFile(szCurrentFile, szNewFile);
        }

        // Update server
        for (int i = 0; i <= len; i++)
            updateServer(US_RENAME + (newName[i] << 8));

        // Update client
        log_msg("Rename on Client : %s -> %s\n", PCPlayerData->name, newName);
        strcpy(PCPlayerData->name, newName);
        updateServer(US_SAVE);
        return 0;
    }

/****************************************************************************************************/

    int STDCALL commands(char *ptText) {
        log_msg("Command : %s\n", ptText);
        Unit *ptChar = D2GetClientPlayer();
        char command[MAX_CMD_SIZE];
        ZeroMemory(command, MAX_CMD_SIZE);
        strncpy(command, ptText, MAX_CMD_SIZE - 1);
        _strlwr(command);
        if (!strncmp(command, CMD_PLAYERS, strlen(CMD_PLAYERS))) {
            int nb = atoi(&command[strlen(CMD_PLAYERS)]);
            if (nb > 0 && nb <= 64)
                nbPlayersCommand = nb;
            return 1;
        }
        if (!strcmp(command, CMD_SAVE)) {
            if (onRealm) return 1;
            updateServer(US_SAVE);
            return 0;
        }
        if (!strncmp(command, CMD_SELECTPAGE, strlen(CMD_SELECTPAGE))) {
            if (!active_newInterfaces) return 1;
            GoStatPage(atoi(&command[strlen(CMD_SELECTPAGE)]) - 1);
            return 0;
        }
        if (!strcmp(command, CMD_LOCK_MOUSE) || !strcmp(command, CMD_LOCK_MOUSE2)) {
            if (onRealm) return 1;
            lockMouseCursor();
            return 0;
        }
        if (!strcmp(command, CMD_UNLOCK_MOUSE) || !strcmp(command, CMD_UNLOCK_MOUSE2)) {
            if (onRealm) return 1;
            unlockMouseCursor();
            return 0;
        }
        if (!strncmp(command, CMD_RENAME_CHAR, strlen(CMD_RENAME_CHAR))) {
            char *param = &ptText[strlen(CMD_RENAME_CHAR)];
            if (param[0] != ' ')
                return 1;
            param++;
            return renameCharacter(ptChar, param);
        }
        if (!strncmp(command, CMD_RENAME_PAGE, strlen(CMD_RENAME_PAGE))) {
            if (!active_multiPageStash) return 1;
            char *param = &ptText[strlen(CMD_RENAME_PAGE)];
            return renamePage(ptChar, param);
        }
        if (!strncmp(command, CMD_SHORT_RENAME_PAGE, strlen(CMD_SHORT_RENAME_PAGE))) {
            if (!active_multiPageStash) return 1;
            char *param = &ptText[strlen(CMD_SHORT_RENAME_PAGE)];
            return renamePage(ptChar, param);
        }
        if (!strcmp(command, CMD_SET_INDEX)) {
            if (!active_multiPageStash) return 1;
            updateServer(US_SET_INDEX);
            return 0;
        }
        if (!strcmp(command, CMD_SET_MAIN_INDEX)) {
            if (!active_multiPageStash) return 1;
            updateServer(US_SET_MAIN_INDEX);
            return 0;
        }
        if (!strcmp(command, CMD_RESET_INDEX)) {
            if (!active_multiPageStash) return 1;
            updateServer(US_RESET_INDEX);
            return 0;
        }
        if (!strcmp(command, CMD_INSERT_PAGE)) {
            if (!active_multiPageStash) return 1;
            insertStash(ptChar);
            updateServer(US_INSERT_PAGE);
            return 0;
        }
        if (!strcmp(command, CMD_SHORT_INSERT_PAGE)) {
            if (!active_multiPageStash) return 1;
            insertStash(ptChar);
            updateServer(US_INSERT_PAGE);
            return 0;
        }
        if (!strcmp(command, CMD_DELETE_PAGE)) {
            if (!active_multiPageStash) return 1;
            if (deleteStash(ptChar, true))
                updateServer(US_DELETE_PAGE);
            return 0;
        }
        if (!strcmp(command, CMD_SHORT_DELETE_PAGE)) {
            if (!active_multiPageStash) return 1;
            if (deleteStash(ptChar, true))
                updateServer(US_DELETE_PAGE);
            return 0;
        }
        if (!strncmp(command, CMD_SWAP_PAGE, strlen(CMD_SWAP_PAGE))) {
            if (!active_multiPageStash) return 1;
            int page = atoi(&command[strlen(CMD_SWAP_PAGE)]) - 1;
            if (page < 0 && PCPY->currentStash->nextStash)
                page = PCPY->currentStash->nextStash->id;
            if (page < 0)
                return 1;
            updateServer(US_SWAP3 + ((page & 0xFF000000) >> 16));
            updateServer(US_SWAP2 + ((page & 0xFF0000) >> 8));
            updateServer(US_SWAP1 + (page & 0xFF00));
            updateServer(US_SWAP0 + ((page & 0xFF) << 8));
            return 0;
        }
        if (!strncmp(command, CMD_SHORT_SWAP_PAGE, strlen(CMD_SHORT_SWAP_PAGE))) {
            if (!active_multiPageStash) return 1;
            int page = atoi(&command[strlen(CMD_SHORT_SWAP_PAGE)]) - 1;
            if (page < 0 && PCPY->currentStash->nextStash)
                page = PCPY->currentStash->nextStash->id;
            if (page < 0)
                return 1;
            updateServer(US_SWAP3 + ((page & 0xFF000000) >> 16));
            updateServer(US_SWAP2 + ((page & 0xFF0000) >> 8));
            updateServer(US_SWAP1 + (page & 0xFF00));
            updateServer(US_SWAP0 + ((page & 0xFF) << 8));
            return 0;
        }
        if (!strncmp(command, CMD_TOGGLE_PAGE, strlen(CMD_TOGGLE_PAGE))) {
            if (!active_sharedStash) return 1;
            int page = atoi(&command[strlen(CMD_TOGGLE_PAGE)]) - 1;
            if (page < 0)
                return 1;
            updateServer(US_SWAP3 + ((page & 0xFF000000) >> 16));
            updateServer(US_SWAP2 + ((page & 0xFF0000) >> 8));
            updateServer(US_SWAP1 + (page & 0xFF00));
            updateServer(US_SWAP0_TOGGLE + ((page & 0xFF) << 8));
            return 0;
        }
        if (!strncmp(command, CMD_SHORT_TOGGLE_PAGE, strlen(CMD_SHORT_TOGGLE_PAGE))) {
            if (!active_sharedStash) return 1;
            int page = atoi(&command[strlen(CMD_SHORT_TOGGLE_PAGE)]) - 1;
            if (page < 0)
                return 1;
            updateServer(US_SWAP3 + ((page & 0xFF000000) >> 16));
            updateServer(US_SWAP2 + ((page & 0xFF0000) >> 8));
            updateServer(US_SWAP1 + (page & 0xFF00));
            updateServer(US_SWAP0_TOGGLE + ((page & 0xFF) << 8));
            return 0;
        }
        if (!strcmp(command, CMD_DISPLAY_LIFE)) {
            active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
            return 0;
        }
        if (!strcmp(command, CMD_DISPLAY_MANA)) {
            active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
            return 0;
        }
        if (!strcmp(command, CMD_DISPLAY_LIFE_MANA) || !strcmp(command, CMD_DISPLAY_MANA_LIFE)) {
            active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
            return 0;
        }
        if (!strcmp(command, CMD_LISTCUBEFORMULA)) {
            if (!active_listAllCubeFormula) return 1;
            listAllCubeFormula();
            return 0;
        }

        //if (!strcmp(command,CMD_RELOAD))
        //{
        //	if (onRealm) return 1;
        //	gambleReload(ptChar);
        //	return 0;
        //}

        //if (!strcmp(command,CMD_MAXGOLD))
        //{
        //	if (onRealm) return 1;
        //	updateServer(US_MAXGOLD);
        //	return 0;
        //}

        //if (!strcmp(command,"t"))
        //{
        //	//test();
        //	FILE* file = fopen("D:\\tmp.txt", "wb+");
        //	for (int i = 0; i<= 0xFFFF; i++)
        //	{
        //		fwprintf( file, L"== %04X ===================================\n%s\n", i, D2GetStringFromIndex(i) );
        //	}
        //	fclose(file);
        //	return 0;
        //}

        if (!strcmp(command, "aa")) {
#pragma pack(1)
            struct {
                BYTE displayType;//0x15 main msg;  0x14: char popup
                BYTE un;
                BYTE zero;
                char string[0xFF];
                char null;
                char u1[0x100];
                char u2[0x100];
                char u3[0x100];
            } data;
#pragma pack()

            //D2SetNbPlayers(nbPlayersCommand);

            memset(&data, 0, sizeof(data));
            data.displayType = 0x15;
            data.un = 1;
            data.zero = 0;//*(BYTE*)(offset_D2Client+0x112CFC); in 1.10
            data.null = NULL;
            sprintf(data.string, "players %u", nbPlayersCommand);
            D2SendMsgToAll((BYTE *) &data);
            return 0;
        }
        return 1;
    }

    __declspec(naked)void caller_Commands() {
        __asm{
        TEST EAX, EAX
        JE MANAGESOUNDCHAOSDEBUG
        PUSH DWORD PTR SS:[ESP+0x1C]
        CALL commands
        TEST EAX, EAX
        JNZ MANAGESOUNDCHAOSDEBUG
        ADD DWORD PTR SS:[ESP], 7
        MANAGESOUNDCHAOSDEBUG:
        RETN 8
        }
    }

    __declspec(naked)void caller_Commands_111() {
        __asm{
        TEST EAX, EAX
        JE MANAGESOUNDCHAOSDEBUG
        PUSH ESI
        CALL commands
        TEST EAX, EAX
        JNZ MANAGESOUNDCHAOSDEBUG
        ADD DWORD PTR SS:[ESP], 7
        MANAGESOUNDCHAOSDEBUG:
        RETN 8
        }
    }

    __declspec(naked)void caller_Commands_113d() {
        __asm{
        TEST EAX, EAX
        JE MANAGESOUNDCHAOSDEBUG
        PUSH EDI
        CALL commands
        TEST EAX, EAX
        JNZ MANAGESOUNDCHAOSDEBUG
        ADD DWORD PTR SS:[ESP], 7
        MANAGESOUNDCHAOSDEBUG:
        RETN 8
        }
    }

    void Install_Commands() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_UpdateServer();
        log_msg("Patch D2Client for install commands. (Commands)\n");
        active_listAllCubeFormula = version_D2Common >= V110;
        active_savegame = version_D2Common >= V111;

        // Run custom commmand
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x7C548 : (version_D2Client == V113d ? 0xB1FD6 : (version_D2Client == V113c ? 0x70AE6 : (version_D2Client == V112 ? 0x86926 : (version_D2Client == V111b ? 0x91C16 : (version_D2Client == V111 ? 0xC1EE6 : (version_D2Client == V110 ? 0x32BDD : (version_D2Client == V109d ? 0x2C110 : 0x2C120)))))))));
        memt_byte(0x83, 0xE8);    // CALL
        MEMT_REF4(0xC08508C4, version_D2Client >= V113d ? caller_Commands_113d : version_D2Client >= V111 ? caller_Commands_111 : caller_Commands);
        //6FB71EE6   . 83C4 08        ADD ESP,8
        //6FB71EE7   . 85C0           TEST EAX,EAX
        //6FB41C16  |. 83C4 08        ADD ESP,8
        //6FB41C19  |. 85C0           TEST EAX,EAX
        //6FB36926  |. 83C4 08        ADD ESP,8
        //6FB36929  |. 85C0           TEST EAX,EAX
        //6FB20AE6  |. 83C4 08        ADD ESP,8
        //6FB20AE9  |. 85C0           TEST EAX,EAX
        //6FB20AE6  |. 83C4 08        ADD ESP,8
        //6FB20AE9  |. 85C0           TEST EAX,EAX
        //6FB61FD6  |. 83C4 08        ADD ESP,8
        //6FB61FD9  |. 85C0           TEST EAX,EAX
        //0047C548  |. 83C4 08        ADD ESP,8
        //0047C54B  |. 85C0           TEST EAX,EAX

        log_msg("\n");
        isInstalled = true;
    }
}
