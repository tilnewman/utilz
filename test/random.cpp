#include "catch.hpp"

#include "utilz/random.hpp"

using namespace utilz;

TEST_CASE("Coin toss averages around 50/50 as the count goes up.", "[boolean]")
{
    Random random;

    std::size_t headsCount { 0 };
    const std::size_t count { 1'000'000 };

    for (std::size_t i(0); i < count; ++i)
    {
        if (random.boolean())
        {
            ++headsCount;
        }
    }

    const double average { static_cast<double>(headsCount) / static_cast<double>(count) };

    REQUIRE(average > 0.4);
    REQUIRE(average < 0.6);
}
