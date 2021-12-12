#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <VersionInfo.h>
#include <d2wrapper.h>
#include <d2functions.h>
#include <regex>
#include "newInterface_CubeListing.h"

namespace PlugY_Tests {
    using namespace Commons;
    using namespace PlugY;

    TEST_SUITE("D2 Init functions") {

        TEST_CASE("FindVersionOrDefault should return UNKNOWN when not initialized ") {
            auto result = findVersionOrDefault(D2Common);
            REQUIRE(result == UNKNOWN);
        }

        TEST_CASE("FindOffsetOrDefault should return defaultValue when not initialized ") {
            auto result = findOffsetOrDefault(D2Common, 0x1000);
            REQUIRE(result == 0x1000);
        }

        TEST_CASE("FindVersionOrDefault should return value when initialized ") {
            version_D2Common = V110;
            init_dll_maps();
            auto result = findVersionOrDefault(D2Common);
            REQUIRE(result == Commons::V110);
        }

        TEST_CASE("FindOffSetOrDefault should return value when initialized ") {
            offset_D2Common = 0x1234;
            init_dll_maps();
            auto result = findOffsetOrDefault(D2Common, 0x2000);
            REQUIRE(result == 0x1234);
        }

        void setFctAddr(DWORD *addr, HMODULE module, LPCSTR index) {
            //dummy replacement
        }

        TEST_CASE("set version specific address should be simple") {
            //getAddressOfVersion(version_D2Common == V114d ? 0x21AED0 : (version_D2Common == V113d ? 0x10907 : (version_D2Common == V113c ? 0x10346 : (version_D2Common == V112 ? 0x11109 : (version_D2Common == V111b ? 0x11084 : (version_D2Common == V111 ? 0x10188 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x00000 : 0x00000
            if (version_D2Common > V113d) {
                int v109d = 0x00000;
                int v110 = 0x00000;
                int v111 = 0x10188;
                int v111b = 0x11084;
                int v112 = 0x11109;
                int v113c = 0x10346;
                int v113d = 0x10907;
                int v114d = 0x21AED0;
                int defaultValue = 0x00000;
//                int addressVersion = version_D2Common == V114d ? v114d : (version_D2Common == V113d ? v113d : (version_D2Common == V113c ? v113c : (version_D2Common == V112 ? v112 : (version_D2Common == V111b ? v111b : (version_D2Common == V111 ? v111 : (version_D2Common == V110 ? v110 : (version_D2Common == V109d ? v109d : defaultValue)))))));
                D2Common11084 = (TD2Common11084) (offset_D2Common + getAddressOfVersion(version_D2Common, defaultValue, v109d, v110, v111, v111b, v112, v113c, v113d, v114d));
            } else {
                int v109d = 00000;
                int v110 = 00000;
                int v111 = 10188;
                int v111b = 11084;
                int v112 = 11109;
                int v113c = 10346;
                int v113d = 10907;
                int defaultValue = 00000;
//                int addressVersion = version_D2Common == V113d ? v113d : (version_D2Common == V113c ? v113c : (version_D2Common == V112 ? v112 : (version_D2Common == V111b ? v111b : (version_D2Common == V111 ? v111 : (version_D2Common == V110 ? v110 : (version_D2Common == V109d ? v109d : defaultValue))))));
                setFctAddr((DWORD *) &D2Common11084, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, defaultValue, v109d, v110, v111, v111b, v112, v113c, v113d));
            }
        }
    }

    TEST_SUITE("Cube Functions") {

        TEST_CASE("replaceColorCodes should replace ÿc2 with [Gold]") {
            auto source = std::wstring(L"     1: Unique Item + Death's Hand + Death's Guard + Death's Touch + ÿc2ZyEl Scroll => Item");
            auto result = PlugY::replaceColorCodes(&source);
            auto expected = std::wstring (L"     1: Unique Item + Death's Hand + Death's Guard + Death's Touch + [Green]ZyEl Scroll => Item");
            INFO("The result is :", from_wide(*result));
            REQUIRE(result->compare(expected) == 0);
        }

        TEST_CASE("replaceColorCodes should replace color codes with [colors]") {
            auto source = std::wstring(L"ÿc1ÿc2ÿc3ÿc4ÿc8ÿc:ÿc0ÿc5ÿc6ÿc7ÿc9ÿc;");
            auto result = PlugY::replaceColorCodes(&source);
            auto expected = std::wstring (L"[Red][Green][Blue][Gold][Orange][Dark Green][white][grey][black][gold][Yellow][Purple]");
            INFO("The result is :", from_wide(*result));
            REQUIRE(result->compare(expected) == 0);
        }

        TEST_CASE("regex replace ÿc2 with [Gold]") {
            auto source = std::wstring(L"ÿc2..");
            auto result = std::regex_replace(source, std::wregex(L"ÿc2"), L"[Gold]");
            auto expected = std::wstring (L"[Gold]..");
            INFO("The result is :", from_wide(result));
            REQUIRE(result.compare(expected) == 0);
        }

        TEST_CASE("regex replace ÿc2:ÿc2 with [Gold]:[Gold]") {
            auto source = std::wstring(L"ÿc2:ÿc2");
            auto result = std::regex_replace(source, std::wregex(L"ÿc2"), L"[Gold]");
            auto expected = std::wstring (L"[Gold]:[Gold]");
            INFO("The result is :", result);
            REQUIRE(result.compare(expected) == 0);
        }

        TEST_CASE("vectorToWstring should concatenate to a single string") {
            auto source = std::wstring(L"Item");
            std::vector<std::wstring> vec;
            vec.push_back(source);
            auto result = PlugY::vectorToWstring(vec);
            auto expected = L"Item\n";
            REQUIRE(result.compare(expected) == 0);
        }
    }
}