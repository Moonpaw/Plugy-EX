/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

    Print PlugY version on screen.

=================================================================*/

#include "extraOptions.h"
#include "windowed.h"
#include "common.h"
#include "modifMemory.h"
#include "d2wrapper.h"
#include "d2functions.h"
#include "error.h"
#include "parameters.h"
#include <stdio.h>
#include <VersionInfo.h>

//using namespace std;

namespace PlugY {
    char * versionText = std::string("").data();
    bool active_VersionTextChange = false;
    BYTE modVersionColor = 0;
    bool active_PrintPlugYVersion = true;
    BYTE colorOfPlugYVersion = 4;
    DWORD newTextBoxData[] = {4, 0x237, 0x243, 0xC8, 0x14, 0, 0, 0, 0, 0, 0, 2};//type,x,y,l,h,?,?,?,?,?,?,?(0,257,C8,28)

    void __stdcall printPlugYVersion(void **childrens, DWORD *sgnNumChildren) {
        if (active_Windowed)
            SetWindowedOptions();
        if (active_PrintPlugYVersion) {
            char buf[20];
            void *textbox = D2CreateTextBox(newTextBoxData);
            childrens[*sgnNumChildren] = textbox;
            d2_assert((*sgnNumChildren)++ >= 40, "sgnNumChildren < MAX_CHILDREN", __FILE__, __LINE__);
            sprintf(buf, "PlugY %s", PLUGY_VERSION);
            D2PrintLineOnTextBox(textbox, buf, colorOfPlugYVersion);
        }
    }

    void **childrens;
    DWORD *sgnNumChildren;

    __declspec(naked)void caller_printPlugYVersion114() {
        __asm{
        PUSH sgnNumChildren
        PUSH childrens
        CALL printPlugYVersion
        MOV ECX, 0x115
        RETN
        }
    }

    __declspec(naked)void caller_printPlugYVersion() {
        __asm{
        POP ESI
        PUSH DWORD PTR[ESI+2]
        PUSH DWORD PTR[ESI+9]
        CALL printPlugYVersion
        CALL D2CreateTextBox
        JMP ESI
        }
    }

    void Install_PrintPlugYVersion() {
        static int isInstalled = false;
        if (isInstalled) return;
        log_msg("Patch D2Launch to print PlugY version. (PrintPlugYVersion)\n");

        // Print PlugY version.
        mem_seek(offset_D2Launch + (version_D2Launch == V114d ? 0x33798 : (version_D2Launch == V113d ? 0x10A11 : (version_D2Launch == V113c ? 0x18061 : (version_D2Launch == V112 ? 0x16AF7 : (version_D2Launch == V111b ? 0x178A7 : (version_D2Launch == V111 ? 0x117C7 : (version_D2Launch == V110 ? 0x9639 : (version_D2Launch == V109d ? 0x7F7D : 0x7F5D)))))))));
        if (version_D2Launch == V114d) {
            memt_byte(0xB9, 0xE8);
            MEMT_REF4(0x00000115, caller_printPlugYVersion114);
            childrens = (void **) (offset_Game + 0x379350);
            sgnNumChildren = (DWORD *) (offset_Game + 0x379944);
            //00433798  |. B9 15010000    MOV ECX,115
        } else {
            MEMJ_REF4(D2CreateTextBox, caller_printPlugYVersion);
            //6FA19638  |. E8 1BED0000    CALL <JMP.&D2Win.#10017>
            //6FA517C6  |. E8 6F81FFFF    CALL <JMP.&D2Win.#10147>
            //6FA578A6  |. E8 D71FFFFF    CALL <JMP.&D2Win.#10113>
            //6FA56B1F  |. E8 1A2EFFFF    CALL <JMP.&D2Win.#10098>
            //6FA56AF6  |. E8 432EFFFF    CALL <JMP.&D2Win.#10098>
            //6FA58060  |. E8 ED18FFFF    CALL <JMP.&D2Win.#10098>
            //6FA50A10  |. E8 218FFFFF    CALL <JMP.&D2Win.#10164>
        }
        log_msg("\n");
        isInstalled = true;
    }

/*************************************************************************************/

    void __fastcall versionChange(void *screen, char *text, DWORD color) {
        D2PrintLineOnTextBox(screen, const_cast<char *>(versionText), modVersionColor);
    }

    __declspec(naked)void caller_VersionChange_114() {
        __asm{
        MOV CL, BYTE PTR DS:[modVersionColor]
        MOV BYTE PTR SS:[ESP+4], CL
        MOV EDX, versionText
        MOV ECX, ESI
        RETN
        }
    }

    __declspec(naked)void caller_VersionChange_10() {
        __asm{
        MOV CL, BYTE PTR DS:[modVersionColor]
        MOV BYTE PTR SS:[ESP+4], CL
        MOV EDX, versionText
        MOV ECX, EDI
        RETN
        }
    }

    void Install_VersionChange()// BUG WITH 2MOD if D2Mod started before PlugY ????
    {
        static int isInstalled = false;
        if (isInstalled) return;
        log_msg("Patch D2Launch to print Mod version. (VersionChange)\n");

//6FA18012  |. 8D5424 0C      LEA EDX,DWORD PTR SS:[ESP+C]
//6FA18016  |. 8BCE           MOV ECX,ESI
//6FA18018  |. 6A 00          PUSH 0


        // Print LoD/Mod version.
        if (version_D2Launch >= V114d) {
            mem_seek(offset_D2Launch + (version_D2Launch == V114d ? 0x337EA : (version_D2Launch == V113d ? 0x10AE4 : (version_D2Launch == V113c ? 0x18134 : (version_D2Launch == V112 ? 0x16BCB : (version_D2Launch == V111b ? 0x1797B : (version_D2Launch == V111 ? 0x1189B : (version_D2Launch == V110 ? 0x9723 : (version_D2Launch == V109d ? 0x00000 : 0x00000)))))))));//6FA19721-6FA10000
            memt_byte(0x8D, 0xE8);    // CALL
            MEMT_REF4(0xCE8BC055, caller_VersionChange_114);
            //004337EA  |. 8D55 C0        LEA EDX,DWORD PTR SS:[EBP-40]            ; |
            //004337ED  |. 8BCE           MOV ECX,ESI                              ; |
        } else if (version_D2Launch >= V110) {
            mem_seek(offset_D2Launch + (version_D2Launch == V114d ? 0x337EA : (version_D2Launch == V113d ? 0x10AE4 : (version_D2Launch == V113c ? 0x18134 : (version_D2Launch == V112 ? 0x16BCB : (version_D2Launch == V111b ? 0x1797B : (version_D2Launch == V111 ? 0x1189B : (version_D2Launch == V110 ? 0x9723 : (version_D2Launch == V109d ? 0x00000 : 0x00000)))))))));//6FA19721-6FA10000
            memt_byte(0x8D, 0xE8);    // CALL
            MEMT_REF4(0x8B102454, caller_VersionChange_10);
            memt_byte(0xCF, 0x90);    // NOP
            //6FA19723  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
            //6FA19727  |. 8BCF           MOV ECX,EDI
            //6FA5189B  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
            //6FA5189F  |. 8BCF           MOV ECX,EDI
            //6FA5797B  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
            //6FA5797F  |. 8BCF           MOV ECX,EDI
            //6FA56BCB  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
            //6FA56BCF  |. 8BCF           MOV ECX,EDI
            //6FA58134  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
            //6FA58138  |. 8BCF           MOV ECX,EDI
            //6FA50AE4  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
            //6FA50AE8  |. 8BCF           MOV ECX,EDI
        } else {
            mem_seek(offset_D2Launch + (version_D2Launch == V114d ? 0x00000 : (version_D2Launch == V113d ? 0x10AEB : (version_D2Launch == V113c ? 0x1813B : (version_D2Launch == V112 ? 0x16BD2 : (version_D2Launch == V111b ? 0x17982 : (version_D2Launch == V111 ? 0x118A2 : (version_D2Launch == V110 ? 0x972A : (version_D2Launch == V109d ? 0x803B : 0x801B)))))))));
            MEMJ_REF4(D2PrintLineOnTextBox, versionChange);
            //6FA19729  |. E8 88EB0000    CALL <JMP.&D2Win.#10046>
            //6FA518A1  |. E8 267FFFFF    CALL <JMP.&D2Win.#10061>
            //6FA57981  |. E8 781EFFFF    CALL <JMP.&D2Win.#10075>
            //6FA56BD1  |. E8 EA2CFFFF    CALL <JMP.&D2Win.#10015>
            //6FA5813A  |. E8 8F17FFFF    CALL <JMP.&D2Win.#10022>
            //6FA50AEA  |. E8 DF8CFFFF    CALL <JMP.&D2Win.#10051>
        }
        log_msg("\n");
        isInstalled = true;
    }


}