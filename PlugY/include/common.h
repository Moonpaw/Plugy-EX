#pragma once

#include <Windows.h>
/*
#include "../Commons/d2constants.h"
#include "../Commons/d2BinFile.h"

#include "../Commons/d2StringTblStruct.h"
#include "../Commons/D2UnitStruct.h"
#include "../Commons/updatingConst.h"
#include "../Commons/VersionInfo.h"
#include "../Commons/D2TypeDefMacros.h"
#include "../Commons/D2TypeNameMacros.h"
#include "error.h"
#include "modifMemory.h"
#include "parameters.h"
#include "d2wrapper.h"
#include "playerCustomData.h"
#include "globalVariable.h"

#include "d2functions.h"
#include "LocalizedStrings.h"*/

#include "d2Struct.h"

namespace PlugY {
    using namespace Commons;
    bool isOnRect(DWORD x, DWORD y, DWORD x0, DWORD y0, DWORD l, DWORD h);
    void freeMessage(sWinMessage *msg);
}
