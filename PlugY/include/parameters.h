/*=================================================================
	File created by Yohann NICOLAS.

	Loading parameters from ini file.

=================================================================*/
#pragma once

#include <string>

namespace PlugY {
#define PLUGY_VERSION "14.03"

    enum TargetMod {
        MOD_NO = 0,
    };

// Global variable (user parameters)
    extern const std::string modDataDirectory;
    extern bool active_plugin;
    extern bool active_DisableBattleNet;
    extern bool active_CheckMemory;
    extern char *dllFilenames;
    extern bool active_D2Mod;
    extern TargetMod selectModParam;

    void loadParameters();

}