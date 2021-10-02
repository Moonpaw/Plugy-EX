/*=================================================================
	File created by Yohann NICOLAS.

	New Stat Interface

=================================================================*/
#pragma once

#include "common.h"
#include "d2functions.h"
namespace PlugY {
    void STDCALL printNewStatsPage();

    DWORD STDCALL mouseNewStatsPageLeftDown(sWinMessage *msg);

    DWORD STDCALL mouseNewStatsPageLeftUp(sWinMessage *msg);
}
