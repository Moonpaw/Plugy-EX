#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <VersionInfo.h>
#include "d2wrapper.h"
#include <d2functions.h>
namespace PlugY_Tests {

    unsigned int Factorial(unsigned int number) {
        return number > 1 ? Factorial(number - 1) * number : 1;
    }

    TEST_CASE("Factorials are computed") {
        REQUIRE(Factorial(0) == 1);
        REQUIRE(Factorial(1) == 1);
        REQUIRE(Factorial(2) == 2);
        REQUIRE(Factorial(3) == 6);
        REQUIRE(Factorial(10) == 3628800);
    }
#define R8(Z, A, B, C, D, E, F, G, H, I) \
(offset_##Z +                            \
(version_##Z == V114d? 0x##I :           \
(version_##Z == V113d? 0x##H :           \
(version_##Z == V113c? 0x##G :           \
(version_##Z == V112? 0x##F :            \
(version_##Z == V111b? 0x##E :           \
(version_##Z == V111? 0x##D :            \
(version_##Z == V110? 0x##C :            \
(version_##Z == V109d? 0x##B : 0x##A)))))))))

    TEST_CASE("E8 should produce the same as e8") {
        using namespace Commons;
        using namespace PlugY;
        auto byDef = R8(D2Common, 0000, 0000, 96A20, 9B74C, 9EE8C, 9B500, 99E1C, A33F0, 344304);
        auto byFun = r8(D2Common, 0x0000, 0x0000, 0x96A20, 0x9B74C, 0x9EE8C, 0x9B500, 0x99E1C, 0xA33F0, 0x344304);
        REQUIRE(byDef == byFun);
    }

#undef R8
}