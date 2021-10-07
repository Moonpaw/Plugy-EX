/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Interface functions

=================================================================*/

#include "statsPoints.h"
#include "plugYFiles.h"        // Install_PlugYImagesFiles()
#include "newInterfaces.h"
#include "common.h"
#include <stdio.h>
#include "d2functions.h"
#include "error.h"
#include "LocalizedStrings.h"
#include <updatingConst.h>
#include <d2constants.h>
#include "modifMemory.h"

namespace PlugY {
    static struct {
        union {
            DWORD all;
            struct {
                DWORD previousPage: 1;
                DWORD nextPage: 1;
            };
        };
    } isDownBtn;
#define    getXPreviousPageBtn()        RX(0x95)//0x70 //19
#define    getLPreviousPageBtn()        32
#define    getYPreviousPageBtn()        RY(0x50)//40
#define    getHPreviousPageBtn()        32
#define isOnPreviousPageBtn(x, y)    isOnRect(x, y, getXPreviousPageBtn(), getYPreviousPageBtn(), getLPreviousPageBtn(), getHPreviousPageBtn())
#define    getXNextPageBtn()        RX(D2GetResolution()?0xBA:0xBA)//0x43:0x8A
#define    getLNextPageBtn()        32
#define    getYNextPageBtn()        RY(D2GetResolution()?0x50:0x50)//40:0x70
#define    getHNextPageBtn()        32
#define isOnNextPageBtn(x, y)    isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())

    void __stdcall printStatsPageBtns() {
        if (!active_newInterfaces || !D2isLODGame()) return;
        DWORD mx = D2GetMouseX();
        DWORD my = D2GetMouseY();
        sDrawImageInfo data;
        ZeroMemory(&data, sizeof(data));

        /*if (printBackgroundOnMainPage && D2GetResolution())
        {
            setImage(&data, statsBackgroundImages);
            setFrame(&data, 1);
            D2PrintImage(&data, getXPreviousPageBtn() - 7, getYPreviousPageBtn() + 8, -1, 5, 0);
        }*/

        setImage(&data, D2LoadBuySelBtn());
        if (D2GetResolution()) {
            setFrame(&data, 12 + isDownBtn.previousPage);
            D2PrintImage(&data, getXPreviousPageBtn(), getYPreviousPageBtn(), -1, 5, 0);
        }
        setFrame(&data, 14 + isDownBtn.nextPage);
        D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);
        D2SetFont(1);
        if (D2GetResolution() && isOnPreviousPageBtn(mx, my))    //print popup "previous page"
        {
            auto lpText = const_cast<LPWSTR>(getLocalString(STR_PREVIOUS_PAGE));
            D2PrintPopup(lpText, getXPreviousPageBtn() + getLPreviousPageBtn() / 2, getYPreviousPageBtn() - getHPreviousPageBtn(), WHITE, 1);
        } else if (isOnNextPageBtn(mx, my)) {
            auto lpText =  const_cast<LPWSTR>(getLocalString(STR_NEXT_PAGE));
            D2PrintPopup(lpText, getXNextPageBtn() + getLNextPageBtn() / 2, getYNextPageBtn() - getHNextPageBtn(), WHITE, 1);
        }
    }

    Unit *__stdcall statsPageMouseDown(sWinMessage *msg) {
        Unit *ptChar = D2GetClientPlayer();
        if (!active_newInterfaces || !D2isLODGame()) return ptChar;
        if (D2GetResolution() && isOnPreviousPageBtn(msg->x, msg->y)) {
            log_msg("push down left button previous page\n");
            isDownBtn.previousPage = 1;
            D2PlaySound(4, 0, 0, 0, 0);
            freeMessage(msg);
            return NULL;
        } else if (isOnNextPageBtn(msg->x, msg->y)) {
            log_msg("push down left button next page\n");
            isDownBtn.nextPage = 1;
            D2PlaySound(4, 0, 0, 0, 0);
            freeMessage(msg);
            return NULL;
        }
        return ptChar;
    }

    Unit *__stdcall statsPageMouseUp(sWinMessage *msg) {
        Unit *ptChar = D2GetClientPlayer();
        if (!active_newInterfaces || !D2isLODGame()) return ptChar;
        if (D2GetResolution() && isOnPreviousPageBtn(msg->x, msg->y)) {
            log_msg("push up left button previous page\n");
            if (isDownBtn.previousPage) {
                GoPreviousStatPage();
                log_msg("previous page press\n");
                isDownBtn.all = 0;
                freeMessage(msg);
                return NULL;
            }
        } else if (isOnNextPageBtn(msg->x, msg->y)) {
            log_msg("push up left button next page\n");
            if (isDownBtn.nextPage) {
                GoNextStatPage();
                log_msg("next page press\n");
                isDownBtn.all = 0;
                freeMessage(msg);
                return NULL;
            }
        }
        isDownBtn.all = 0;
        return ptChar;
    }

    __declspec(naked)void caller_printStatsPageBtns_114() {
        __asm{
        CALL printStatsPageBtns
        POP EDI
        POP ESI
        POP EBX
        MOV ESP, EBP
        POP EBP
        RETN
        }
    }

    __declspec(naked)void caller_printStatsPageBtns_111() {
        __asm{
        CALL printStatsPageBtns
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        ADD ESP, 0x370
        RETN
        }
    }

    __declspec(naked)void caller_printStatsPageBtns() {
        __asm{
        CALL printStatsPageBtns
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        ADD ESP, 0x3B0
        RETN
        }
    }

    __declspec(naked)void caller_printStatsPageBtns_9() {
        __asm{
        CALL printStatsPageBtns
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        ADD ESP, 0x374
        RETN
        }
    }

    __declspec(naked)void caller_statsPageMouseDown_114() {
        __asm{
        PUSH DWORD PTR SS:[ESP+0x18]
        CALL statsPageMouseDown
        TEST EAX, EAX
        JE fin_statsPageMouseDown
        JMP D2GetClientPlayer
        fin_statsPageMouseDown:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBX
        POP EBP
        RETN 4
        }
    }

    __declspec(naked)void caller_statsPageMouseDown_111() {
        __asm{
        PUSH DWORD PTR SS:[ESP+0x20]
        CALL statsPageMouseDown
        TEST EAX, EAX
        JE fin_statsPageMouseDown
        RETN
        fin_statsPageMouseDown:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        RETN 4
        }
    }

    __declspec(naked)void caller_statsPageMouseDown() {
        __asm{
        PUSH DWORD PTR SS:[ESP+0x18]
        CALL statsPageMouseDown
        TEST EAX, EAX
        JE fin_statsPageMouseDown
        RETN
        fin_statsPageMouseDown:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        RETN 4
        }
    }

    __declspec(naked)void caller_statsPageMouseUp_114() {
        __asm{
        PUSH DWORD PTR SS:[EBP+0x8]
        CALL statsPageMouseUp
        TEST EAX, EAX
        JE fin_statsPageMouseUp
        JMP D2GetClientPlayer
        fin_statsPageMouseUp:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBX
        MOV ESP, EBP
        POP EBP
        RETN 4
        }
    }

    __declspec(naked)void caller_statsPageMouseUp() {
        __asm{
        PUSH EBP
        CALL statsPageMouseUp
        TEST EAX, EAX
        JE fin_statsPageMouseUp
        RETN
        fin_statsPageMouseUp:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        ADD ESP, 8
        RETN 4
        }
    }

    __declspec(naked)void caller_statsPageMouseUp_9() {
        __asm{
        PUSH EBP
        CALL statsPageMouseUp
        TEST EAX, EAX
        JE fin_statsPageMouseUp
        RETN
        fin_statsPageMouseUp:
        ADD ESP, 4
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        POP ECX
        RETN 4
        }
    }

    void Install_InterfaceStats() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_PlugYImagesFiles();
        log_msg("Patch D2Client for stats interface. (InterfaceStats)\n");

        // Print new buttons images
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA8949 : (version_D2Client == V113d ? 0xC03B6 : (version_D2Client == V113c ? 0xBDC16 : (version_D2Client == V112 ? 0x6C016 : (version_D2Client == V111b ? 0x8A0B6 : (version_D2Client == V111 ? 0x83636 : (version_D2Client == V110 ? 0x30F86 : (version_D2Client == V109d ? 0x2A7AE : 0x2A7BE)))))))));
        memt_byte(0x5F, 0xE9);    // JMP
        MEMT_REF4(version_D2Client >= V114d ? 0xE58B5B5E : 0x815B5D5E, version_D2Client >= V114d ? caller_printStatsPageBtns_114 : version_D2Client >= V111 ? caller_printStatsPageBtns_111 : version_D2Client == V110 ? caller_printStatsPageBtns : caller_printStatsPageBtns_9);
        //6FAD0F86   . 5F                   POP EDI
        //6FAD0F87   . 5E                   POP ESI
        //6FAD0F88   . 5D                   POP EBP
        //6FAD0F89   . 5B                   POP EBX
        //6FAD0F8A   . 81C4 B0030000        ADD ESP,3B0
        //6FAD0F90   . C3                   RETN
        //6FB33636   . 5F             POP EDI
        //6FB33637   . 5E             POP ESI
        //6FB33638   . 5D             POP EBP
        //6FB33639   . 5B             POP EBX
        //6FB3363A   . 81C4 70030000  ADD ESP,370
        //6FB33640   . C3             RETN
        //6FB3A0B6   . 5F             POP EDI
        //6FB3A0B7   . 5E             POP ESI
        //6FB3A0B8   . 5D             POP EBP
        //6FB3A0B9   . 5B             POP EBX
        //6FB3A0BA   . 81C4 70030000  ADD ESP,370
        //6FB3A0C0   . C3             RETN
        //6FB1C016   . 5F             POP EDI
        //6FB1C017   . 5E             POP ESI
        //6FB1C018   . 5D             POP EBP
        //6FB1C019   . 5B             POP EBX
        //6FB1C01A   . 81C4 70030000  ADD ESP,370
        //6FB1C020   . C3             RETN
        //6FB6DC16  |. 5F             POP EDI
        //6FB6DC17  |. 5E             POP ESI
        //6FB6DC18  |. 5D             POP EBP
        //6FB6DC19  |. 5B             POP EBX
        //6FB6DC1A  |. 81C4 70030000  ADD ESP,370
        //6FB6DC20  \. C3             RETN
        //6FB703B6  |. 5F             POP EDI
        //6FB703B7  |. 5E             POP ESI
        //6FB703B8  |. 5D             POP EBP
        //6FB703B9  |. 5B             POP EBX
        //6FB703BA  |. 81C4 70030000  ADD ESP,370
        //6FB703C0  \. C3             RETN
        //004A8949   . 5F             POP EDI
        //004A894A   . 5E             POP ESI
        //004A894B   . 5B             POP EBX
        //004A894C   . 8BE5           MOV ESP,EBP

        if (version_D2Client >= V114d) {
            // Manage mouse down (Play sound)
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA77D4 : (version_D2Client == V113d ? 0xBF568 : (version_D2Client == V113c ? 0xBCDC8 : (version_D2Client == V112 ? 0x6B1A8 : (version_D2Client == V111b ? 0x89248 : (version_D2Client == V111 ? 0x827C8 : (version_D2Client == V110 ? 0x3133D : (version_D2Client == V109d ? 0x2AA5D : 0x2AA6D)))))))));
            MEMC_REF4(D2GetClientPlayer, caller_statsPageMouseDown_114);
            //004A77D3   . E8 F8C5FBFF    CALL Game.00463DD0

            // Manage mouse up
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7963 : (version_D2Client == V113d ? 0xC05D3 : (version_D2Client == V113c ? 0xBDE33 : (version_D2Client == V112 ? 0x6C233 : (version_D2Client == V111b ? 0x8A2D3 : (version_D2Client == V111 ? 0x83853 : (version_D2Client == V110 ? 0x3151A : (version_D2Client == V109d ? 0x2AC33 : 0x2AC43)))))))));
            MEMC_REF4(D2GetClientPlayer, caller_statsPageMouseUp_114);
            //004A7962  |. E8 69C4FBFF    CALL Game.00463DD0
        } else if (version_D2Client >= V111) {
            // Manage mouse down (Play sound)
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA77D4 : (version_D2Client == V113d ? 0xBF568 : (version_D2Client == V113c ? 0xBCDC8 : (version_D2Client == V112 ? 0x6B1A8 : (version_D2Client == V111b ? 0x89248 : (version_D2Client == V111 ? 0x827C8 : (version_D2Client == V110 ? 0x3133D : (version_D2Client == V109d ? 0x2AA5D : 0x2AA6D)))))))));
            memt_byte(0xA1, 0xE8);
            MEMT_REF4(ptptClientChar, caller_statsPageMouseDown);
            //6FB327C8   . A1 F0C4BC6F    MOV EAX,DWORD PTR DS:[6FBCC4F0]
            //6FB39248   . A1 E0C1BC6F    MOV EAX,DWORD PTR DS:[6FBCC1E0]
            //6FB1B1A8   . A1 D0C3BC6F    MOV EAX,DWORD PTR DS:[6FBCC3D0]
            //6FB6CDC8   . A1 FCBBBC6F    MOV EAX,DWORD PTR DS:[6FBCBBFC]
            //6FB6F568   . A1 50D0BC6F    MOV EAX,DWORD PTR DS:[6FBCD050]

            // Manage mouse up
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7963 : (version_D2Client == V113d ? 0xC05D3 : (version_D2Client == V113c ? 0xBDE33 : (version_D2Client == V112 ? 0x6C233 : (version_D2Client == V111b ? 0x8A2D3 : (version_D2Client == V111 ? 0x83853 : (version_D2Client == V110 ? 0x3151A : (version_D2Client == V109d ? 0x2AC33 : 0x2AC43)))))))));
            memt_byte(0xA1, 0xE8);
            MEMT_REF4(ptptClientChar, caller_statsPageMouseUp);
            //6FB33853   . A1 F0C4BC6F    MOV EAX,DWORD PTR DS:[6FBCC4F0]
            //6FB3A2D3   . A1 E0C1BC6F    MOV EAX,DWORD PTR DS:[6FBCC1E0]
            //6FB1C233   . A1 D0C3BC6F    MOV EAX,DWORD PTR DS:[6FBCC3D0]
            //6FB6DE33   . A1 FCBBBC6F    MOV EAX,DWORD PTR DS:[6FBCBBFC]
            //6FB705D3   . A1 50D0BC6F    MOV EAX,DWORD PTR DS:[6FBCD050]
        } else {
            // Manage mouse down (Play sound)
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA77D4 : (version_D2Client == V113d ? 0xBF568 : (version_D2Client == V113c ? 0xBCDC8 : (version_D2Client == V112 ? 0x6B1A8 : (version_D2Client == V111b ? 0x89248 : (version_D2Client == V111 ? 0x827C8 : (version_D2Client == V110 ? 0x3133D : (version_D2Client == V109d ? 0x2AA5D : 0x2AA6D)))))))));
            MEMC_REF4(D2GetClientPlayer, caller_statsPageMouseDown);
            //6FAD133C   . E8 8F700500    CALL D2Client.6FB283D0

            // Manage mouse up
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xA7963 : (version_D2Client == V113d ? 0xC05D3 : (version_D2Client == V113c ? 0xBDE33 : (version_D2Client == V112 ? 0x6C233 : (version_D2Client == V111b ? 0x8A2D3 : (version_D2Client == V111 ? 0x83853 : (version_D2Client == V110 ? 0x3151A : (version_D2Client == V109d ? 0x2AC33 : 0x2AC43)))))))));
            MEMC_REF4(D2GetClientPlayer, version_D2Client == V110 ? caller_statsPageMouseUp : caller_statsPageMouseUp_9);//0x00056EB2
            //6FAD1519   . E8 B26E0500    CALL D2Client.6FB283D0
        }
        log_msg("\n");
        isInstalled = true;
    }

}