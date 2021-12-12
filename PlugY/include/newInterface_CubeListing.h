/*=================================================================
	File created by Yohann NICOLAS.

	Cube Listing functions

=================================================================*/
#pragma once

#include "common.h"
#include <vector>

namespace PlugY {
    void listAllCubeFormula();
    std::wstring* replaceColorCodes(std::wstring *str);
    std::wstring vectorToWstring(const std::vector<std::wstring>& vec);
}