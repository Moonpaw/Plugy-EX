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
            auto byDef = R8(D2Common, 0000, 0000, 96A20, 9B74C, 9EE8C, 9B500, 99E1C, A33F0, 344304);
            auto byFun = r8(D2Common, 0x0000, 0x0000, 0x96A20, 0x9B74C, 0x9EE8C, 0x9B500, 0x99E1C, 0xA33F0, 0x344304);
            REQUIRE(byDef == byFun);
        }
    }
}