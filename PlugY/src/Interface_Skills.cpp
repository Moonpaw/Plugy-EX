/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Interface functions

=================================================================*/

#include "updateServer.h"    // Install_UpdateServer()
#include "plugYFiles.h"        // Install_PlugYImagesFiles()
#include "skillsPoints.h"
#include "common.h"
#include <stdio.h>
#include "d2functions.h"
#include "LocalizedStrings.h"
#include "globalVariable.h"
#include "error.h"
#include <updatingConst.h>
#include "modifMemory.h"

namespace PlugY {
    using namespace Commons;
    int posXUnassignSkillBtn = -1;
    int posYUnassignSkillBtn = -1;
    DWORD btnSkillIsDown = 0;

    DWORD getXSkillBtn() { return RX(posXUnassignSkillBtn < 0 ? 0x243 : posXUnassignSkillBtn); }

#define    getLSkillBtn()            32

    DWORD getYSkillBtn() {
        return RY(posYUnassignSkillBtn < 0 ? 0x1B1 : posYUnassignSkillBtn);
    }

#define    getHSkillBtn()            32
#define isOnButtonUnassignSkill(x, y) isOnRect(x, y, getXSkillBtn(), getYSkillBtn(), getLSkillBtn(), getHSkillBtn())

    void __stdcall printSkillsPageBtns() {
        if (active_SkillsPoints && !onRealm && D2isLODGame()) {
            sDrawImageInfo data;
            ZeroMemory(&data, sizeof(data));
            setImage(&data, unassignSkillsBtnImages);
            setFrame(&data, btnSkillIsDown);
            D2PrintImage(&data, getXSkillBtn(), getYSkillBtn(), -1, 5, 0);
            if (isOnButtonUnassignSkill(D2GetMouseX(), D2GetMouseY())) {
                auto popupText = const_cast<LPWSTR>(getLocalString(STR_SKILLS_UNASSIGN));
                D2PrintPopup(popupText, getXSkillBtn() + getLSkillBtn() / 2, getYSkillBtn() - getHSkillBtn(), 0, 1);
            }
        }
    }

    Unit *__stdcall skillsPageMouseDown(sWinMessage *msg) {
        Unit *ptChar = D2GetClientPlayer();
        if (active_SkillsPoints && !onRealm && D2isLODGame() && isOnButtonUnassignSkill(D2GetMouseX(), D2GetMouseY())) {
            log_msg("push down left button unassign skill\n");
            btnSkillIsDown = 1;
            D2PlaySound(4, 0, 0, 0, 0);
            freeMessage(msg);
            return NULL;
        }
        return ptChar;
    }

    void __stdcall skillsPageMouseUp() {
        if (active_SkillsPoints && !onRealm && D2isLODGame() && isOnButtonUnassignSkill(D2GetMouseX(), D2GetMouseY())) {
            log_msg("push up left button unassign skill\n");
            if (btnSkillIsDown)
                updateServer(US_UNASSIGN_SKILLS);
        }
        btnSkillIsDown = 0;
    }

    __declspec(naked)void caller_printSkillsPageBtns_111() {
        __asm{
        CALL printSkillsPageBtns
        POP EDI
        POP ESI
        POP EBX
        RETN
        }
    }

    __declspec(naked)void caller_printSkillsPageBtns() {
        __asm{
        CALL printSkillsPageBtns
        POP EDI
        POP ESI
        POP EBP
        POP EBX
        ADD ESP, 0x48
        RETN
        }
    }

    __declspec(naked)void caller_DontPrintSkillPointsRemaining_114() {
        __asm{
        MOV AL, BYTE PTR DS:[onRealm]
        TEST AL, AL
        JNZ dontPrint
        ADD DWORD PTR SS:[ESP], 0x97
        RETN
        dontPrint:
        MOV ECX, 0x1083
        RETN
        }
    }

    __declspec(naked)void caller_DontPrintSkillPointsRemaining_111() {
        __asm{
        MOV AL, BYTE PTR DS:[onRealm]
        TEST AL, AL
        JNZ dontPrint
        ADD DWORD PTR SS:[ESP], 0xF2
        RETN
        dontPrint:
        MOV ECX, 0x1083
        RETN
        }
    }

    __declspec(naked)void caller_DontPrintSkillPointsRemaining() {
        __asm{
        MOV AL, BYTE PTR DS:[onRealm]
        TEST AL, AL
        JNZ dontPrint
        ADD DWORD PTR SS:[ESP], 0x9D
        RETN
        dontPrint:
        MOV ECX, 0x1083
        RETN
        }
    }

    __declspec(naked)void caller_skillsPageMouseDown_114() {
        __asm{
        PUSH ESI
        CALL skillsPageMouseDown
        RETN
        }
    }

    __declspec(naked)void caller_skillsPageMouseDown_111() {
        __asm{
        PUSH EBP
        CALL skillsPageMouseDown
        RETN
        }
    }

    __declspec(naked)void caller_skillsPageMouseDown() {
        __asm{
        PUSH EBX
        CALL skillsPageMouseDown
        RETN
        }
    }

    __declspec(naked)void caller_skillsPageMouseUp() {
        __asm{
        CALL skillsPageMouseUp
        JMP D2FreeWinMessage
        }
    }

    void Install_InterfaceSkills() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_UpdateServer();
        Install_PlugYImagesFiles();
        log_msg("Patch D2Client for skills interface. (InterfaceSkills)\n");

        // Print new buttons images
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xAB7A5 : (version_D2Client == V113d ? 0x2F380 : (version_D2Client == V113c ? 0x77F20 : (version_D2Client == V112 ? 0x7F320 : (version_D2Client == V111b ? 0x8A9C0 : (version_D2Client == V111 ? 0x16190 : (version_D2Client == V110 ? 0x77073 : (version_D2Client == V109d ? 0x7AC20 : 0x7AC20)))))))));
        memt_byte(0x5F, 0xE9);    // JMP caller_printBtns
        if (version_D2Client >= V111) {
            MEMT_REF4(0xCCC35B5E, caller_printSkillsPageBtns_111);
            //6FAC6190   5F               POP EDI
            //6FAC6191   5E               POP ESI
            //6FAC6192   5B               POP EBX
            //6FAC6193   C3               RETN
            //6FAC6194   CC               INT3
            //6FB3A9C0  |> 5F             POP EDI
            //6FB3A9C1  |. 5E             POP ESI
            //6FB3A9C2  |. 5B             POP EBX
            //6FB3A9C3  \. C3             RETN
            //6FB3A9C4     CC             INT3
            //6FB2F320  |> 5F             POP EDI
            //6FB2F321  |. 5E             POP ESI
            //6FB2F322  |. 5B             POP EBX
            //6FB2F323  \. C3             RETN
            //6FB2F324     CC             INT3
            //6FB27F20  |> 5F             POP EDI
            //6FB27F21  |. 5E             POP ESI
            //6FB27F22  |. 5B             POP EBX
            //6FB27F23  \. C3             RETN
            //6FB27F24     CC             INT3
            //6FADF380  |> 5F             POP EDI
            //6FADF381  |. 5E             POP ESI
            //6FADF382  |. 5B             POP EBX
            //6FADF383  \. C3             RETN
            //6FADF384     CC             INT3
            //004AB7A5  |> 5F             POP EDI
            //004AB7A6  |. 5E             POP ESI
            //004AB7A7  |. 5B             POP EBX
            //004AB7A8  \. C3             RETN
            //004AB7A9     CC             INT3
        } else {
            MEMT_REF4(0x835B5D5E, caller_printSkillsPageBtns);
            memt_byte(0xC4, 0x90);    // NOP
            memt_byte(0x48, 0x90);    // NOP
            memt_byte(0xC3, 0x90);    // NOP
            //6FB17073  |. 5F             POP EDI
            //6FB17074  |. 5E             POP ESI
            //6FB17075  |. 5D             POP EBP
            //6FB17076  |. 5B             POP EBX
            //6FB17077  |. 83C4 48        ADD ESP,48
            //6FB1707A  \. C3             RETN
        }
        if (posXUnassignSkillBtn == -1 && posYUnassignSkillBtn == -1) {
            // Don't print "Skill Points Remaining"
            mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xAACE0 : (version_D2Client == V113d ? 0x2F7E4 : (version_D2Client == V113c ? 0x78334 : (version_D2Client == V112 ? 0x7ECF4 : (version_D2Client == V111b ? 0x8AC74 : (version_D2Client == V111 ? 0x16294 : (version_D2Client == V110 ? 0x77080 : (version_D2Client == V109d ? 0x7AC30 : 0x7AC30)))))))));
            memt_byte(0xB9, 0xE8);
            MEMT_REF4(0x00001083, version_D2Client >= V114d ? caller_DontPrintSkillPointsRemaining_114 : version_D2Client >= V111 ? caller_DontPrintSkillPointsRemaining_111 : caller_DontPrintSkillPointsRemaining);
            //6FB17080  /$ B9 83100000    MOV ECX,1083
            //6FAC6294  |. B9 83100000    MOV ECX,1083
            //6FB3AC74  |. B9 83100000    MOV ECX,1083
            //6FB2ECF4  |. B9 83100000    MOV ECX,1083
            //6FB28334  |. B9 83100000    MOV ECX,1083
            //6FADF7E4  |. B9 83100000    MOV ECX,1083
            //004AACE0  /$ B9 83100000    MOV ECX,1083
        }

        // Manage mouse down (Play sound)
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xABC1A : (version_D2Client == V113d ? 0x31112 : (version_D2Client == V113c ? 0x79C62 : (version_D2Client == V112 ? 0x808B2 : (version_D2Client == V111b ? 0x8C6E2 : (version_D2Client == V111 ? 0x17BC2 : (version_D2Client == V110 ? 0x780E4 : (version_D2Client == V109d ? 0x7BBD1 : 0x7BBD1)))))))));
        memt_byte(0xC7, 0xE8);    // CALL caller_skillsPageMouseDown
        MEMT_REF4(version_D2Client >= V114d ? 0x00001846 : version_D2Client >= V111 ? 0x00001845 : 0x00001843, version_D2Client == V114d ? caller_skillsPageMouseDown_114 : version_D2Client >= V111 ? caller_skillsPageMouseDown_111 : caller_skillsPageMouseDown);
        memt_byte(0x00, 0x90);    // NOP
        memt_byte(0x00, 0x90);    // NOP
        //6FB180E4   > C743 18 00000000     MOV DWORD PTR DS:[EBX+18],0
        //6FAC7BC2   > C745 18 00000000     MOV DWORD PTR SS:[EBP+18],0
        //6FB3C6E2   > C745 18 00000000     MOV DWORD PTR SS:[EBP+18],0
        //6FB308B2   > C745 18 00000000     MOV DWORD PTR SS:[EBP+18],0
        //6FB29C62   > C745 18 00000000     MOV DWORD PTR SS:[EBP+18],0
        //6FAE1112   > C745 18 00000000     MOV DWORD PTR SS:[EBP+18],0
        //004ABC1A  |> C746 18 00000000     MOV DWORD PTR DS:[ESI+18],0

        // Manage mouse up
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0xABC96 : (version_D2Client == V113d ? 0x30AA8 : (version_D2Client == V113c ? 0x795F8 : (version_D2Client == V112 ? 0x80248 : (version_D2Client == V111b ? 0x8C078 : (version_D2Client == V111 ? 0x17558 : (version_D2Client == V110 ? 0x78466 : (version_D2Client == V109d ? 0x7BC40 : 0x7BC40)))))))));
        MEMJ_REF4(D2FreeWinMessage, caller_skillsPageMouseUp);//0xFFF93B0A
        //6FB18465   . E8 C07D0400    CALL <JMP.&Storm.#511>
        //6FAC7557   .^E9 4248FFFF    JMP <JMP.&Storm.#511>
        //6FB3C077   .^E9 16FDF7FF    JMP <JMP.&Storm.#511>
        //6FB30247   .^E9 2CBCF8FF    JMP <JMP.&Storm.#511>
        //6FB295F7   .^E9 8828F9FF    JMP <JMP.&Storm.#511>
        //6FAE0AA7   .^E9 E0B2FDFF    JMP <JMP.&Storm.#511>
        //004ABC95  |. E8 F645F7FF    CALL Game.00420290

        log_msg("\n");
        isInstalled = true;
    }
}
