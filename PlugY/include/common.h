#pragma once

#include <Windows.h>
#include <string>
#include <algorithm>
#include <iterator>
#include "d2Struct.h"

namespace PlugY {
    using namespace Commons;
    bool isOnRect(DWORD x, DWORD y, DWORD x0, DWORD y0, DWORD l, DWORD h);
    void freeMessage(sWinMessage *msg);

    inline std::wstring to_wide (const std::string &multi) {
        std::wstring wide; wchar_t w; mbstate_t mb {};
        size_t n = 0, len = multi.length () + 1;
        while (auto res = mbrtowc (&w, multi.c_str () + n, len - n, &mb)) {
            if (res == size_t (-1) || res == size_t (-2))
                throw "invalid encoding";

            n += res;
            wide += w;
        }
        return wide;
    }

    inline std::string from_wide (const std::wstring& wide){
        std::string str;
        std::transform(wide.begin(), wide.end(), std::back_inserter(str), [] (wchar_t c) {
            return (char)c;
        });
        return str;
    }
}
