/*=================================================================
	File created by Yohann NICOLAS.

	Add an extra save file shared by all own characters.

=================================================================*/
#pragma once

#include "common.h"
namespace PlugY {
    BYTE *readSharedSaveFile(char *name, DWORD *size);

    void writeSharedSaveFile(char *name, BYTE *data, DWORD size, bool isHardcore);

    int loadSharedSaveFile(Commons::Unit *ptChar, BYTE *data, DWORD maxSize);

    void saveSharedSaveFile(Commons::Unit *ptChar, BYTE **data, DWORD *maxSize, DWORD *curSize);

    void backupSharedSaveFile();

}