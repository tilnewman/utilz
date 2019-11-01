#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "utilz/math.hpp"

#include <limits>

using namespace utilz;
using namespace utilz::math;

TEST_CASE("isRealClose(integer)", "[isRealClose]")
{
    constexpr int high { std::numeric_limits<int>::max() };
    constexpr int half { high / 2 };
    constexpr int low { std::numeric_limits<int>::lowest() };

    REQUIRE(isRealClose(low, low));
    REQUIRE(isRealClose(low + 1, low + 1));
    REQUIRE(isRealClose(-half, -half));
    REQUIRE(isRealClose(-1, -1));
    REQUIRE(isRealClose(0, 0));
    REQUIRE(isRealClose(1, 1));
    REQUIRE(isRealClose(half, half));
    REQUIRE(isRealClose(high - 1, high - 1));
    REQUIRE(isRealClose(high, high));
}
