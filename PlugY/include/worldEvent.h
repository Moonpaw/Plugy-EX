/*=================================================================
	File created by Yohann NICOLAS.

	World Event Management.

=================================================================*/
#pragma once

#include <string>
#include "common.h"
namespace PlugY {
    extern bool active_WorldEvent;
    extern DWORD showSOJSoldCounterInAllDiff;
    extern std::string itemsToSell;
    extern DWORD worldEventmonsterID;
    extern DWORD valueOfOwnSOJSold;
    extern DWORD valueInitSOJSoldMin;
    extern DWORD valueInitSOJSoldDelta;
    extern DWORD triggerAtSolJSoldMin;
    extern DWORD triggerAtSolJSoldDelta;
    extern bool active_AutomaticSell;
    extern DWORD timeBeforeAutoSellMin;
    extern DWORD timeBeforeAutoSellDelta;

    void initWorldEventVariables();

    void Install_WorldEvent();

}