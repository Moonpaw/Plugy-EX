/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Change Stat win per level up.

=================================================================*/

#include "statPerLevelUp.h"
#include "common.h"
#include "d2functions.h"
#include "error.h"
#include "modifMemory.h"

namespace PlugY {
    bool active_StatPerLevelUpChange = 0;
    DWORD statPerLevelUp = 5;

    __declspec(naked)void caller_changeStatPerLevelUp_114() {
        __asm{
        MOV EAX, statPerLevelUp
        IMUL EAX, EDI
        MOV DWORD PTR SS:[ESP+0xC], EAX
        JMP V2AddPlayerStat
        }
    }

    __declspec(naked)void caller_changeStatPerLevelUp_111() {
        __asm{
        MOV EAX, statPerLevelUp
        IMUL EAX, EBX
        MOV DWORD PTR SS:[ESP+0xC], EAX
        JMP V2AddPlayerStat
        }
    }

    __declspec(naked)void caller_changeStatPerLevelUp() {
        __asm{
        MOV EAX, statPerLevelUp
        IMUL EAX, EDI
        MOV DWORD PTR SS:[ESP+0xC], EAX
        JMP V2AddPlayerStat
        }
    }

    void Install_StatPerLevelUp() {
        static int isInstalled = false;
        if (isInstalled) return;
        log_msg("Patch D2Game for change Stat points win per level up. (StatPerLevelUp)\n");
        mem_seek(offset_D2Game + (version_D2Game == V114d ? 0x1709C6 : (version_D2Game == V113d ? 0xEDC9A : (version_D2Game == V113c ? 0xEB1DA : (version_D2Game == V112 ? 0xAA44A : (version_D2Game == V111b ? 0x7968A : (version_D2Game == V111 ? 0xD7ADA : (version_D2Game == V110 ? 0x4ED55 : (version_D2Game == V109d ? 0x42648 : 0x42258)))))))));
        MEMJ_REF4(V2AddPlayerStat, version_D2Game >= V114d ? caller_changeStatPerLevelUp_114 : version_D2Game >= V111 ? caller_changeStatPerLevelUp_111 : caller_changeStatPerLevelUp);
        //6FC7ED54  |. E8 61CB0900    CALL <JMP.&D2Common.#10518>
        //02057AD9  |. E8 AA28F3FF    CALL <JMP.&D2Common.#10109>
        //01FE9689  |. E8 260DF9FF    CALL <JMP.&D2Common.#10627>
        //6FCCA449  |. E8 6A01F6FF    CALL <JMP.&D2Common.#10762>
        //6FD0B1D9  |. E8 F4F2F1FF    CALL <JMP.&D2Common.#10551>
        //6FD0DC99  |. E8 08C7F1FF    CALL <JMP.&D2Common.#10645>
        //005709C5  |. E8 E6680B00    CALL Game.006272B0                       ; \Game.006272B0

        log_msg("\n");
        isInstalled = true;
    }
}
