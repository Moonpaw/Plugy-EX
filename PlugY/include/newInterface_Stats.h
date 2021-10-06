/*=================================================================
	File created by Yohann NICOLAS.

	New Stat Interface

=================================================================*/
#pragma once

#include "common.h"
#include "d2functions.h"
namespace PlugY {
    void __stdcall printNewStatsPage();

    DWORD __stdcall mouseNewStatsPageLeftDown(sWinMessage *msg);

    DWORD __stdcall mouseNewStatsPageLeftUp(sWinMessage *msg);
}
