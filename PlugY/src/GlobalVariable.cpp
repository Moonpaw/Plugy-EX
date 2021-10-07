/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Updating server.

=================================================================*/
#include <stdio.h>
//#include "bigStash.h" // active_bigStash_tested
//#include "uberQuest.h" //active_UberQuest + resetQuestState()
//#include "infinityStash.h" //active_UberQuest + resetQuestState()
#include "common.h"
#include "d2functions.h"
#include "LocalizedStrings.h"
#include "bigStash.h"
#include "error.h"
#include "modifMemory.h"
#include "globalVariable.h"
#include "uberQuest.h"
#include "parameters.h"

namespace PlugY {
    using namespace Commons;
    bool onRealm = false;
    bool needToInit = false;
    int previouslyOnRealm = -1;

// mode 0:SinglePlayer - 1:TCPIP - 2:Battlenet
    void __stdcall BtnPress(int mode) {
        needToInit = true;
        loadLocalizedStrings(D2GetLang());

//	if (active_WorldEvent)
//		initWorldEventVariables();
        if (active_UberQuest)
            resetQuestState();
        d2_assert(active_bigStash_tested && onRealm && (previouslyOnRealm == 0), "Need to restart after play an open game with the Big Stash", __FILE__, __LINE__);
        d2_assert(active_bigStash_tested && !onRealm && (previouslyOnRealm > 0), "Need to restart after play an closed game with the Big Stash", __FILE__, __LINE__);
        previouslyOnRealm = onRealm;
    }

    __declspec(naked)void caller_BnetBtnPress114() {
        __asm{
        CMP active_DisableBattleNet, 1
        JE disableBattleNet
        MOV onRealm, 1
        PUSH EAX
        PUSH 2
        CALL BtnPress
        POP EAX
        SUB ESP, 0x3FC//400
        JMP DWORD PTR SS:[ESP+0x3FC]
        disableBattleNet:
        POP EAX
        POP EAX
        RETN
        }
    }

    __declspec(naked)void caller_BnetBtnPress() {
        __asm{
        CMP active_DisableBattleNet, 1
        JE disableBattleNet
        MOV onRealm, 1
        PUSH EAX
        PUSH 2
        CALL BtnPress
        POP EAX
        SUB ESP, 0x3FC//400
        JMP DWORD PTR SS:[ESP+0x3FC]
        disableBattleNet:
        POP EAX
        RETN
        }
    }

/*
FCT_ASM ( caller_MultiPlayerBtnPress )
	CALL BtnPress
	MOV	EAX,1
	RETN
}}
*/

    __declspec(naked)void caller_TCPIPBtnPress114() {
        __asm{
        MOV onRealm, 0
        PUSH 1
        CALL BtnPress
        MOV ECX, DWORD PTR SS:[ESP]
        ADD ECX, 0xB9B0
        JMP ECX
        }
    }

    __declspec(naked)void caller_TCPIPBtnPress111() {
        __asm{
        MOV onRealm, 0
        PUSH 1
        CALL BtnPress
        MOV ESI, 0x40
        RETN
        }
    }

    __declspec(naked)void caller_TCPIPBtnPress() {
        __asm{
        MOV onRealm, 0
        PUSH 1
        CALL BtnPress
        MOV EBP, 1
        RETN
        }
    }

    __declspec(naked)void caller_SinglePlayerBtnPress() {
        __asm{
        MOV onRealm, 0
        PUSH 0
        CALL BtnPress
        MOV EDX, 0x400
        RETN
        }
    }

    __declspec(naked)void caller_fixClientRemovingBug() {
        __asm{
        TEST ECX, ECX
        JE notFound
        CMP DWORD PTR DS:[ECX], EBP
        JE found
        next:
        MOV EAX, ECX
        MOV ECX, DWORD PTR DS:[EAX+0x4A8]
        TEST ECX, ECX
        JE notFound
        CMP DWORD PTR DS:[ECX], EBP
        JNZ next
        found:
        ADD DWORD PTR SS:[ESP], 0xB
        RETN
        notFound:
        ADD DWORD PTR SS:[ESP], 0x1D
        RETN
        }
    }

    void Install_VariableOnRealm() {
        static int isInstalled = false;
        if (isInstalled) return;
        log_msg("Patch D2Launch for set not on realm variable. (VariableonRealm)\n");

        // click on Battle.net button
        mem_seek(offset_D2Launch + (version_D2Launch == V114d ? 0x3533B : (version_D2Launch == V113d ? 0x11C65 : (version_D2Launch == V113c ? 0x19295 : (version_D2Launch == V112 ? 0x17D15 : (version_D2Launch == V111b ? 0x18AA5 : (version_D2Launch == V111 ? 0x129E5 : (version_D2Launch == V110 ? 0x9915 : (version_D2Launch == V109d ? 0x81A5 : 0x8195)))))))));
        memt_byte(0x81, 0xE8);    // CALL
        MEMT_REF4(0x000400EC, version_D2Launch == V114d ? caller_BnetBtnPress114 : caller_BnetBtnPress);
        memt_byte(0x00, 0x90);    // NOP
        //6FA529E5   . 81EC 00040000  SUB ESP,400
        //0043533B  |. 81EC 00040000  SUB ESP,400

        // click on Multiplayer button
//	mem_seek R7(D2Launch, D5EC, D5CC, EFFC, 0000, 0000, 0000, 0000);
//	memt_byte( 0xB8, 0xE8 );	// CALL
//	MEMT_REF4( 0x00000001, caller_MultiPlayerBtnPress);
        //6FA1EFFC   . B8 01000000    MOV EAX,1

        // click on TCP/IP button
        mem_seek(offset_D2Launch + (version_D2Launch == V114d ? 0x2FFEC : (version_D2Launch == V113d ? 0x1053E : (version_D2Launch == V113c ? 0x17B8E : (version_D2Launch == V112 ? 0x16659 : (version_D2Launch == V111b ? 0x17409 : (version_D2Launch == V111 ? 0x11329 : (version_D2Launch == V110 ? 0x9F99 : (version_D2Launch == V109d ? 0x87C9 : 0x87B9)))))))));
        if (version_D2Launch <= V110) {
            memt_byte(0xBD, 0xE8);    // CALL
            MEMT_REF4(0x00000001, caller_TCPIPBtnPress);
        } else if (version_D2Launch >= V114d) {
            MEMT_REF4(0x0000B9B0, caller_TCPIPBtnPress114);
            //0042FFEB   . E8 B0B90000    CALL Game.0043B9A0
        } else {
            memt_byte(0xBE, 0xE8);    // CALL
            MEMT_REF4(0x00000040, caller_TCPIPBtnPress111);
            //6FA51329   . BE 40000000    MOV ESI,40
        }

        // click on SinglePlayer button
        mem_seek(offset_D2Launch + (version_D2Launch == V114d ? 0x30BC9 : (version_D2Launch == V113d ? 0xA906 : (version_D2Launch == V113c ? 0x11F36 : (version_D2Launch == V112 ? 0x10A56 : (version_D2Launch == V111b ? 0x117E6 : (version_D2Launch == V111 ? 0xB726 : (version_D2Launch == V110 ? 0xEC16 : (version_D2Launch == V109d ? 0xD1E6 : 0xD1F6)))))))));
        memt_byte(0xBA, 0xE8);    // CALL
        MEMT_REF4(0x00000400, caller_SinglePlayerBtnPress);
        //6FA4B726   . BA 00040000    MOV EDX,400
        //00430BC9  |. BA 00040000    MOV EDX,400

        if (version_D2Game == V110) {
            log_msg("\nPatch D2Game for fixing ptClient removing bug. (VariableonRealm)\n");
            //Bug crash ptClient search fix (for Megalixir Mod).
            mem_seek(offset_D2Game + (version_D2Game == V114d ? 0x0000 : (version_D2Game == V113d ? 0x0000 : (version_D2Game == V113c ? 0x0000 : (version_D2Game == V112 ? 0x0000 : (version_D2Game == V111b ? 0x0000 : (version_D2Game == V111 ? 0x0000 : (version_D2Game == V110 ? 0x2B97 : (version_D2Game == V109d ? 0x0000 : 0x0000)))))))));
            memt_byte(0x39, 0xE8);
            MEMT_REF4(0x8B0C7429, caller_fixClientRemovingBug);
            memt_byte(0xC1, 0x90);
            //6FC32B97  |> 3929           CMP DWORD PTR DS:[ECX],EBP
            //6FC32B99  |. 74 0C          JE SHORT D2Game.6FC32BA7
            //6FC32B9B  |> 8BC1           MOV EAX,ECX
        }
        log_msg("\n");
        isInstalled = true;
    }
}
