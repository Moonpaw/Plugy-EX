#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

unsigned int Factorial(unsigned int number) {
    return number > 1  ? Factorial(number - 1) * number : 1;
}

TEST_CASE("Factorials are computed") {
    CHECK(Factorial(0) == 1);
    CHECK(Factorial(1) == 1);
    CHECK(Factorial(2) == 2);
    CHECK(Factorial(3) == 6);
    CHECK(Factorial(10) == 3628800);
}