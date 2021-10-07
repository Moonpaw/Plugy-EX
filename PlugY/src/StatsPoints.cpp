/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Unassign Stats Point for futher re-assignment.

=================================================================*/

#include "plugYFiles.h"            // Install_PlugYImagesFiles()
#include "interface_Stats.h"    // Install_InterfaceStats()
#include "updateServer.h"
#include "extraOptions.h"
#include "common.h"
#include "error.h"
#include <stdio.h>
#include "globalVariable.h"
#include "d2functions.h"
#include "modifMemory.h"
#include <d2constants.h>
#include "LocalizedStrings.h"

namespace PlugY {
    bool active_StatsPoints = 0;
    DWORD keyUsedForUnassignStatPoint = VK_CONTROL;
    bool active_StatsShiftClickLimit = 1;
    DWORD limitValueToShiftClick = 5;

    void UnassignStr(Commons::Unit *ptChar, int nb) {
        log_msg("Start Unassign Strengh\n");
        int currentStr, removePtsNb;
        CharStatsBIN *charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
        currentStr = D2GetPlayerBaseStat(ptChar, STATS_STRENGTH, 0);
        if (currentStr <= charStats->baseSTR) return;
        removePtsNb = currentStr - charStats->baseSTR >= nb ? nb : currentStr - charStats->baseSTR;
        if (currentStr - removePtsNb < 1) removePtsNb = currentStr - 1;
        log_msg("Start Unassign Strengh (cur %d, base %d, rem %d)\n", currentStr, charStats->baseSTR, removePtsNb);
        D2AddPlayerStat(ptChar, STATS_STRENGTH, -removePtsNb, 0);
        D2AddPlayerStat(ptChar, STATS_STATPTS, removePtsNb, 0);
    }

    void UnassignDex(Commons::Unit *ptChar, int nb) {
        log_msg("Start Unassign Dexterity\n");
        int currentDex, removePtsNb;
        CharStatsBIN *charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
        currentDex = D2GetPlayerBaseStat(ptChar, STATS_DEXTERITY, 0);
        if (currentDex <= charStats->baseDEX) return;
        removePtsNb = currentDex - charStats->baseDEX >= nb ? nb : currentDex - charStats->baseDEX;
        if (currentDex - removePtsNb < 1) removePtsNb = currentDex - 1;
        log_msg("Start Unassign Dexterity (cur %d, base %d, rem %d)\n", currentDex, charStats->baseDEX, removePtsNb);
        D2AddPlayerStat(ptChar, STATS_DEXTERITY, -removePtsNb, 0);
        D2AddPlayerStat(ptChar, STATS_STATPTS, removePtsNb, 0);
    }

    void UnassignVit(Commons::Unit *ptChar, int nb) {
        log_msg("Start Unassign Vitality\n");
        int currentVit, removePtsNb, removeVitNb, removeStaNb;
        CharStatsBIN *charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
        currentVit = D2GetPlayerBaseStat(ptChar, STATS_VITALITY, 0);
        if (currentVit <= charStats->baseVIT) return;
        removePtsNb = currentVit - charStats->baseVIT >= nb ? nb : currentVit - charStats->baseVIT;
        if (currentVit - removePtsNb < 1) removePtsNb = currentVit - 1;
        removeVitNb = removePtsNb * (charStats->lifePerVitality << 6);
        removeStaNb = removePtsNb * (charStats->staminaPerVitality << 6);
        log_msg("Start Unassign Vitality (cur %d, base %d, rem %d)\n", currentVit, charStats->baseVIT, removePtsNb);
        D2AddPlayerStat(ptChar, STATS_VITALITY, -removePtsNb, 0);
        D2AddPlayerStat(ptChar, STATS_MAXHP, -removeVitNb, 0);
        D2AddPlayerStat(ptChar, STATS_MAXSTAMINA, -removeStaNb, 0);
        D2AddPlayerStat(ptChar, STATS_STATPTS, removePtsNb, 0);
    }

    void UnassignEne(Commons::Unit *ptChar, int nb) {
        log_msg("Start Unassign Energy\n");
        int currentEne, removePtsNb, removeManNb;
        CharStatsBIN *charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
        currentEne = D2GetPlayerBaseStat(ptChar, STATS_ENERGY, 0);
        if (currentEne <= charStats->baseENE) return;
        removePtsNb = currentEne - charStats->baseENE >= nb ? nb : currentEne - charStats->baseENE;
        if (currentEne - removePtsNb < 1) removePtsNb = currentEne - 1;
        removeManNb = removePtsNb * (charStats->manaPerMagic << 6);
        log_msg("Start Unassign Energy (cur %d, base %d, rem %d)\n", currentEne, charStats->baseENE, removePtsNb);
        D2AddPlayerStat(ptChar, STATS_ENERGY, -removePtsNb, 0);
        D2AddPlayerStat(ptChar, STATS_MAXMANA, -removeManNb, 0);
        D2AddPlayerStat(ptChar, STATS_STATPTS, removePtsNb, 0);
    }

    void UnassignStrPoint(Commons::Unit *ptChar) {
        UnassignStr(ptChar, 1);
    }

    void UnassignStrPoints(Commons::Unit *ptChar) {
        UnassignStr(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick : 0x7FFFFFFF);
    }

    void UnassignDexPoint(Commons::Unit *ptChar) {
        UnassignDex(ptChar, 1);
    }

    void UnassignDexPoints(Commons::Unit *ptChar) {
        UnassignDex(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick : 0x7FFFFFFF);
    }

    void UnassignVitPoint(Commons::Unit *ptChar) {
        UnassignVit(ptChar, 1);
    }

    void UnassignVitPoints(Commons::Unit *ptChar) {
        UnassignVit(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick : 0x7FFFFFFF);
    }

    void UnassignEnePoint(Commons::Unit *ptChar) {
        UnassignEne(ptChar, 1);
    }

    void UnassignEnePoints(Commons::Unit *ptChar) {
        UnassignEne(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick : 0x7FFFFFFF);
    }


//////////////////////////////////


    void __stdcall printDisabledStatsBtn(WORD statID, sDrawImageInfo *data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6) {
        if (onRealm || !D2isLODGame()) {
            D2PrintImage(data, x, y, p4, p5, p6);
            return;
        }
        Unit *ptChar = D2GetClientPlayer();
        CharStatsBIN *charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
        int minValue = 1;
        switch (statID) {
            case STATS_STRENGTH:
                minValue = charStats->baseSTR;
                break;
            case STATS_DEXTERITY:
                minValue = charStats->baseDEX;
                break;
            case STATS_VITALITY:
                minValue = charStats->baseVIT;
                break;
            case STATS_ENERGY:
                minValue = charStats->baseENE;
                break;
        }
        int statValue = D2GetPlayerBaseStat(ptChar, statID, 0);
        if (isOnRect(D2GetMouseX(), D2GetMouseY(), x + 5, y + 5, 32, 32)) {
            WCHAR text[100];
            if (active_StatsShiftClickLimit)
                _snwprintf(text, sizeof(text) - 1, getLocalString(STR_STATS_UNASSIGN_WITH_LIMIT), limitValueToShiftClick);
            else
                _snwprintf(text, sizeof(text) - 1, getLocalString(STR_STATS_UNASSIGN_WITHOUT_LIMIT));
            if (active_DisplayBaseStatsValue) {
                wcscat(text, L"\n");
                int len = wcslen(text);
                _snwprintf(text + len, sizeof(text) - len, getLocalString(STR_STATS_BASE_MIN), statValue, minValue);
            }
            D2SetFont(1);
            D2PrintPopup(text, x + 18, y - 32, WHITE, 1);
        }
        if (GetKeyState(keyUsedForUnassignStatPoint) >= 0) {
            if (D2GetPlayerBaseStat(ptChar, 4, 0) <= 0)
                setFrame(data, 2);
        } else {
            setImage(data, unassignStatsBtnImages);
            if (minValue >= statValue)
                setFrame(data, 2);
        }
        D2PrintImage(data, x, y, p4, p5, p6);
    }

    __declspec(naked)void caller_printUnassignStatsBtn() {
        __asm{
        POP EAX
        XOR ECX, ECX
        MOV CX, WORD PTR DS:[ESI+8]
        PUSH ECX
        PUSH EAX
        JMP printDisabledStatsBtn
        }
    }

    BYTE currentMsgID = 0;

    WORD UnassignStats() {
        if (onRealm || !D2isLODGame()) return 0;
        return GetKeyState(keyUsedForUnassignStatPoint);
    }

    __declspec(naked)void caller_UnassignStats_9() {
        __asm{
        PUSH EAX
        CALL UnassignStats
        TEST AX, AX
        POP EAX
        JNL NOT_CTRL

        MOV currentMsgID, 0x10
        TEST AX, AX
        JNL NOT_SHIFT
        ADD currentMsgID, 4
        NOT_SHIFT:
        MOV EAX, 1
        MOV ESI, EAX
        RETN

        NOT_CTRL:
        MOV currentMsgID, 0
        TEST AX, AX
        MOV EAX, 1
        RETN
        }
    }

    __declspec(naked)void caller_UnassignStats() {
        __asm{
        PUSH EAX
        CALL UnassignStats
        TEST AX, AX
        POP EAX
        JNL NOT_CTRL

        MOV currentMsgID, 0x10
        TEST AX, AX
        JNL NOT_SHIFT
        ADD currentMsgID, 4
        NOT_SHIFT:
        MOV ESI, 1
        ADD DWORD PTR SS:[ESP], 0xB
        RETN

        NOT_CTRL:
        MOV currentMsgID, 0
        TEST AX, AX
        JNL END_UNASSGNSTATS
        ADD DWORD PTR SS:[ESP], 0x7
        END_UNASSGNSTATS:
        RETN
        }
    }

    __declspec(naked)void caller_setValue_114() {
        __asm{
        MOV CL, 0x3A
        OR DX, WORD PTR DS:[ESI]
        ADD DL, currentMsgID
        MOV CH, DL
        RETN
        }
    }

    __declspec(naked)void caller_setValue_111() {
        __asm{
        ADD CL, currentMsgID
        MOV WORD PTR SS:[ESP+0x19], CX
        RETN
        }
    }

    __declspec(naked)void caller_setValue() {
        __asm{
        ADD DL, currentMsgID
        JMP D2SendToServer3
        }
    }

    DWORD __stdcall pushDown(DWORD num) {
        Unit *ptChar = D2GetClientPlayer();
        if (!D2isLODGame() || GetKeyState(keyUsedForUnassignStatPoint) >= 0)//GetAsyncKeyState
        {
            if (D2GetPlayerBaseStat(ptChar, 4, 0) > 0)
                return 1;
        } else {
            CharStatsBIN *charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
            switch (num) {
                case 0:
                    if ((DWORD) charStats->baseSTR < (DWORD) D2GetPlayerBaseStat(ptChar, STATS_STRENGTH, 0))
                        return 1;
                    break;
                case 1:
                    if ((DWORD) charStats->baseDEX < (DWORD) D2GetPlayerBaseStat(ptChar, STATS_DEXTERITY, 0))
                        return 1;
                    break;
                case 2:
                    if ((DWORD) charStats->baseVIT < (DWORD) D2GetPlayerBaseStat(ptChar, STATS_VITALITY, 0))
                        return 1;
                    break;
                case 3:
                    if ((DWORD) charStats->baseENE < (DWORD) D2GetPlayerBaseStat(ptChar, STATS_ENERGY, 0))
                        return 1;
                    break;
            }
        }
        return 0;
    }

    __declspec(naked)void caller_pushDown_114() {
        __asm{
        PUSH EDX
        PUSH DWORD PTR SS:[EBP+0x8]
        CALL pushDown
        POP EDX
        TEST EAX, EAX
        JNZ end_pushDown
        SUB DWORD PTR SS:[ESP], 0x22
        RETN
        end_pushDown :
        MOV EAX, DWORD PTR SS:[EBP+8]
        LEA ECX, DWORD PTR DS:[EAX*8]
        RETN
        }
    }

    __declspec(naked)void caller_pushDown_111() {
        __asm{
        PUSH EDX
        PUSH EDX
        CALL pushDown
        POP EDX
        TEST EAX, EAX
        JNZ end_pushDown
        SUB DWORD PTR SS:[ESP], 0x22
        RETN
        end_pushDown:
        MOV EDI, 1
        RETN
        }
    }

    __declspec(naked)void caller_pushDown() {
        __asm{
        PUSH EDX
        PUSH EDX
        CALL pushDown
        POP EDX
        TEST EAX, EAX
        JNZ end_pushDown
        SUB DWORD PTR SS:[ESP], 0x22
        RETN
        end_pushDown:
        LEA EAX, DWORD PTR DS:[EDX*8]
        RETN
        }
    }

    void Install_StatsPoints() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_PlugYImagesFiles();
//	Install_InterfaceStats();
        Install_UpdateServer();
        log_msg("Patch D2Client for unassign stat points when specified key is press. (StatsPoints)\n");

        // Always print stat button images.
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7FFB : (version_D2Client == V113d ? 0xBF955 : (version_D2Client == V113c ? 0xBD1B5 : (version_D2Client == V112 ? 0x6B59A : (version_D2Client == V111b ? 0x8963A : (version_D2Client == V111 ? 0x82BBA : (version_D2Client == V110 ? 0x30073 : (version_D2Client == V109d ? 0x29B02 : 0x29B12)))))))));
        memt_byte(0x8B, 0xEB);    // JMP SHORT D2Client.6FAD0088
        memt_byte(version_D2Client == V114d ? 0x4D : 0x4C, getAddressOfVersion(version_D2Client, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x12));
        memt_byte(version_D2Client == V114d ? 0xF8 : 0x24, 0x90);    // NOP
        if (version_D2Client < V114a) memt_byte(getAddressOfVersion(version_D2Client, 0x20, 0x20, 0x14, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x53), 0x90);            // NOP (V109d:0x20 , V110:0x14
        //6FAD0073     8B4C24 14      MOV ECX,DWORD PTR SS:[ESP+14]
        //6FB32BBA   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
        //6FB3963A   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
        //6FB1B59A   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
        //6FB6D1B5  |> 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
        //6FB6F955   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
        //004A7FFB   > 8B4D F8        MOV ECX,DWORD PTR SS:[EBP-8]
        //004A7FFE   . 53             PUSH EBX                                 ; /Arg3

        //print our buttons
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA808C : (version_D2Client == V113d ? 0xBF9DE : (version_D2Client == V113c ? 0xBD23E : (version_D2Client == V112 ? 0x6B637 : (version_D2Client == V111b ? 0x896D4 : (version_D2Client == V111 ? 0x82C54 : (version_D2Client == V110 ? 0x300FD : (version_D2Client == V109d ? 0x29B8D : 0x29B9D)))))))));
        MEMJ_REF4(D2PrintImage, caller_printUnassignStatsBtn);
        //6FB32C53   . E8 82A3F8FF    CALL <JMP.&D2gfx.#10047>
        //6FB396D3   . E8 D238F8FF    CALL <JMP.&D2gfx.#10044>
        //6FB1B636   . E8 431AFAFF    CALL <JMP.&D2gfx.#10024>
        //6FB6D23D   . E8 54FEF4FF    CALL <JMP.&D2gfx.#10041>
        //6FB6F9DD   . E8 ECD5F4FF    CALL <JMP.&D2gfx.#10042>
        //004A808B   . E8 F0E30400    CALL Game.004F6480                       ; \Game.004F6480

        // Always manage push down.
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA77E4 : (version_D2Client == V113d ? 0xBF579 : (version_D2Client == V113c ? 0xBCDD9 : (version_D2Client == V112 ? 0x6B1B9 : (version_D2Client == V111b ? 0x89259 : (version_D2Client == V111 ? 0x827D9 : (version_D2Client == V110 ? 0x3134D : (version_D2Client == V109d ? 0x2AA6B : 0x2AA7B)))))))));
        memt_byte(0x74, 0x90);    // NOP
        memt_byte(version_D2Client == V114d ? 0x62 : 0x4E, 0x90);    // NOP
        //6FAD134D     74 4E          JE SHORT D2Client.6FAD139D
        //6FB327D9   . 74 4E          JE SHORT D2Client.6FB32829
        //6FB39259   . 74 4E          JE SHORT D2Client.6FB392A9
        //6FB1B1B9     74 4E          JE SHORT D2Client.6FB1B209
        //6FB6CDD9   . 74 4E          JE SHORT D2Client.6FB6CE29
        //6FB6F579   . 74 4E          JE SHORT D2Client.6FB6F5C9
        //004A77E4   . 74 62          JE SHORT Game.004A7848

        if (version_D2Client >= V114d) {
            // On Push down.
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7863 : (version_D2Client == V113d ? 0xBF5E4 : (version_D2Client == V113c ? 0xBCE44 : (version_D2Client == V112 ? 0x6B224 : (version_D2Client == V111b ? 0x892C4 : (version_D2Client == V111 ? 0x82844 : (version_D2Client == V110 ? 0x313B8 : (version_D2Client == V109d ? 0x2AAD6 : 0x2AAE6)))))))));
            memt_byte(0x8B, 0xE8);
            MEMT_REF4(0x0C8D0845, caller_pushDown_114);
            memt_byte(0xC5, 0x90);
            memt_dword(0x00000000, 0x90909090);
            //004A7863   > 8B45 08        MOV EAX,DWORD PTR SS:[EBP+8]
            //004A7866   . 8D0CC5 0000000>LEA ECX,DWORD PTR DS:[EAX*8]
        } else if (version_D2Client >= V111) {
            // On Push down.
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7863 : (version_D2Client == V113d ? 0xBF5E4 : (version_D2Client == V113c ? 0xBCE44 : (version_D2Client == V112 ? 0x6B224 : (version_D2Client == V111b ? 0x892C4 : (version_D2Client == V111 ? 0x82844 : (version_D2Client == V110 ? 0x313B8 : (version_D2Client == V109d ? 0x2AAD6 : 0x2AAE6)))))))));
            memt_byte(0x6B, 0xE8);
            MEMT_REF4(0x01BF0ED2, caller_pushDown_111);
            memt_byte(0x00, 0x6B);    // IMUL EDX,EDX,0E
            memt_byte(0x00, 0xD2);
            memt_byte(0x00, 0x0E);
            //6FB32844   > 6BD2 0E        IMUL EDX,EDX,0E
            //6FB32847   . BF 01000000    MOV EDI,1
            //6FB392C4   > 6BD2 0E        IMUL EDX,EDX,0E
            //6FB392C7   . BF 01000000    MOV EDI,1
            //6FB1B224   6BD2 0E          IMUL EDX,EDX,0E
            //6FB1B227   BF 01000000      MOV EDI,1
            //6FB6CE44   > 6BD2 0E        IMUL EDX,EDX,0E
            //6FB6CE47   . BF 01000000    MOV EDI,1
            //6FB6F5E4   > 6BD2 0E        IMUL EDX,EDX,0E
            //6FB6F5E7   . BF 01000000    MOV EDI,1

        } else {
            // On Push down.
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x0000 : (version_D2Client == V113d ? 0x0000 : (version_D2Client == V113c ? 0x0000 : (version_D2Client == V112 ? 0x0000 : (version_D2Client == V111b ? 0x892C4 : (version_D2Client == V111 ? 0x82844 : (version_D2Client == V110 ? 0x313B8 : (version_D2Client == V109d ? 0x2AAD6 : 0x2AAE6)))))))));
            memt_byte(0x8D, 0xE8);    // CALL
            MEMT_REF4(0x0000D504, caller_pushDown);
            memt_byte(0x00, 0x90);    // NOP
            memt_byte(0x00, 0x90);    // NOP
            //6FAD13B8   8D04D5 00000000  LEA EAX,DWORD PTR DS:[EDX*8]
        }
        if (version_D2Client >= V110) {
            // Always manage push up.
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7976 : (version_D2Client == V113d ? 0xC05E9 : (version_D2Client == V113c ? 0xBDE49 : (version_D2Client == V112 ? 0x6C249 : (version_D2Client == V111b ? 0x8A2E9 : (version_D2Client == V111 ? 0x83869 : (version_D2Client == V110 ? 0x3152E : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
            memt_byte(version_D2Client == V114d ? 0x0F : 0x74, 0x90);    // NOP
            memt_byte(version_D2Client == V114d ? 0x84 : version_D2Client >= V111 ? 0x65 : 0x68, 0x90);    // NOP
            if (version_D2Client == V114d) memt_dword(0x000000BB, 0x90909090);
            //6FAD152E     74 68          JE SHORT D2Client.6FAD1598
            //6FB33869   . 74 65          JE SHORT D2Client.6FB338D0
            //6FB3A2E9   . 74 65          JE SHORT D2Client.6FB3A350
            //6FB1C249     74 65          JE SHORT D2Client.6FB1C2B0
            //6FB6DE49   . 74 65          JE SHORT D2Client.6FB6DEB0
            //6FB705E9   . 74 65          JE SHORT D2Client.6FB70650
            //004A7976  |. 0F84 BB000000  JE Game.004A7A37

            // Unassign stats point when ctrl is push.
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA79F2 : (version_D2Client == V113d ? 0xC069B : (version_D2Client == V113c ? 0xBDEFB : (version_D2Client == V112 ? 0x6C2FB : (version_D2Client == V111b ? 0x8A39B : (version_D2Client == V111 ? 0x8391B : (version_D2Client == V110 ? 0x315D3 : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
            memt_byte(0x66, 0xE8);    // CALL
            MEMT_REF4(0x077CC085, caller_UnassignStats);
            //6FAD15D3   . 66:85C0        TEST AX,AX
            //6FAD15D6   . 7C 07          JL SHORT D2Client.6FAD15DF
            //6FB3391B   . 66:85C0        TEST AX,AX
            //6FB3391E   . 7C 07          JL SHORT D2Client.6FB33927
            //6FB3A39B   . 66:85C0        TEST AX,AX
            //6FB3A39E   . 7C 07          JL SHORT D2Client.6FB3A3A7
            //6FB1C2FB   . 66:85C0        TEST AX,AX
            //6FB1C2FE   . 7C 07          JL SHORT D2Client.6FB1C307
            //6FB6DEFB   . 66:85C0        TEST AX,AX
            //6FB6DEFE   . 7C 07          JL SHORT D2Client.6FB6DF07
            //6FB7069B   . 66:85C0        TEST AX,AX
            //6FB7069E   . 7C 07          JL SHORT D2Client.6FB706A7
            //004A79F2  |. 66:85C0        TEST AX,AX
            //004A79F5  |. 7C 07          JL SHORT Game.004A79FE
        } else {
            // Always manage push up.
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x0000 : (version_D2Client == V113d ? 0x0000 : (version_D2Client == V113c ? 0x0000 : (version_D2Client == V112 ? 0x0000 : (version_D2Client == V111b ? 0x0000 : (version_D2Client == V111 ? 0x0000 : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x2AC45 : 0x2AC55)))))))));
            memt_byte(0x0F, 0x90);    // NOP
            memt_byte(0x84, 0x90);    // NOP
            memt_dword(0x000000AE, 0x90909090);    // NOP NOP NOP NOP
            //6FACAC45   . 0F84 AE000000  JE D2Client.6FACACF9

            // Unassign stats point when ctrl is push.
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x0000 : (version_D2Client == V113d ? 0x0000 : (version_D2Client == V113c ? 0x0000 : (version_D2Client == V112 ? 0x0000 : (version_D2Client == V111b ? 0x0000 : (version_D2Client == V111 ? 0x0000 : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x2ACC9 : 0x2ACD9)))))))));
            memt_byte(0xB8, 0xE8);    // CALL
            MEMT_REF4(0x00000001, caller_UnassignStats_9);
            //6FACACC9   . B8 01000000    MOV EAX,1
        }

        // Set the id for the calling function.
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7A29 : (version_D2Client == V113d ? 0xC06DE : (version_D2Client == V113c ? 0xBDF3E : (version_D2Client == V112 ? 0x6C33E : (version_D2Client == V111b ? 0x8A3DE : (version_D2Client == V111 ? 0x8395E : (version_D2Client == V110 ? 0x31611 : (version_D2Client == V109d ? 0x2ACF2 : 0x2AD02)))))))));
        if (version_D2Client >= V111) {
            memt_byte(version_D2Client == V114d ? 0xB1 : 0x66, 0xE8);    // CALL
            MEMT_REF4(version_D2Client == V114d ? 0x160B663A : 0x15244C89, version_D2Client == V114d ? caller_setValue_114 : caller_setValue_111);
            //6FB3395E   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX
            //6FB3A3DE   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX
            //6FB1C33E   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX              ; |
            //6FB6DF3E   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX              ; |
            //6FB706DE   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX              ; |
            //004A7A29  |. B1 3A          |MOV CL,3A
            //004A7A2B  |. 66:0B16        |OR DX,WORD PTR DS:[ESI]
        } else {
            MEMC_REF4(D2SendToServer3, caller_setValue);
            //6FAD1610   . E8 7BC3FDFF    CALL D2Client.6FAAD990
        }
        log_msg("\n");
        isInstalled = true;
    }

/*********************************************************************************/


    __declspec(naked)void caller_LimitShift_111() {
        __asm{
        CMP EDI, limitValueToShiftClick
        JL DontTruncTheValue
        MOV EDI, limitValueToShiftClick
        DontTruncTheValue:
        JMP DWORD PTR DS:[GetKeyState]
        }
    }

    __declspec(naked)void caller_LimitShift() {
        __asm{
        CMP ESI, limitValueToShiftClick
        JL DontTruncTheValue
        MOV ESI, limitValueToShiftClick
        DontTruncTheValue:
        JMP DWORD PTR DS:[GetKeyState]
        }
    }

    void Install_StatsLimitShiftClick() {
        static int isInstalled = false;
        if (isInstalled) return;
        log_msg("Patch D2Client for limit the assigment of stat points when shift is used. (LimitShift)\n");

        // Limit the assigment of stat points.
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA79EC : (version_D2Client == V113d ? 0xC0695 : (version_D2Client == V113c ? 0xBDEF5 : (version_D2Client == V112 ? 0x6C2F5 : (version_D2Client == V111b ? 0x8A395 : (version_D2Client == V111 ? 0x83915 : (version_D2Client == V110 ? 0x315CD : (version_D2Client == V109d ? 0x2ACC0 : 0x2ACD0)))))))));
        memt_byte(0xFF, 0x90);    // NOP
        memt_byte(0x15, 0xE8);    // CALL
        MEMD_REF4(GetKeyState, version_D2Client >= V111 ? caller_LimitShift_111 : caller_LimitShift);
        //6FAD15CD   . FF15 68E0B66F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
        //6FB33915   . FF15 CCF0B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
        //6FB3A395   . FF15 08F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
        //6FB1C2F5   . FF15 10F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState
        //6FB6DEF5   . FF15 04F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState
        //6FB70695   . FF15 2001B86F  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState
        //004A79EC  |. FF15 5CC46C00  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState

        log_msg("\n");
        isInstalled = true;
    }
}