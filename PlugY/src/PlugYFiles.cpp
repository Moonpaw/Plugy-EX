/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Adding custom data.
	Save and load infinity & shared Stash

=================================================================*/

#include "plugYFiles.h"
#include "common.h"
#include <stdio.h>
#include "d2functions.h"
#include "error.h"
#include "parameters.h"
#include "modifMemory.h"

namespace PlugY {
//#include "newInterfaces.h"
    extern bool active_SkillsPoints, active_StatsPoints, active_newInterfaces, active_multiPageStash, active_sharedGold;
    void *unassignSkillsBtnImages = NULL;
    void *unassignStatsBtnImages = NULL;
    void *stashBtnsImages = NULL;
    void *newStatsInterfaceImages = NULL;
    void *statsBackgroundImages = NULL;
    void *sharedGoldBtnsImages = NULL;


//void* lookupItemStatCost = NULL;


    DWORD __stdcall isModFile(char *filename) {
        if (strstr(filename, modDataDirectory.c_str())) {
            log_msg("Load custom file : %s\n", filename);
            if ((GetFileAttributesA(filename) & 0x10) == 0)
                return true;
            char fileTemp[0x104];
            strcpy(fileTemp, filename);
            D2FogGetInstallPath(filename, 0x104 - strlen(filename));
            strcat(filename, fileTemp);
            log_msg("Load custom file full path : %s\n", filename);
            if ((GetFileAttributesA(filename) & 0x10) == 0)
                return true;
        }
        return false;
    }

    DWORD __stdcall isModFile_114(char *filename) {
        if (strstr(filename, modDataDirectory.c_str())) {
            log_msg("Load custom file : %s\n", filename);
            if ((GetFileAttributesA(filename) & 0x10) == 0)
                return true;
        }
        return false;
    }

    __declspec(naked)void caller_isModFile() {
        __asm{
        TEST ESI, ESI
        JNZ ISNOTMODDATA
        MOV EBP, DWORD PTR SS:[ESP+0x140]
        PUSH EBP
        CALL isModFile
        TEST EAX, EAX
        JE ISNOTMODDATA
        MOV BL, BYTE PTR SS:[ESP+0x144]
        POP EAX
        POP EAX
        MOV EAX, D2StormMPQOpenFile
        ADD EAX, 0x9A
        JMP EAX
        ISNOTMODDATA:
        JMP DWORD PTR CS:[LeaveCriticalSection]
        }
    }

    __declspec(naked)void caller_isModFile_111() {
        __asm{
        TEST EDI, EDI
        JNZ ISNOTMODDATA
        MOV ESI, DWORD PTR SS:[ESP+0x130]
        PUSH ESI
        CALL isModFile
        TEST EAX, EAX
        JE ISNOTMODDATA
        MOV BL, BYTE PTR SS:[ESP+0x134]
        POP EAX
        POP EAX
        MOV EAX, D2StormMPQOpenFile
        ADD EAX, 0xBD
        MOV EBP, GetFileAttributesA
        JMP EAX
        ISNOTMODDATA:
        JMP DWORD PTR CS:[LeaveCriticalSection]
        }
    }

/*
FCT_ASM ( caller_isModFile_114 )
	TEST ESI,ESI
	JNZ ISNOTMODDATA
	MOV ESI, DWORD PTR SS:[ESP+0x130]
	PUSH ESI
	CALL isModFile
	TEST EAX,EAX
	JE ISNOTMODDATA
	MOV BL, BYTE PTR SS:[ESP+0x134]
	POP EAX
	POP EAX
	MOV EAX,D2StormMPQOpenFile
	ADD EAX,0x93
	MOV EBP,GetFileAttributesA
	JMP EAX
ISNOTMODDATA:
	JMP DWORD PTR CS:[LeaveCriticalSection]
}}
*/

    __declspec(naked)void caller_isModFile_114() {
        __asm{
        PUSH EDX
        PUSH EBX
        CALL isModFile_114
        POP EDX
        TEST EAX, EAX
        JE ISNOTMODDATA
        MOV EDX, 1 // Active -direct command
        ISNOTMODDATA:
        LEA EAX, DWORD PTR SS:[EBP-0x108]
        RETN
        }
    }

    void Install_PlugYFiles() {
        static int isInstalled = false;
        if (isInstalled) return;
        log_msg("Patch Storm to found custom file. (PlugYFiles)\n");

        // Try in Diablo II\PlugY\ if file not found
        mem_seek(offset_Storm + (version_Storm == V114d ? 0x19369 : (version_Storm == V113d ? 0x2DA79 : (version_Storm == V113c ? 0x28D89 : (version_Storm == V112 ? 0x121E9 : (version_Storm == V111b ? 0x14259 : (version_Storm == V111 ? 0x2CC69 : (version_Storm == V110 ? 0x18677 : (version_Storm == V109d ? 0x19296 : 0x192C6)))))))));//( (DWORD)D2Storm268 + V7(Storm, 01A8, 01A8, 01AB, 0429, 0429, 0429, 0000) );
        if (version_Storm >= V114a) {
            memt_byte(0x8D, 0x90); // NOP
            memt_byte(0x85, 0xE8); // CALL
            MEMT_REF4(0xFFFFFEF8, caller_isModFile_114);
            //00419369  |. 8D85 F8FEFFFF  LEA EAX,DWORD PTR SS:[EBP-108]
        } else {
            memt_byte(0xFF, 0x90); // NOP
            memt_byte(0x15, 0xE8); // CALL
            MEMD_REF4(LeaveCriticalSection, version_Storm >= V114a ? caller_isModFile_114 : version_Storm >= V111 ? caller_isModFile_111 : caller_isModFile);
            //6FFC8677  |. FF15 F411FE6F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
            //6FC1CC69  |. FF15 3832C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
            //6FC04259  |. FF15 3832C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
            //6FC021E9  |. FF15 4432C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
            //6FC18D89  |. FF15 5832C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
            //6FC1DA79  |. FF15 3C32C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
            //0041BC81  |. FF15 14C26C00  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
        }
        log_msg("\n");
        isInstalled = true;
    }
//6FFC7EF0 >/$ 8B4C24 10      MOV ECX,DWORD PTR SS:[ESP+10]

/****************************************************************************************************/


    void loadImagesFile(void **images, const char *name) {
        if (!images || !name) return;
        if (!*images) {
            char buffer[MAX_PATH];
            sprintf(buffer, "%s\\%s", modDataDirectory.c_str(), name);
            log_msg("Images file to load : %s\n", buffer);
            *images = D2LoadImage(buffer, 0);
            if (!*images) {
                sprintf(buffer, "Don't find Buttons Images File : %s.dc6", name);
                d2_assert(!*images, buffer, __FILE__, __LINE__);
            }
        }
    }

    void __stdcall loadCustomImages() {
        if (active_SkillsPoints) loadImagesFile(&unassignSkillsBtnImages, "UnassignSkillsBtns");
        if (active_StatsPoints) loadImagesFile(&unassignStatsBtnImages, "UnassignStatsBtns");
        if (active_multiPageStash || active_newInterfaces) loadImagesFile(&stashBtnsImages, "StashBtns");
        if (active_sharedGold) loadImagesFile(&sharedGoldBtnsImages, "SharedGoldBtns");
        if (active_newInterfaces) loadImagesFile(&newStatsInterfaceImages, "EmptyPage");
        if (active_newInterfaces) loadImagesFile(&statsBackgroundImages, "StatsBackground");
    }

#define FREE_IMAGE_FILE(I) if(I) {D2FreeImage(I);I=NULL;}

    void __stdcall freeCustomImages() {
        FREE_IMAGE_FILE(unassignSkillsBtnImages);
        FREE_IMAGE_FILE(unassignStatsBtnImages);
        FREE_IMAGE_FILE(stashBtnsImages);
        FREE_IMAGE_FILE(sharedGoldBtnsImages);
        FREE_IMAGE_FILE(newStatsInterfaceImages);
        FREE_IMAGE_FILE(statsBackgroundImages);
    }

    __declspec(naked)void caller_loadCustomImages_114() {
        __asm{
        PUSH ECX
        CALL loadCustomImages
        POP ECX
        JMP D2LoadResImage
        }
    }

    __declspec(naked)void caller_loadCustomImages() {
        __asm{
        CALL loadCustomImages
        MOV ECX, 0x0C
        RETN
        }
    }

    __declspec(naked)void caller_freeCustomImages_114() {
        __asm{
        CALL freeCustomImages
        CALL D2FreeResImages
        RETN
        }
    }

    __declspec(naked)void caller_freeCustomImages() {
        __asm{
        CALL freeCustomImages
        MOV ECX, 0x0C
        RETN
        }
    }

    void Install_PlugYImagesFiles() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_PlugYFiles();
        log_msg("Patch D2Client to load/free custom images. (PlugYImagesFiles)\n");

        // Load custom images
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x9692F : (version_D2Client == V113d ? 0x6E0BE : (version_D2Client == V113c ? 0x27EAE : (version_D2Client == V112 ? 0x82761 : (version_D2Client == V111b ? 0xB67E1 : (version_D2Client == V111 ? 0x2E101 : (version_D2Client == V110 ? 0x5E4B1 : (version_D2Client == V109d ? 0x57E21 : 0x57E21)))))))));
        if (version_D2Client == V114d) {
            MEMC_REF4(D2LoadResImage, caller_loadCustomImages_114);
            //0049692E  |. E8 8DB7FBFF    CALL Game.004520C0
        } else {
            memt_byte(0xB9, 0xE8);
            MEMT_REF4(0x0000000C, caller_loadCustomImages);
            //6FAFE4B1  |. B9 0C000000    MOV ECX,0C
            //6FADE101  |. B9 0C000000    MOV ECX,0C
            //6FB667E1  |. B9 0C000000    MOV ECX,0C
            //6FB32761  |. B9 0C000000    MOV ECX,0C
            //6FAD7EAE  |. B9 0C000000    MOV ECX,0C
            //6FB1E0BE  |. B9 0C000000    MOV ECX,0C
        }

        // Free custom images
        mem_seek(offset_D2Client + (version_D2Client == V114d ? 0x56DED : (version_D2Client == V113d ? 0x6D07D : (version_D2Client == V113c ? 0x26F8D : (version_D2Client == V112 ? 0x8158D : (version_D2Client == V111b ? 0xB580D : (version_D2Client == V111 ? 0x2D12D : (version_D2Client == V110 ? 0x5E639 : (version_D2Client == V109d ? 0x57FA9 : 0x57FA9)))))))));
        if (version_D2Client == V114d) {
            MEMC_REF4(D2FreeResImages, caller_freeCustomImages_114);
            //00456DEC   . E8 9FFB0300    CALL Game.00496990
        } else {
            memt_byte(0xB9, 0xE8);
            MEMT_REF4(0x0000000C, caller_freeCustomImages);
            //6FAFE639  |> B9 0C000000    MOV ECX,0C
            //6FADD12D  |> B9 0C000000    MOV ECX,0C
            //6FB6580D  |> B9 0C000000    MOV ECX,0C
            //6FB3158D  |> B9 0C000000    MOV ECX,0C
            //6FAD6F8D  |> B9 0C000000    MOV ECX,0C
            //6FB1D07D  |> B9 0C000000    MOV ECX,0C
        }
        log_msg("\n");
        isInstalled = true;
    }


/****************************************************************************************************/
/*char* STDCALL isModCompileFile (char* filename)
{
	if (strstr(filename, modDataDirectory) )
		return ".";
	return NULL;
}
char * fff = "%s";
FCT_ASM( caller_compileExcel_114 )
	PUSH ECX
	PUSH EDX
	PUSH EDX
	CALL isModCompileFile
	POP EDX
	POP ECX
	TEST EAX,EAX
	JE ISNOTMODDATA
	POP EAX
	MOV DWORD PTR SS:[ESP],EDX
	PUSH fff
	ADD EAX,5
	PUSH EAX
ISNOTMODDATA:
	LEA EAX,DWORD PTR SS:[EBP-0x108]
	RETN
}}*/

    void loadStatsInterfaceDesc(DWORD mempool);
    void freeStatsInterfaceDesc();

    void __fastcall loadTxtFiles(DWORD mempool) {
        loadStatsInterfaceDesc(mempool);
    }

    void __fastcall freeTxtFiles() {
        freeStatsInterfaceDesc();
    }

    __declspec(naked)void caller_loadTxtFiles_111() {
        __asm{
        MOV ECX, DWORD PTR SS:[ESP+4]
        CALL loadTxtFiles
        JMP D2LoadSuperuniques
        }
    }

    __declspec(naked)void caller_loadTxtFiles() {
        __asm{
        PUSH ECX
        CALL loadTxtFiles
        POP ECX
        JMP D2LoadSuperuniques
        }
    }

    __declspec(naked)void caller_freeTxtFiles() {
        __asm{
        CALL freeTxtFiles
        JMP D2Fog10212
        }
    }

    void Install_PlugYTxtFiles() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_PlugYFiles();
        log_msg("Patch D2Common to load/free custom txt files. (PlugYTxtFiles)\n");

//	lookupItemStatCost =  (void*)R7(D2Common, A1D70, A1D70, AA1D8, 0000, 0000, 0000, 0000);

        // Load custom txt files
        mem_seek(offset_D2Common + (version_D2Common == V114d ? 0x25A560 : (version_D2Common == V113d ? 0x855E4 : (version_D2Common == V113c ? 0x5D6E4 : (version_D2Common == V112 ? 0x81C44 : (version_D2Common == V111b ? 0x37444 : (version_D2Common == V111 ? 0x76854 : (version_D2Common == V110 ? 0x2F7D7 : (version_D2Common == V109d ? 0x7F4B : 0x7F4B)))))))));
        MEMC_REF4(D2LoadSuperuniques, version_D2Common >= V111 && version_D2Common < V114a ? caller_loadTxtFiles_111 : caller_loadTxtFiles);
        //6FD47F4A  |. E8 B1750100    CALL D2Common.6FD5F500
        //6FD47F4A  |. E8 C1750100    CALL D2Common.6FD5F510
        //01B6F7D6  |. E8 C5A7FFFF    CALL D2Common.01B69FA0
        //6FDC6853  |. E8 58B6FFFF    CALL D2Common.6FDC1EB0                   ; \D2Common.6FDC1EB0
        //6FD87443  |. E8 58B6FFFF    CALL D2Common.6FD82AA0                   ; \D2Common.6FD82AA0
        //6FDD1C43  |. E8 58B6FFFF    CALL D2Common.6FDCD2A0                   ; \D2Common.6FDCD2A0
        //6FDAD6E3  |. E8 88C1FFFF    CALL D2Common.6FDA9870                   ; \D2Common.6FDA9870
        //6FDD55E3  |. E8 58B6FFFF    CALL D2Common.6FDD0C40                   ; \D2Common.6FDD0C40
        //0065A55F  |. E8 7CADFFFF    CALL Game.006552E0

        // Free custom txt files
        mem_seek(offset_D2Common + (version_D2Common == V114d ? 0x25A1C8 : (version_D2Common == V113d ? 0xFAA3 : (version_D2Common == V113c ? 0x5E8B3 : (version_D2Common == V112 ? 0x44E13 : (version_D2Common == V111b ? 0x15AB3 : (version_D2Common == V111 ? 0x332B3 : (version_D2Common == V110 ? 0x10186 : (version_D2Common == V109d ? 0x79EC : 0x79EC)))))))));
        MEMJ_REF4(D2Fog10212, caller_freeTxtFiles);
        //6FD479EB   . E8 C8C00600    CALL <JMP.&Fog.#10212>
        //6FD479EB   . E8 C8C00600    CALL <JMP.&Fog.#10212>
        //01B50185  |. E8 F8410700    CALL <JMP.&Fog.#10212>
        //6FD832B2  |. E8 755FFDFF    CALL <JMP.&Fog.#10212>
        //6FD65AB2  |. E8 B537FFFF    CALL <JMP.&Fog.#10212>
        //6FD94E12  |. E8 1744FCFF    CALL <JMP.&Fog.#10212>
        //6FDAE8B2  |. E8 8FA9FAFF    CALL <JMP.&Fog.#10212>
        //6FD5FAA2  |. E8 5FB4FFFF    CALL <JMP.&Fog.#10212>
        //0065A1C7   . E8 E42E0600    CALL Game.006BD0B0                       ; \Game.006BD0B0

        /*if ( version_D2Client >= V114a )
        {
            mem_seek R8(Storm,	0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 2122A2);
            memt_byte( 0x8D ,0x90); // NOP
            memt_byte( 0x85 ,0xE8); // CALL
            MEMT_REF4(0xFFFFFEF8, caller_compileExcel_114);
            //006122A2  |. 8D85 F8FEFFFF  LEA EAX,DWORD PTR SS:[EBP-108]           ; |
        }*/

        log_msg("\n");
        isInstalled = true;
    }


}