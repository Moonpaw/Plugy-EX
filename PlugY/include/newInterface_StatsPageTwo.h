/*=================================================================
	File created by Yohann NICOLAS.

	New Stat Interface Page 2

=================================================================*/
#pragma once

#include "common.h"

namespace PlugY {
    void __stdcall printNewStatsPageTwo(int currentPage);

    DWORD __stdcall mouseNewStatsPageTwoLeftDown(sWinMessage *msg);

    DWORD __stdcall mouseNewStatsPageTwoLeftUp(sWinMessage *msg);

}