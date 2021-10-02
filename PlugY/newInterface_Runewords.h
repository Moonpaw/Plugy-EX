#pragma once

#include "common.h"
#include "d2functions.h"

namespace PlugY {
    void STDCALL printRuneWordsPage();
    DWORD STDCALL mouseRuneWordsPageLeftDown(sWinMessage *msg);
    DWORD STDCALL mouseRuneWordsPageLeftUp(sWinMessage *msg);
}