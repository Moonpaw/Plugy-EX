/*=================================================================
	File created by Yohann NICOLAS.

	Updating Client.

=================================================================*/
#pragma once

#include "common.h"
namespace PlugY {
    void Install_UpdateClient();

    void updateClient(Commons::Unit *ptChar, DWORD mFunc, DWORD p1, DWORD p2, DWORD p3);

    void updateClient(Commons::Unit *ptChar, DWORD mFunc, char *msg);

}