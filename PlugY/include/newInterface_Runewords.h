#pragma once

#include "common.h"
#include "d2functions.h"
#include <vector>

namespace PlugY {
    void __stdcall printRuneWordsPage();
    DWORD __stdcall mouseRuneWordsPageLeftDown(sWinMessage *msg);
    DWORD __stdcall mouseRuneWordsPageLeftUp(sWinMessage *msg);

}