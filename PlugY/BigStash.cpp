/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Use a more big stash

=================================================================*/

#include "bigStash.h"
#include "plugYFiles.h"        // Install_PlugYFiles()
#include "common.h"
#include "d2functions.h"
#include "globalVariable.h"
#include "error.h"
#include "modifMemory.h"
#include "parameters.h"

namespace PlugY {
    using namespace Commons;
    bool active_bigStash = false;
    bool active_bigStash_tested = false;
    const char *tradeStash_RefFile = "%s\\TradeStash";
    const BYTE gridX_BB = 10;
    const BYTE gridY_BB = 10;
    const DWORD gridLeft_BB = 16;
    const DWORD gridRight_BB = 302;
    const DWORD gridTop_BB = 82;
    const DWORD gridbottom_BB = 371;

    InventoryBIN *STDCALL modifStashGrid(InventoryBIN *ptInventoryBin) {
        active_bigStash_tested = true;
        if (onRealm || !active_bigStash) return ptInventoryBin;
        InventoryBIN *inventory = ptInventoryBin + 12;
        inventory->gridX = gridX_BB;
        inventory->gridY = gridY_BB;
        inventory->gridLeft = gridLeft_BB;
        inventory->gridRight = gridRight_BB;
        inventory->gridTop = gridTop_BB;
        inventory->gridBottom = gridbottom_BB;
        inventory = ptInventoryBin + 28;
        inventory->gridX = gridX_BB;
        inventory->gridY = gridY_BB;
        inventory->gridLeft = gridLeft_BB + 80;
        inventory->gridRight = gridRight_BB + 80;
        inventory->gridTop = gridTop_BB + 60;
        inventory->gridBottom = gridbottom_BB + 60;
        return ptInventoryBin;
    }

    __declspec(naked)void caller_modifStashGrid() {
        __asm{
        PUSH DWORD PTR SS:[ESP+0x14]
        PUSH DWORD PTR SS:[ESP+0x14]
        PUSH DWORD PTR SS:[ESP+0x14]
        PUSH DWORD PTR SS:[ESP+0x14]
        PUSH DWORD PTR SS:[ESP+0x14]
        CALL D2CompileTxtFile
        PUSH EAX
        CALL modifStashGrid
        RETN 0x14
        }
    }

//FCT_ASM ( caller_modifStashGrid )
//	POP ESI
//	CALL D2CompileTxtFile
//	PUSH EAX
//	CALL modifStashGrid
//	JMP ESI
//}}

    __declspec(naked)void caller_changeTradeStash() {
        __asm{
        CMP onRealm, 0
        JNZ normalTradeStash
        MOV EAX, modDataDirectory
        MOV DWORD PTR SS:[ESP+0x8], EAX
        MOV EAX, tradeStash_RefFile
        MOV DWORD PTR SS:[ESP+0x4], EAX
        normalTradeStash:
        POP EAX
        PUSH 0x104
        JMP EAX
        }
    }

    void Install_BigStash() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_PlugYFiles();
        log_msg("Patch D2Common & D2Client for make 10x10 squares in the stash. (BigStash)\n");

        // modification of stash grid
        mem_seek R8(D2Common, C9F3, CA03, 14ED3, 5FCB5, 2A505, 1BDB5, 82CA5, 6CC25, 25C0F8);
        MEMC_REF4(D2CompileTxtFile, caller_modifStashGrid);
        //01B64ED2  |. E8 99AEFFFF    CALL D2Common.#10578
        //6FDAFCB4  |. E8 A7C3FCFF    CALL D2Common.#10653
        //6FD7A504  |. E8 5743FEFF    CALL D2Common.#10496                     ; \#10496
        //6FD6BDB4  |. E8 97600200    CALL D2Common.#10244                     ; \#10244
        //6FDD2CA4  |. E8 97C2FDFF    CALL D2Common.#10849                     ; \#10849
        //6FDBCC24  |. E8 B7FEF9FF    CALL D2Common.#10037                     ; \#10037
        //0065C0F7  |. E8 F461FBFF    CALL Game.006122F0                       ; \Game.006122F0

        // modification of stash background
        mem_seek R8(D2Client, 45B1C, 45B1C, 4C61C, A643C, 749BC, A9D7C, 8CC1C, 943FC, 89EB5);
        memt_byte(0x68, 0xE8);    // CALL caller_changeTradeStash
        MEMT_REF4(0x00000104, caller_changeTradeStash);
        //6FAEC61C  |. 68 04010000    PUSH 104
        //6FB5643C  |. 68 04010000    PUSH 104
        //6FB249BC  |. 68 04010000    PUSH 104
        //6FB59D7C  |. 68 04010000    PUSH 104
        //6FB3CC1C  |. 68 04010000    PUSH 104
        //6FB443FC  |. 68 04010000    PUSH 104
        //00489EB5  |. 68 04010000    PUSH 104                                 ; |Arg2 = 00000104

        log_msg("\n");
        isInstalled = true;
    }
}
