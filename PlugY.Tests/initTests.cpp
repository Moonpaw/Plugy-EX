#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <VersionInfo.h>
#include <d2wrapper.h>
#include <d2functions.h>

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

        TEST_CASE("E8 should produce the same as e8") {
            init_dll_maps();
            version_D2Common = V110;
            offset_D2Common = 0x1234;
            auto byDef = (offset_D2Common + (version_D2Common == V114d ? 0x344304 : (version_D2Common == V113d ? 0xA33F0 : (version_D2Common == V113c ? 0x99E1C : (version_D2Common == V112 ? 0x9B500 : (version_D2Common == V111b ? 0x9EE8C : (version_D2Common == V111 ? 0x9B74C : (version_D2Common == V110 ? 0x96A20 : (version_D2Common == V109d ? 0x0000 : 0x0000)))))))));
            DWORD defaultValue = 0x0000;
            DWORD b = 0x0000;
            DWORD c = 0x96A20;
            DWORD d = 0x9B74C;
            DWORD e = 0x9EE8C;
            DWORD f = 0x9B500;
            DWORD g = 0x99E1C;
            DWORD h = 0xA33F0;
            DWORD i = 0x344304;
            auto byFun = r8(D2Common, defaultValue, b, c, d, e, f, g, h, i);
            CAPTURE(byDef);
            CAPTURE(byFun);
            auto expected = offset_D2Common + c;
            CAPTURE(expected);
            REQUIRE(byDef == byFun);
        }

        TEST_CASE("R8 should produce the same as r8") {
            init_dll_maps();
            version_D2Common = V110;
            offset_D2Common = 0x1234;
            DWORD defaultValue = 0x0000;
            DWORD b = 0x0000;
            DWORD c = 0x96A20;
            DWORD d = 0x9B74C;
            DWORD e = 0x9EE8C;
            DWORD f = 0x9B500;
            DWORD g = 0x99E1C;
            DWORD h = 0xA33F0;
            DWORD i = 0x344304;
            auto byFun = r8(D2Common, defaultValue, b, c, d, e, f, g, h, i);
            CAPTURE(byFun);
            auto expected = offset_D2Common + c;
            CAPTURE(expected);
            REQUIRE(byFun==expected);
        }

        void setFctAddr(DWORD *addr, HMODULE module, LPCSTR index) {
            //dummy replacement
        }
        DWORD matchVersion(DWORD version, DWORD defaultValue, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113c, DWORD v113d, DWORD v114d);

        TEST_CASE("set version specific address should be simple"){
            if (version_D2Common > V113d) { D2Common11084 = (TD2Common11084) (offset_D2Common + (version_D2Common == V114d ? 0x21AED0 : (version_D2Common == V113d ? 0x10907 : (version_D2Common == V113c ? 0x10346 : (version_D2Common == V112 ? 0x11109 : (version_D2Common == V111b ? 0x11084 : (version_D2Common == V111 ? 0x10188 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x00000 : 0x00000))))))))); }
            else setFctAddr((DWORD *) &D2Common11084, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10907 : (version_D2Common == V113c ? 10346 : (version_D2Common == V112 ? 11109 : (version_D2Common == V111b ? 11084 : (version_D2Common == V111 ? 10188 : (version_D2Common == V110 ? 00000 : (version_D2Common == V109d ? 00000 : 00000))))))));
        }
    }
}