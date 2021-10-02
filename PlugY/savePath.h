/*=================================================================
	File created by Yohann NICOLAS.

	Changing the current save path.

=================================================================*/
#pragma once

#include "common.h"
namespace PlugY {
    extern char *savePath;
    extern bool active_changingSavePath;

    void Install_ChangingSavePath();

}