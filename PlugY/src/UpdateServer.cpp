/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Updating server.

=================================================================*/

#include "updateServer.h"
#include "statsPoints.h"
#include "skillsPoints.h"
#include "infinityStash.h"
#include "commands.h"
#include "common.h"
#include "d2functions.h"
#include "globalVariable.h"
#include <updatingConst.h>
#include "error.h"
#include "modifMemory.h"

namespace PlugY {
    void updateServer(WORD p) {
        if (!onRealm)
            D2SendToServer3(0x3A, p);
    }

    int renameIndex = 0;
    char renameString[21];
    DWORD PageSwap;

    int __stdcall handleServerUpdate(Commons::Unit *ptChar, WORD param) {
        int type = param & 0xFF;
        DWORD arg = (param & 0xFF00) >> 8;
        log_msg("Received custom message: type=%i, arg=%i\n", type, arg);
        switch (type) {
            case US_UNASSIGN_STR_POINT :
                UnassignStrPoint(ptChar);
                return 1;
            case US_UNASSIGN_ENE_POINT :
                UnassignEnePoint(ptChar);
                return 1;
            case US_UNASSIGN_DEX_POINT :
                UnassignDexPoint(ptChar);
                return 1;
            case US_UNASSIGN_VIT_POINT :
                UnassignVitPoint(ptChar);
                return 1;
            case US_UNASSIGN_STR_POINTS :
                UnassignStrPoints(ptChar);
                return 1;
            case US_UNASSIGN_ENE_POINTS :
                UnassignEnePoints(ptChar);
                return 1;
            case US_UNASSIGN_DEX_POINTS :
                UnassignDexPoints(ptChar);
                return 1;
            case US_UNASSIGN_VIT_POINTS :
                UnassignVitPoints(ptChar);
                return 1;
            case US_UNASSIGN_SKILLS :
                UnassignAllSkillsPoints(ptChar);
                return 1;
            case US_SET_INDEX:
                setCurrentStashIndex(ptChar, 1);
                return 1;
            case US_SET_MAIN_INDEX:
                setCurrentStashIndex(ptChar, 2);
                return 1;
            case US_RESET_INDEX:
                setCurrentStashIndex(ptChar, 0);
                return 1;
            case US_SELECT_PREVIOUS :
                selectPreviousStash(ptChar);
                return 1;
            case US_SELECT_NEXT :
                selectNextStash(ptChar);
                return 1;
            case US_SELECT_SELF :
                if (active_sharedStash) toggleToSelfStash(ptChar);
                return 1;
            case US_SELECT_SHARED :
                if (active_sharedStash) toggleToSharedStash(ptChar);
                return 1;
            case US_SELECT_PREVIOUS_INDEX :
                selectPreviousIndexStash(ptChar);
                return 1;
            case US_SELECT_NEXT_INDEX :
                selectNextIndexStash(ptChar);
                return 1;
            case US_SELECT_PREVIOUS2 :
                selectPrevious2Stash(ptChar);
                return 1;
            case US_SELECT_NEXT2 :
                selectNext2Stash(ptChar);
                return 1;
            case US_SELECT_PREVIOUS_INDEX2:
                selectPreviousIndex2Stash(ptChar);
                return 1;
            case US_SELECT_NEXT_INDEX2 :
                selectNextIndex2Stash(ptChar);
                return 1;
            case US_INSERT_PAGE:
                insertStash(ptChar);
                selectNextStash(ptChar);
                return 1;
            case US_DELETE_PAGE:
                deleteStash(ptChar, false);
                return 1;
            case US_SAVE :
                savePlayers(ptChar);
                return 1;
            case US_MAXGOLD :
                maxGold(ptChar);
                return 1;
            case US_PUTGOLD :
                putGold(ptChar, 0);
                return 1;
            case US_TAKEGOLD :
                takeGold(ptChar, 0);
                return 1;
            case US_SWAP3 :
                PageSwap = arg << 24;
                return 1;
            case US_SWAP2 :
                PageSwap |= arg << 16;
                return 1;
            case US_SWAP1 :
                PageSwap |= arg << 8;
                return 1;
            case US_SWAP0:
                swapStash(ptChar, PageSwap | arg, false);
                PageSwap = 0;
                return 1;
            case US_SWAP0_TOGGLE :
                swapStash(ptChar, PageSwap | arg, true);
                PageSwap = 0;
                return 1;
            case US_RENAME :
                if (renameIndex == 0)
                    ZeroMemory (renameString, sizeof(renameString));
                if (arg != NULL && renameIndex < 15)
                    renameString[renameIndex++] = (char) arg;
                if (arg == NULL) {
                    renameString[renameIndex] = NULL;
                    renameIndex = 0;
                    log_msg("Rename on Server : %s -> %s\n", getPlayerData(ptChar)->name, renameString);
                    strcpy(getPlayerData(ptChar)->name, renameString);
                    strcpy(getPlayerData(ptChar)->ptNetClient->name, renameString);
                }
                return 1;
            case US_PAGENAME:
                if (renameIndex == 0)
                    ZeroMemory (renameString, sizeof(renameString));
                if (arg != NULL && renameIndex < 20)
                    renameString[renameIndex++] = (char) arg;
                if (arg == NULL) {
                    renameString[renameIndex] = NULL;
                    renameIndex = 0;
                    log_msg("Rename current page on Server : %s -> %s\n", getPYPlayerData(ptChar)->currentStash->name, renameString);
                    renameCurrentStash(ptChar, renameString);
                }
                return 1;
            default :
                return 0;
        }
    }

    __declspec(naked)void caller_handleServerUpdate_114() {
        __asm{
        PUSH ESI
        PUSH EBX
        CALL handleServerUpdate
        TEST EAX, EAX
        JNZ END_RCM
        MOV EAX, ESI
        AND EAX, 0xFF
        SHR ESI, 8
        MOV EDI, EAX
        RETN
        END_RCM:
        ADD ESP, 8
        POP EDI
        POP ESI
        XOR EAX, EAX
        POP EBX
        RETN 8
        }
    }

    __declspec(naked)void caller_handleServerUpdate() {
        __asm{
        PUSH ESI
        PUSH EBX
        CALL handleServerUpdate
        TEST EAX, EAX
        JNZ END_RCM
        MOV EAX, ESI
        AND EAX, 0xFF
        SHR ESI, 8
        MOV EDI, EAX
        RETN
        END_RCM:
        ADD ESP, 4
        POP EDI
        POP ESI
        XOR EAX, EAX
        POP EBX
        RETN 8
        }
    }

    __declspec(naked)void caller_handleServerUpdate_9() {
        __asm{
        XOR EDX, EDX
        MOV DX, WORD PTR DS:[EAX+1]
        PUSH ECX
        PUSH EDX
        PUSH EDX
        PUSH ECX
        CALL handleServerUpdate
        POP EDX
        POP ECX
        TEST EAX, EAX
        JNZ END_RCM
        RETN
        END_RCM:
        POP EAX
        XOR EAX, EAX
        RETN 8
        }
    }

    void Install_UpdateServer() {
        static int isInstalled = false;
        if (isInstalled) return;
        log_msg("Patch D2Game for received button click message. (UpdateServer)\n");

        // manage button click message from Client.
        mem_seek(offset_D2Game + (version_D2Game == V114d ? 0x14BD38 : (version_D2Game == V113d ? 0x676C3 : (version_D2Game == V113c ? 0xCC983 : (version_D2Game == V112 ? 0x975C3 : (version_D2Game == V111b ? 0x2C773 : (version_D2Game == V111 ? 0x54AE3 : (version_D2Game == V110 ? 0x56EA2 : (version_D2Game == V109d ? 0x4AAC2 : 0x4A702)))))))));
        if (version_D2Game >= V111) {
            memt_byte(0xC1, 0x57);    // PUSH EDI
            memt_byte(0xEE, 0xE8);    // CALL caller_handleServerUpdate
            MEMT_REF4(0xF88B5708, version_D2Game == V114d ? caller_handleServerUpdate_114 : caller_handleServerUpdate);
            //01FD4AE3   . C1EE 08        SHR ESI,8
            //01FD4AE6   . 57             PUSH EDI
            //01FD4AE7   . 8BF8           MOV EDI,EAX
            //01F9C773   . C1EE 08        SHR ESI,8
            //01F9C776   . 57             PUSH EDI
            //01F9C777   . 8BF8           MOV EDI,EAX
            //6FCB75C3   . C1EE 08        SHR ESI,8
            //6FCB75C6   . 57             PUSH EDI
            //6FCB75C7   . 8BF8           MOV EDI,EAX
            //6FCEC983   . C1EE 08        SHR ESI,8
            //6FCEC986   . 57             PUSH EDI
            //6FCEC987   . 8BF8           MOV EDI,EAX
            //066A76C3  |.  C1EE 08       SHR ESI,8
            //066A76C6  |.  57            PUSH EDI
            //066A76C7  |.  8BF8          MOV EDI,EAX
            //0054BD38  |. C1EE 08        SHR ESI,8
            //0054BD3B  |. 57             PUSH EDI
            //0054BD3C  |. 8BF8           MOV EDI,EAX
        } else if (version_D2Game == V110) {
            memt_byte(0xC1, 0xE8);    // CALL caller_handleServerUpdate
            MEMT_REF4(0xF88B08EE, caller_handleServerUpdate);
            //6FC86EA2   . C1EE 08        SHR ESI,8
            //6FC86EA5   . 8BF8           MOV EDI,EAX
        } else {
            memt_byte(0x33, 0xE8);    // CALL caller_handleServerUpdate
            MEMT_REF4(0x508B66D2, caller_handleServerUpdate_9);
            memt_byte(0x01, 0x90);    // NOP
            //6FC7A702   . 33D2           XOR EDX,EDX
            //6FC7A704   . 66:8B50 01     MOV DX,WORD PTR DS:[EAX+1]
        }
        log_msg("\n");
        isInstalled = true;
    }

}