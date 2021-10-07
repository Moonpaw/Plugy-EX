/*=================================================================
	File created by Yohann NICOLAS.

	Save Player Custom Data.

=================================================================*/
#pragma once

#include "common.h"
namespace PlugY {
    extern bool active_AutoBackup;
    extern int maxBackupPerCharacter;

    void backupSaveFiles(char *name, int isHardCoreGame);

    void Install_SavePlayerData();

}