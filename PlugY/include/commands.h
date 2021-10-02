/*=================================================================
	File created by Yohann NICOLAS.

	Commands directly in game.

=================================================================*/
#pragma once

#include "common.h"
namespace PlugY {
    extern bool active_Commands;
    void savePlayers(Commons::Unit *ptChar);
    void maxGold(Commons::Unit *ptChar);
    void putGold(Commons::Unit *ptChar, DWORD amount);
    void takeGold(Commons::Unit *ptChar, DWORD amount);
    void updateSharedGold(DWORD goldAmount);
    void Install_Commands();
}
