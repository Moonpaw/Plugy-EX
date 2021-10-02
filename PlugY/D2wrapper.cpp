/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d and DoNotCloseNihlathakPortal by haxifix.

    @file D2wrapper.cpp
    @brief Main Diablo II extra DLL handler.

    This is the sources of the D2DLL class.

=================================================================*/

#include "plugYFiles.h"			// Install_PlugYFiles()
#include "globalVariable.h"		// Install_VariableOnRealm()
#include "commands.h"			// Install_Commands()
#include "mainScreen.h"			// Install_PrintPlugYVersion() Install_VersionChange()
#include "savePath.h"			// Install_ChangingSavePath()
#include "bigStash.h"			// Install_BigStash()
#include "skillPerLevelUp.h"	// Install_SkillPerLevelUp()
#include "statPerLevelUp.h"		// Install_StatPerLevelUp()
#include "statsPoints.h"		// Install_StatsPoints() Install_StatsLimitShiftClick()
#include "skillsPoints.h"		// Install_SkillsPoints()
#include "infinityStash.h"		// Install_MultiPageStash()
#include "newInterfaces.h"		// Install_NewInterfaces()
#include "worldEvent.h"			// Install_WorldEvent()
#include "uberQuest.h"			// Install_UberQuest()
#include "extraOptions.h"		// Install_AlwaysRegenMapInSP()
#include "language.h"			// Install_LanguageManagement()
#include "windowed.h"			// installed with Install_PrintPlugYVersion()
#include "savePlayerData.h"		// Install_SavePlayerData()
#include "customLibraries.h"
#include "common.h"
#include "error.h"
#include "d2functions.h"
#include "parameters.h"
#include "d2wrapper.h"

namespace PlugY {
    int version_Game = UNKNOWN;
    int version_D2Client = UNKNOWN;
    int version_D2CMP = UNKNOWN;
    int version_D2Common = UNKNOWN;
    int version_D2Game = UNKNOWN;
    int version_D2gfx = UNKNOWN;
    int version_D2Lang = UNKNOWN;
    int version_D2Launch = UNKNOWN;
    int version_D2Net = UNKNOWN;
    int version_D2Win = UNKNOWN;
    int version_Fog = UNKNOWN;
    int version_Storm = UNKNOWN;
    DWORD offset_Game = NULL;
    DWORD offset_D2Client = NULL;
    DWORD offset_D2CMP = NULL;
    DWORD offset_D2Common = NULL;
    DWORD offset_D2Game = NULL;
    DWORD offset_D2gfx = NULL;
    DWORD offset_D2Lang = NULL;
    DWORD offset_D2Launch = NULL;
    DWORD offset_D2Net = NULL;
    DWORD offset_D2Win = NULL;
    DWORD offset_Fog = NULL;
    DWORD offset_Storm = NULL;
    const char *S_Game = "Game.exe";
    const char *S_D2Client = "D2Client.dll";
    const char *S_D2CMP = "D2CMP.dll";
    const char *S_D2Common = "D2Common.dll";
    const char *S_D2Game = "D2Game.dll";
    const char *S_D2gfx = "D2gfx.dll";
    const char *S_D2Lang = "D2Lang.dll";
    const char *S_D2Launch = "D2Launch.dll";
    const char *S_D2Net = "D2Net.dll";
    const char *S_D2Win = "D2Win.dll";
    const char *S_Fog = "Fog.dll";
    const char *S_Storm = "Storm.dll";

// Change the protection scheme of a loaded
// DLL called libraryName in memory space at address addr+size to allow us to customize it.
    void hookLibrary(const char *libraryName, DWORD addr) {
        DWORD dw = 0;
        BYTE *offsetPESignature = addr + *(BYTE **) ((BYTE *) addr + 0x3C);
        DWORD sizeOfCode = *(DWORD *) (offsetPESignature + 0x1C);
        BYTE *baseOfCode = addr + *(BYTE **) (offsetPESignature + 0x2C);
        if (!VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READWRITE, &dw)) {
            log_msg("Failed to hook library : %s. (%08X,%08X)\n", libraryName, baseOfCode, sizeOfCode);
            exit(-1);
        }
        log_msg("%s successfully hooked. (%08X,%08X)\n", libraryName, baseOfCode, sizeOfCode);
    }

    void unhookLibrary(const char *libraryName, DWORD addr) {
        DWORD dw = 0;
        BYTE *offsetPESignature = addr + *(BYTE **) ((BYTE *) addr + 0x3C);
        DWORD sizeOfCode = *(DWORD *) (offsetPESignature + 0x1C);
        BYTE *baseOfCode = addr + *(BYTE **) (offsetPESignature + 0x2C);
        if (!VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READ, &dw))
            log_msg("Failed to unhook library : %s. (%08X,%08X)\n", libraryName, baseOfCode, sizeOfCode);
        else
            log_msg("%s successfully unhooked. (%08X,%08X)\n", libraryName, baseOfCode, sizeOfCode);
    }

    void freeLibrary(DWORD library) {
        if (library && library != offset_Game)
            FreeLibrary((HMODULE) library);
    }

    void freeD2Libraries() {
        if (version_Game >= V114a)
            return;
        log_msg("***** Free Libraries *****\n");

        freeLibrary(offset_D2Client);
        freeLibrary(offset_D2CMP);
        freeLibrary(offset_D2Common);
        freeLibrary(offset_D2Game);
        freeLibrary(offset_D2gfx);
        freeLibrary(offset_D2Lang);
        freeLibrary(offset_D2Launch);
        freeLibrary(offset_D2Net);
        freeLibrary(offset_D2Win);
        freeLibrary(offset_Fog);
        freeLibrary(offset_Storm);
        log_msg("\n\n");
    }

    void hookLibraries() {
        log_msg("***** Unprotect Libraries *****\n");
        if (version_Game >= V114a)
            hookLibrary(S_Game, offset_Game);
        else {
            hookLibrary(S_D2Client, offset_D2Client);
            //	hookLibrary(S_D2CMP,	offset_D2CMP);
            hookLibrary(S_D2Common, offset_D2Common);
            hookLibrary(S_D2Game, offset_D2Game);
            hookLibrary(S_D2gfx, offset_D2gfx);
            hookLibrary(S_D2Lang, offset_D2Lang);
            hookLibrary(S_D2Launch, offset_D2Launch);
            //	hookLibrary(S_D2Net,	offset_D2Net);
            //	hookLibrary(S_D2Win,	offset_D2Win);
            hookLibrary(S_Fog, offset_Fog);
            hookLibrary(S_Storm, offset_Storm);
        }
        log_msg("\n\n");
    }

    void unhookLibraries() {
        log_msg("***** Reprotect Libraries *****\n");
        if (version_Game >= V114a)
            unhookLibrary(S_Game, offset_Game);
        else {
            unhookLibrary(S_D2Client, offset_D2Client);
            //	unhookLibrary(S_D2CMP,		offset_D2CMP);
            unhookLibrary(S_D2Common, offset_D2Common);
            unhookLibrary(S_D2Game, offset_D2Game);
            unhookLibrary(S_D2gfx, offset_D2gfx);
            unhookLibrary(S_D2Lang, offset_D2Lang);
            unhookLibrary(S_D2Launch, offset_D2Launch);
            //	unhookLibrary(S_D2Net,		offset_D2Net);
            //	unhookLibrary(S_D2Win,		offset_D2Win);
            unhookLibrary(S_Fog, offset_Fog);
            unhookLibrary(S_Storm, offset_Storm);
        }
        log_msg("\n\n");
    }

    void freeCustomLibraries() {
        if (!customDlls)
            return;
        log_msg("***** Free custom libraries *****\n");
        TCustomDll *dll = customDlls;
        TCustomDll *nextDll;
        while (dll) {
            dll->release();
            freeLibrary(dll->offset);
            nextDll = dll->nextDll;
            delete (dll);
            dll = nextDll;
        }
    }

    void initCustomLibraries() {
        log_msg("***** Init custom libraries *****\n");
        TCustomDll *dll = customDlls;
        while (dll) {
            dll->init();
            dll = dll->nextDll;
        }
    }

    void loadCustomLibraries() {
        char *curString = NULL;
        TCustomDll *nextDll;
        DWORD offset_currentDll;
        log_msg("***** Custom libraries *****\n");
        if (dllFilenames)
            curString = strtok(dllFilenames, "|");
        if (!curString)
            log_msg("No custom libraries to load.\n");
        else {
            while (curString) {
                if (curString[0]) {
                    log_msg("Load custom library : %s\n", curString);
                    offset_currentDll = (DWORD) LoadLibrary(curString);
                    if (!offset_currentDll) {
                        log_msg("Load library %s failed !\n", curString);
                        exit(0);
                    }
                    nextDll = customDlls;
                    customDlls = new(TCustomDll);
                    customDlls->nextDll = nextDll;
                    customDlls->initialize(offset_currentDll);
                }
                curString = strtok(NULL, "|");
            }
        }
        if (dllFilenames)
            D2FogMemDeAlloc(dllFilenames, __FILE__, __LINE__, 0);
        log_msg("\n\n");
    }

    IMAGE_NT_HEADERS *GetHeader(LPBYTE pBase) {
        if (pBase == NULL)
            return NULL;
        IMAGE_DOS_HEADER *pDosHeader = (IMAGE_DOS_HEADER *) pBase;
        if (IsBadReadPtr(pDosHeader, sizeof(IMAGE_DOS_HEADER)))
            return NULL;
        if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
            return NULL;
        IMAGE_NT_HEADERS *pHeader = (IMAGE_NT_HEADERS *) (pBase + pDosHeader->e_lfanew);
        if (IsBadReadPtr(pHeader, sizeof(IMAGE_NT_HEADERS)))
            return NULL;
        if (pHeader->Signature != IMAGE_NT_SIGNATURE)
            return NULL;
        return pHeader;
    }

    void initD2modules() {
        log_msg("***** Get D2 Modules address and version *****\n\n");
        offset_D2Client = (DWORD) LoadLibrary("D2Client.dll");
        offset_D2CMP = (DWORD) LoadLibrary("D2CMP.dll");
        offset_D2Common = (DWORD) LoadLibrary("D2Common.dll");
        offset_D2Game = (DWORD) LoadLibrary("D2Game.dll");
        offset_D2gfx = (DWORD) LoadLibrary("D2gfx.dll");
        offset_D2Lang = (DWORD) LoadLibrary("D2Lang.dll");
        offset_D2Launch = (DWORD) LoadLibrary("D2Launch.dll");
        offset_D2Net = (DWORD) LoadLibrary("D2Net.dll");
        offset_D2Win = (DWORD) LoadLibrary("D2Win.dll");
        offset_Fog = (DWORD) LoadLibrary("Fog.dll");
        offset_Storm = (DWORD) LoadLibrary("Storm.dll");
        int count_109b = 0;
        int count_109d = 0;
        int count_110f = 0;
        int count_111 = 0;
        int count_111b = 0;
        int count_112a = 0;
        int count_113c = 0;
        int count_113d = 0;
        int count_114a = 0;
        int count_114b = 0;
        int count_114c = 0;
        int count_114d = 0;
        IMAGE_NT_HEADERS *pHeader;
        if (offset_D2Client != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2Client);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000C234D) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000C16CD) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000C1C1D) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045E6) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045EE) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045FA) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045F6) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045DE) count_113d++;
        }
        if (offset_D2CMP != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2CMP);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00011361) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00011361) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00010E61) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C23) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C23) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C23) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C23) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C23) count_113d++;
        }
        if (offset_D2Common != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2Common);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00074D1D) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00074E2D) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000856DD) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C94) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C8D) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C97) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C8F) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000047C7) count_113d++;
        }
        if (offset_D2Game != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2Game);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000C66AC) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000C6D5C) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000EDC2C) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000036E6) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000373D) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000374B) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000373C) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00003747) count_113d++;
        }
        if (offset_D2gfx != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2gfx);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000054EB) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000054EB) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000054A5) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001807) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001807) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001807) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001807) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001807) count_113d++;
        }
        if (offset_D2Lang != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2Lang);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00005148) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00005138) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00005048) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A6A) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A5B) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A75) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A71) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A5A) count_113d++;
        }
        if (offset_D2Launch != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2Launch);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000172C3) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00017243) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00018DC7) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A84) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A85) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A85) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A87) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001A84) count_113d++;
        }
        if (offset_D2Net != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2Net);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002BCE) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002BCE) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00002C6E) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001676) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001676) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000167E) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001676) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000167E) count_113d++;
        }
        if (offset_D2Win != NULL) {
            pHeader = GetHeader((LPBYTE) offset_D2Win);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00014F38) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00014F38) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00012EC0) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000187E) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000187E) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000188E) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000187E) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00001887) count_113d++;
        }
        if (offset_Fog != NULL) {
            pHeader = GetHeader((LPBYTE) offset_Fog);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00013658) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000142E7) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000162B0) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00003159) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00003142) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000314A) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00003162) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00003142) count_113d++;
        }
        if (offset_Storm != NULL) {
            pHeader = GetHeader((LPBYTE) offset_Storm);
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00013658) count_109b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000142E7) count_109d++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000162B0) count_110f++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00003159) count_111++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00003142) count_111b++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0000314A) count_112a++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x00003162) count_113c++;
            if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x0003C3E0) count_113d++;
        }
        int minimum_match_dll = 7;
        if (count_109b >= minimum_match_dll) version_Game = V109b;
        if (count_109d >= minimum_match_dll) version_Game = V109d;
        if (count_110f >= minimum_match_dll) version_Game = V110;
        if (count_111 >= minimum_match_dll) version_Game = V111;
        if (count_111b >= minimum_match_dll) version_Game = V111b;
        if (count_112a >= minimum_match_dll) version_Game = V112;
        if (count_113c >= minimum_match_dll) version_Game = V113c;
        if (count_113d >= minimum_match_dll) version_Game = V113d;

        version_D2Common = version_Game;
        version_D2Win = version_Game;
        version_D2Launch = version_Game;
        version_D2gfx = version_Game;
        version_D2Client = version_Game;
        version_D2Net = version_Game;
        version_D2Lang = version_Game;
        version_D2Game = version_Game;
        version_D2CMP = version_Game;
        version_Fog = version_Game;
        version_Storm = version_Game;
        log_msg("DLL match for version 1.09b :\t%d\n", count_109b);
        log_msg("DLL match for version 1.09d :\t%d\n", count_109d);
        log_msg("DLL match for version 1.10f :\t%d\n", count_110f);
        log_msg("DLL match for version 1.11  :\t%d\n", count_111);
        log_msg("DLL match for version 1.11b :\t%d\n", count_111b);
        log_msg("DLL match for version 1.12a :\t%d\n", count_112a);
        log_msg("DLL match for version 1.13c :\t%d\n", count_113c);
        log_msg("\n");
        offset_Game = (DWORD) GetModuleHandle("Game.exe");
        if (offset_Game != NULL) {
            version_Game = GetD2Version((HMODULE) offset_Game);
            log_msg("Game.exe loaded at:\t%08X (%s)\n", offset_Game, GetVersionString(version_Game));
            if (version_Game >= V114a) {
                version_D2Common = version_Game;
                version_D2Win = version_Game;
                version_D2Launch = version_Game;
                version_D2gfx = version_Game;
                version_D2Client = version_Game;
                version_D2Net = version_Game;
                version_D2Lang = version_Game;
                version_D2Game = version_Game;
                version_D2CMP = version_Game;
                version_Fog = version_Game;
                version_Storm = version_Game;
            }
        }

        log_msg("Version game is:\t(%s)\n\n", GetVersionString(version_Game));
        if (version_Game == UNKNOWN) {
            MessageBoxA(NULL, "This version of Diablo II is not supported by Plugy. Please upgrade or downgrade to a supported version.", "Plugy 14.01", MB_OK);
        }
    }

//////////////////////////////////// EXPORTS FUNCTIONS ////////////////////////////////////


    extern "C" __declspec(dllexport) bool __stdcall Release() {
        log_msg("\n***** FREE LIBRARIES *****\n\n");
        freeCustomLibraries();
        freeD2Libraries();
        log_msg("***** END DIABLO II *****\n");
        log_close();
        return true;
    }

    extern "C" __declspec(dllexport) void *__stdcall Init(LPSTR IniName) {
        if (IniName) log_msg("* PlugY is called from D2mod.dll\n\n");
        static int isInstalled = false;
        if (isInstalled) return NULL;
        isInstalled = true;
        initD2modules();
        if (version_Game < V109 || version_Game > V113d && version_Game != V114d) {
            log_box("PlugY isn't compatible with this version : %s", GetVersionString(version_Game));
            Release();
            exit(0);
        }
        initD2functions();
        loadParameters();
        if (!active_plugin) return NULL;
        loadCustomLibraries();
        hookLibraries();
        log_msg("***** INSTALL FUNCTIONS *****\n");
        Install_PlugYFiles();
        Install_VariableOnRealm();
        if (active_Commands)
            Install_Commands();
        if (active_ChangeLanguage || active_LanguageManagement)
            Install_LanguageManagement();
        if (active_VersionTextChange)
            Install_VersionChange();
        if (active_PrintPlugYVersion || active_Windowed)
            Install_PrintPlugYVersion();
        if (active_StatsPoints)
            Install_StatsPoints();
        else if (active_DisplayBaseStatsValue)
            Install_DisplayBaseStatsValue();
        if (active_SkillsPoints)
            Install_SkillsPoints();
        if (active_changingSavePath)
            Install_ChangingSavePath();
        if (active_AutoBackup)
            Install_SavePlayerData();
        if (active_StatsShiftClickLimit)
            Install_StatsLimitShiftClick();
        if (active_RunLODs)
            Install_RunLODs();
        if (active_bigStash)
            Install_BigStash();
        if (active_SkillPerLevelUpChange)
            Install_SkillPerLevelUp();
        if (active_StatPerLevelUpChange)
            Install_StatPerLevelUp();
        if (active_multiPageStash)
            Install_MultiPageStash();
        if (active_newInterfaces)
            Install_NewInterfaces();
        if (active_WorldEvent)
            Install_WorldEvent();
        if (active_UberQuest)
            Install_UberQuest();
        if (active_alwaysRegenMapInSP)
            Install_AlwaysRegenMapInSP();
        if (nbPlayersCommandByDefault)
            Install_SendPlayersCommand();
        if (active_DisplayItemLevel)
            Install_DisplayItemLevel();
        if (active_AlwaysDisplayLifeMana)
            Install_AlwaysDisplayLifeMana();
        if (active_EnabledTXTFilesWithMSExcel)
            Install_EnabledTXTFilesWithMSExcel();
        if (active_LadderRunewords)
            Install_LadderRunewords();
        if (active_EnabledCowPortalWhenCowKingWasKill)
            Install_EnabledCowPortalWhenCowKingWasKill();
        if (active_DoNotCloseNihlathakPortal)
            Install_DoNotCloseNihlathakPortal();
        if (active_MoveCainNearHarrogathWaypoint)
            Install_MoveCainNearHarrogathWaypoint();
        if (active_RemoveExperienceDiminushingReturn)
            Install_RemoveExperienceDiminushingReturn();
        log_msg("\nDLL patched sucessfully.\n\n\n");
        unhookLibraries();
        initCustomLibraries();

        //loadLocalizedStrings(D2GetLang());

        log_msg("***** ENTERING DIABLO II *****\n\n");
        active_logFile--;
        if (active_logFile < 1)
            log_close();
        return NULL;
    }
}
