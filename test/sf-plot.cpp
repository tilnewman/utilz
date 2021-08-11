#include "catch.hpp"

#include "utilz/math.hpp"
#include "utilz/sf-plot.hpp"

#include <iostream>
#include <limits>

using namespace utilz;
using namespace utilz::plot;

TEST_CASE("setupColors()", "[setupColors]")
{
    utilz::plot::Colors colors(sf::Color::White);
    REQUIRE(colors.data == sf::Color::White);
}
