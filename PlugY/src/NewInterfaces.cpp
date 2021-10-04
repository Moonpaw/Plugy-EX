/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Interface functions

=================================================================*/

#include "plugYFiles.h"        // Install_PlugYImagesFiles()
#include "globalVariable.h"
#include "updateServer.h"    // Install_UpdateServer()
#include "interface_Stats.h"// Install_InterfaceStats()
#include "newInterfaces.h"
#include "newInterface_Stats.h"
#include "newInterface_StatsPageTwo.h"
#include "newInterface_Runewords.h"
#include "common.h"
#include <stdio.h>
#include "d2functions.h"
#include "error.h"
#include "LocalizedStrings.h"
#include <updatingConst.h>
#include <d2constants.h>
#include "modifMemory.h"

namespace PlugY {
    bool active_newInterfaces = false;
    bool selectMainPageOnOpenning = true;
    bool printBackgroundOnMainPage = true;
    DWORD bDontPrintBorder = false;
    int selectedPage = 0;
    int lastPage = 0;
    int extraHiddenPage = 0;

    void GoNextStatPage() {
        selectedPage++;
        if (selectedPage > lastPage + 2)
            selectedPage = 0;
    }

    void GoPreviousStatPage() {
        selectedPage--;
        if (selectedPage < 0)
            selectedPage = lastPage;
    }

    void GoStatPage(int page) {
        if ((page >= 0) && (page <= lastPage + (D2GetResolution() ? extraHiddenPage : 0)))
            selectedPage = page;
        else {
            selectedPage = 0;
        }

    }

    int GetCurrentPage() {
        return selectedPage;
    }

//Itemtype filtering
//bool ItemtypeIsAllowed(WORD* iTypes, std::string weapons, std::string arms, std::string charms, bool showWeapons, bool showArmors, bool showCharms)
//{
//	for (int i = 0; i < 6; i++)
//	{
//		int iType = iTypes[i];
//		if (iType >= 0)
//		{
//			if (showWeapons)
//			{
//				if (weapons.find(" " + std::to_string(iType) + ",") != std::string::npos)
//				{
//					return true;
//				}
//			}
//			else if (showArmors)
//			{
//				if (arms.find(" " + std::to_string(iType) + ",") != std::string::npos)
//				{
//					return true;
//				}
//			}
//			else if (showCharms)
//			{
//				if (charms.find(" " + std::to_string(iType) + ",") != std::string::npos)
//				{
//					return true;
//				}
//			}
//		}
//	}
//}

    void STDCALL printCustomPage() {
        if (onRealm) {
            D2PrintStatsPage();
            return;
        }
        if ((selectedPage > 0) && (selectedPage <= lastPage))
            printNewStatsPageTwo(selectedPage);
        else if (selectedPage == lastPage + 1)
            printRuneWordsPage();
        else if (selectedPage == lastPage + 2)
            printNewStatsPage();
        else
            D2PrintStatsPage();
    }

    DWORD STDCALL mouseCustomPageLeftDown(sWinMessage *msg) {
        if (onRealm) return -1;
        if ((selectedPage > 0) && (selectedPage <= lastPage))
            return mouseNewStatsPageTwoLeftDown(msg);
        else if (selectedPage == lastPage + 1)
            return mouseRuneWordsPageLeftDown(msg);
        else if (selectedPage == lastPage + 2)
            return mouseNewStatsPageLeftDown(msg);
        else
            return -1;
    }

    DWORD STDCALL mouseCustomPageLeftUp(sWinMessage *msg) {
        if (onRealm) return -1;
        if ((selectedPage > 0) && (selectedPage <= lastPage))
            return mouseNewStatsPageTwoLeftUp(msg);
        else if (selectedPage == lastPage + 1)
            return mouseRuneWordsPageLeftUp(msg);
        else if (selectedPage == lastPage + 2)
            return mouseNewStatsPageLeftUp(msg);
        else
            return -1;
    }

    __declspec(naked)void caller_DontPrintBorder_114() {
        __asm{
        MOV ECX, bDontPrintBorder
        TEST ECX, ECX
        JE printBorder
        MOV bDontPrintBorder, 0
        ADD DWORD PTR SS:[ESP], 0xC1
        RETN
        printBorder:
        POP ECX
        PUSH 0x48
        LEA EAX, DWORD PTR SS:[EBP-0x48]
        JMP ECX
        }
    }

    __declspec(naked)void caller_DontPrintBorder_111() {
        __asm{
        MOV ECX, bDontPrintBorder
        TEST ECX, ECX
        JE printBorder
        MOV bDontPrintBorder, 0
        ADD DWORD PTR SS:[ESP], 0xBC
        RETN
        printBorder:
        MOV ECX, 0x12
        RETN
        }
    }

    __declspec(naked)void caller_DontPrintBorder() {
        __asm{
        MOV ECX, bDontPrintBorder
        TEST ECX, ECX
        JE printBorder
        MOV bDontPrintBorder, 0
        ADD DWORD PTR SS:[ESP], 0xB6
        RETN
        printBorder:
        MOV ECX, 0x12
        RETN
        }
    }

    __declspec(naked)void caller_mouseCustomPageLeftDown_114() {
        __asm{
        PUSH EAX
        PUSH ESI
        CALL mouseCustomPageLeftDown
        TEST EAX, EAX
        POP EAX
        JE end_mouseNewPageLDown
        JG continue_mouseNewPageLDown
        LEA ECX, DWORD PTR DS:[EAX+0x80]
        RETN
        continue_mouseNewPageLDown:
        POP EAX
        ADD EAX, 0x172
        PUSH EDI
        JMP EAX
        RETN
        end_mouseNewPageLDown:
        ADD ESP, 4
        POP ESI
        POP EBX
        POP EBP
        RETN 4
        }
    }

    __declspec(naked)void caller_mouseCustomPageLeftDown_111() {
        __asm{
        PUSH EAX
        PUSH ESI
        CALL mouseCustomPageLeftDown
        TEST EAX, EAX
        POP EAX
        JE end_mouseNewPageLDown
        JG continue_mouseNewPageLDown
        LEA ECX, DWORD PTR DS:[EAX+0x80]
        RETN
        continue_mouseNewPageLDown:
        POP EAX
        ADD EAX, 0x143
        PUSH EDI
        JMP EAX
        RETN
        end_mouseNewPageLDown:
        ADD ESP, 4
        POP ESI
        POP EBP
        POP EBX
        RETN 4
        }
    }

    __declspec(naked)void caller_mouseCustomPageLeftDown() {
        __asm{
        PUSH EAX
        PUSH EDI
        CALL mouseCustomPageLeftDown
        TEST EAX, EAX
        POP EAX
        JE end_mouseNewPageLDown
        JG continue_mouseNewPageLDown
        LEA ECX, DWORD PTR DS:[EAX+0x80]
        RETN
        continue_mouseNewPageLDown:
        ADD DWORD PTR SS:[ESP], 0x152
        RETN
        end_mouseNewPageLDown:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        RETN 4
        }
    }

    __declspec(naked)void caller_mouseCustomPageLeftDown_9() {
        __asm{
        PUSH EAX
        PUSH EDI
        CALL mouseCustomPageLeftDown
        TEST EAX, EAX
        POP EAX
        JE end_mouseNewPageLDown
        JG continue_mouseNewPageLDown
        LEA ECX, DWORD PTR DS:[EAX+0x80]
        RETN
        continue_mouseNewPageLDown:
        ADD DWORD PTR SS:[ESP], 0x149
        RETN
        end_mouseNewPageLDown:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        RETN 4
        }
    }

    __declspec(naked)void caller_mouseCustomPageLeftUp_114() {
        __asm{
        PUSH EBP
        CALL mouseCustomPageLeftUp
        TEST EAX, EAX
        JE end_mouseNewPageLUp
        JG continue_mouseNewPageLUp
        MOV EAX, DWORD PTR DS:[ptWindowStartX]
        MOV EAX, DWORD PTR DS:[EAX]
        RETN
        continue_mouseNewPageLUp:
        ADD DWORD PTR SS:[ESP], 0x17D
        RETN
        end_mouseNewPageLUp:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBX
        MOV ESP, EBP
        POP EBP
        RETN 4
        }
    }

    __declspec(naked)void caller_mouseCustomPageLeftUp_111() {
        __asm{
        PUSH EBP
        CALL mouseCustomPageLeftUp
        TEST EAX, EAX
        JE end_mouseNewPageLUp
        JG continue_mouseNewPageLUp
        MOV EAX, DWORD PTR DS:[ptWindowStartX]
        MOV EAX, DWORD PTR DS:[EAX]
        RETN
        continue_mouseNewPageLUp:
        ADD DWORD PTR SS:[ESP], 0x2C4
        RETN
        end_mouseNewPageLUp:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        ADD ESP, 8
        RETN 4
        }
    }

    __declspec(naked)void caller_mouseCustomPageLeftUp() {
        __asm{
        PUSH EBP
        CALL mouseCustomPageLeftUp
        TEST EAX, EAX
        JE end_mouseNewPageLUp
        JG continue_mouseNewPageLUp
        MOV EAX, DWORD PTR DS:[ptWindowStartX]
        MOV EAX, DWORD PTR DS:[EAX]
        RETN
        continue_mouseNewPageLUp:
        ADD DWORD PTR SS:[ESP], 0x1AE
        RETN
        end_mouseNewPageLUp:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        ADD ESP, 8
        RETN 4
        }
    }

    __declspec(naked)void caller_mouseCustomPageLeftUp_9() {
        __asm{
        PUSH EBP
        CALL mouseCustomPageLeftUp
        TEST EAX, EAX
        JE end_mouseNewPageLUp
        JG continue_mouseNewPageLUp
        MOV EAX, DWORD PTR DS:[ptWindowStartX]
        MOV EAX, DWORD PTR DS:[EAX]
        RETN
        continue_mouseNewPageLUp:
        ADD DWORD PTR SS:[ESP], 0x16A
        RETN
        end_mouseNewPageLUp:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        POP ECX
        RETN 4
        }
    }

    __declspec(naked)void caller_resetSelected_114() {
        __asm{
        CMP ECX, 2
        JNZ NO_RESET
        MOV selectedPage, 0
        NO_RESET:
        POP EAX
        PUSH EBX
        PUSH ESI
        PUSH EDI
        MOV EDI, ECX
        JMP EAX
        }
    }

    __declspec(naked)void caller_resetSelectedPageByToolBar() {
        __asm{
        MOV selectedPage, 0
        CMP EAX, 0x26
        JNZ noJump
        ADD DWORD PTR SS:[ESP], 0x1F
        noJump:
        RETN
        }
    }

    __declspec(naked)void caller_resetSelectedPageByKey() {
        __asm{
        MOV selectedPage, 0
        POP EAX
        PUSH EBP
        XOR EBP, EBP
        CMP EDX, EBP
        JMP EAX
        }
    }

    __declspec(naked)void caller_resetSelectedPage() {
        __asm{
        TEST EAX, EAX
        SETE DL
        JNZ END_resetSelectedPage
        CMP ESI, 2
        JNZ END_resetSelectedPage
        MOV selectedPage, 0
        END_resetSelectedPage:
        RETN
        }
    }

    void Install_NewInterfaces() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_UpdateServer();
        Install_PlugYImagesFiles();
        Install_PlugYTxtFiles();
        Install_InterfaceStats();
        log_msg("Patch D2Client for new custom page interface. (NewInterfaces)\n");
        if (version_D2Client >= V110)
            extraHiddenPage = 1;
        if (selectMainPageOnOpenning) {
            if (version_D2Client >= V114a) {
                mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x55F24 : (version_D2Client == V113d ? 0x0000 : (version_D2Client == V113c ? 0x0000 : (version_D2Client == V112 ? 0x0000 : (version_D2Client == V111b ? 0x0000 : (version_D2Client == V111 ? 0x0000 : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
                memt_byte(0x53, 0xE8);    // CALL caller_resetSelectedPage
                MEMT_REF4(0xF98B5756, caller_resetSelected_114);
                //00455F24  |. 53             PUSH EBX
                //00455F25  |. 56             PUSH ESI
                //00455F26  |. 57             PUSH EDI
                //00455F27  |. 8BF9           MOV EDI,ECX
            } else if (version_D2Client >= V111) {
                //Reset selectedPage variable on opening stats page
                mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x7EC5C : (version_D2Client == V113d ? 0xC41FE : (version_D2Client == V113c ? 0x65F5E : (version_D2Client == V112 ? 0x55E0E : (version_D2Client == V111b ? 0x8F73E : (version_D2Client == V111 ? 0x4B79E : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
                memt_byte(version_D2Client == V114d ? 0xB9 : 0x83, 0xE8);    // CALL caller_resetSelectedPage
                MEMT_REF4(version_D2Client == V114d ? 0x00000002 : 0x1F7426F8, caller_resetSelectedPageByToolBar);
                //6FAFB79E   > 83F8 26        CMP EAX,26
                //6FAFB7A1   . 74 1F          JE SHORT D2Client.6FAFB7C2
                //6FB3F73E   > 83F8 26        CMP EAX,26
                //6FB3F741   . 74 1F          JE SHORT D2Client.6FB3F762
                //6FB05E0E   > 83F8 26        CMP EAX,26
                //6FB05E11   . 74 1F          JE SHORT D2Client.6FB05E32
                //6FB15F5E   > 83F8 26        CMP EAX,26
                //6FB15F61   . 74 1F          JE SHORT D2Client.6FB15F82
                //6FB741FE   > 83F8 26        CMP EAX,26
                //6FB74201   . 74 1F          JE SHORT D2Client.6FB05E32
                //6FB741FE   > 83F8 26        CMP EAX,26
                //6FB74201   . 74 1F          JE SHORT D2Client.6FB74222
                //0047EC5C   > B9 02000000    MOV ECX,2

                mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x0000 : (version_D2Client == V113d ? 0x3E39A : (version_D2Client == V113c ? 0x3C5EA : (version_D2Client == V112 ? 0xA31DA : (version_D2Client == V111b ? 0x6A8FA : (version_D2Client == V111 ? 0x1E55A : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
                memt_byte(0x55, 0xE8);    // CALL caller_resetSelectedPage
                MEMT_REF4(0xD53BED33, caller_resetSelectedPageByKey);
                //6FACE55A   . 55             PUSH EBP
                //6FACE55B   . 33ED           XOR EBP,EBP
                //6FACE55D   . 3BD5           CMP EDX,EBP
                //6FB1A8FA   . 55             PUSH EBP
                //6FB1A8FB   . 33ED           XOR EBP,EBP
                //6FB1A8FD   . 3BD5           CMP EDX,EBP
                //6FB531DA   . 55             PUSH EBP
                //6FB531DB   . 33ED           XOR EBP,EBP
                //6FB531DD   . 3BD5           CMP EDX,EBP
                //6FAEC5EA   . 55             PUSH EBP
                //6FAEC5EB   . 33ED           XOR EBP,EBP
                //6FAEC5ED   . 3BD5           CMP EDX,EBP
                //6FAEE39A   . 55             PUSH EBP
                //6FAEE39B   . 33ED           XOR EBP,EBP
                //6FAEE39D   . 3BD5           CMP EDX,EBP

                //For Toggle fct : (not used for open the stat page)
                //		mem_seek R7(D2Client, 88B58, 87ED8, 83478, A1FBE, 6571E, 8EF8E, 0000);//((DWORD)D2TogglePage+0x218);
                //		memt_byte( 0x3B, 0xE8 );
                //		MEMT_REF4( 0x393974C5, caller_resetSelectedPage_111);
                //		memt_byte( 0x28, 0x90 );	// NOP
                //6FB51FBE  |. 3BC5           CMP EAX,EBP                              ;  Case 2 of switch 6FB51FB8
                //6FB51FC0  |. 74 39          JE SHORT D2Client.6FB51FFB
                //6FB51FC2  |. 3928           CMP DWORD PTR DS:[EAX],EBP
                //6FB1571E  |. 3BC5           CMP EAX,EBP                              ;  Case 2 of switch 6FB15718
                //6FB15720  |. 74 39          JE SHORT D2Client.6FB1575B
                //6FB15722  |. 3928           CMP DWORD PTR DS:[EAX],EBP
                //6FB3EF8E  |. 3BC5           CMP EAX,EBP                              ;  Case 2 of switch 6FB3EF88
                //6FB3EF90  |. 74 39          JE SHORT D2Client.6FB3EFCB
                //6FB3EF92  |. 3928           CMP DWORD PTR DS:[EAX],EBP
            } else {
                //Reset selectedPage variable on opening stats page
                mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x0000 : (version_D2Client == V113d ? 0x0000 : (version_D2Client == V113c ? 0x0000 : (version_D2Client == V112 ? 0x8EF8E : (version_D2Client == V111b ? 0x6571E : (version_D2Client == V111 ? 0xA1FBE : (version_D2Client == V110 ? 0x83478 : (version_D2Client == V109d ? 0x87ED8 : 0x88B58)))))))));//((DWORD)D2TogglePage+0x218);
                memt_byte(0x85, 0xE8);    // CALL caller_resetSelectedPage
                MEMT_REF4(0xC2940FC0, caller_resetSelectedPage);
                //6FB23478  |. 85C0           TEST EAX,EAX
                //6FB2347A  |. 0F94C2         SETE DL
                //FOR 1.11
            }
        }

        // Print custom page
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x57052 : (version_D2Client == V113d ? 0x1D549 : (version_D2Client == V113c ? 0xC3B49 : (version_D2Client == V112 ? 0x902B9 : (version_D2Client == V111b ? 0x66B59 : (version_D2Client == V111 ? 0xA3759 : (version_D2Client == V110 ? 0x81FAB : (version_D2Client == V109d ? 0x86A17 : 0x87697)))))))));
        MEMC_REF4(D2PrintStatsPage, printCustomPage);
        //6FB21FAA   . E8 B1DDFAFF    CALL D2Client.6FACFD60
        //6FB53758   . E8 43F1FDFF    CALL D2Client.6FB328A0
        //6FB16B58  |. E8 C3270200    CALL D2Client.6FB39320
        //6FB402B8  |. E8 C3AFFDFF    CALL D2Client.6FB1B280
        //6FB73B48  |. E8 5393FFFF    CALL D2Client.6FB6CEA0
        //6FACD548  |. E8 F3200A00    CALL D2Client.6FB1B280
        //00457051  |. E8 AA0C0500    CALL Game.004A7D00

        // Don't print Border
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x98636 : (version_D2Client == V113d ? 0x6D2B6 : (version_D2Client == V113c ? 0x271C6 : (version_D2Client == V112 ? 0x82166 : (version_D2Client == V111b ? 0xB5A46 : (version_D2Client == V111 ? 0x2D366 : (version_D2Client == V110 ? 0x5F4C6 : (version_D2Client == V109d ? 0x58EF6 : 0x58EF6)))))))));
        memt_byte(version_D2Client >= V114d ? 0x6A : 0xB9, 0xE8);    // CALL caller_DontPrintBorder
        MEMT_REF4(version_D2Client >= V114d ? 0xB8458D48 : 0x00000012, version_D2Client >= V114d ? caller_DontPrintBorder_114 : version_D2Client >= V111 ? caller_DontPrintBorder_111 : caller_DontPrintBorder);
        //6FAFF4C6   > B9 12000000    MOV ECX,12
        //6FADD366  |. B9 12000000    MOV ECX,12
        //6FB65A46  |. B9 12000000    MOV ECX,12
        //6FB32166  |. B9 12000000    MOV ECX,12
        //6FAD71C6  |. B9 12000000    MOV ECX,12
        //6FB1D2B6  |. B9 12000000    MOV ECX,12
        //00498636  |. 6A 48          PUSH 48
        //00498638  |. 8D45 B8        LEA EAX,DWORD PTR SS:[EBP-48]

        // Manage mouse down (Play sound)
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7731 : (version_D2Client == V113d ? 0xBF4D6 : (version_D2Client == V113c ? 0xBCD36 : (version_D2Client == V112 ? 0x6B116 : (version_D2Client == V111b ? 0x891B6 : (version_D2Client == V111 ? 0x82736 : (version_D2Client == V110 ? 0x312A5 : (version_D2Client == V109d ? 0x2A9CC : 0x2A9DC)))))))));
        memt_byte(0x8D, 0xE8);    // CALL
        MEMT_REF4(0x00008088, version_D2Client == V114d ? caller_mouseCustomPageLeftDown_114 : version_D2Client >= V111 ? caller_mouseCustomPageLeftDown_111 : version_D2Client == V110 ? caller_mouseCustomPageLeftDown : caller_mouseCustomPageLeftDown_9);
        memt_byte(0x00, 0x90);    // NOP
        //6FAD12A5   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
        //6FB32736   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
        //6FB391B6   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
        //6FB1B116   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
        //6FB6CD36   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
        //6FB6F4D6   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
        //004A7731   . 8D88 80000000  LEA ECX,DWORD PTR DS:[EAX+80]

        // Manage mouse up
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA78DA : (version_D2Client == V113d ? 0xC0459 : (version_D2Client == V113c ? 0xBDCB9 : (version_D2Client == V112 ? 0x6C0B9 : (version_D2Client == V111b ? 0x8A159 : (version_D2Client == V111 ? 0x836D9 : (version_D2Client == V110 ? 0x3148D : (version_D2Client == V109d ? 0x2ABAB : 0x2ABBB)))))))));
        memt_byte(0xA1, 0xE8);    // CALL caller_mouseCustomPageLeftUp
        MEMT_REF4(ptWindowStartX, version_D2Client >= V114d ? caller_mouseCustomPageLeftUp_114 : version_D2Client >= V111 ? caller_mouseCustomPageLeftUp_111 : version_D2Client == V110 ? caller_mouseCustomPageLeftUp : caller_mouseCustomPageLeftUp_9);
        //6FAD148D   . A1 48A7BB6F       MOV EAX,DWORD PTR DS:[6FBBA748]
        //6FB336D9   . A1 24BDBC6F       MOV EAX,DWORD PTR DS:[6FBCBD24]
        //6FB3A159   . A1 F8BEBC6F       MOV EAX,DWORD PTR DS:[6FBCBEF8]
        //6FB1C0B9   . A1 28BDBC6F       MOV EAX,DWORD PTR DS:[6FBCBD28]
        //6FB6DCB9   . A1 A0B9BC6F       MOV EAX,DWORD PTR DS:[6FBCB9A0]
        //6FB70459   . A1 54D3BC6F       MOV EAX,DWORD PTR DS:[6FBCD354]
        //004A78DA  |. A1 58287A00    MOV EAX,DWORD PTR DS:[7A2858]

        // open page : 6FB23515  |> 892CB5 A8A6BB6>MOV DWORD PTR DS:[ESI*4+6FBBA6A8],EBP
        //6FB2347D  |. 8914B5 A8A6BB6F   MOV DWORD PTR DS:[ESI*4+6FBBA6A8],EDX

        log_msg("\n");
        isInstalled = true;
    }

}