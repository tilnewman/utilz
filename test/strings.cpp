#include "catch.hpp"

#include "utilz/strings.hpp"

using namespace utilz;

TEST_CASE("upperAndLower", "[upperAndLower]")
{
    CHECK(isUpper('A'));
    CHECK(isUpper('a') == false);
    CHECK(isUpper('0') == false);

    CHECK(isLower('a'));
    CHECK(isLower('A') == false);
    CHECK(isLower('0') == false);

    CHECK(toUpperCopy('a') == 'A');
    CHECK(toUpperCopy('A') == 'A');
    CHECK(toUpperCopy('0') == '0');

    CHECK(toLowerCopy('a') == 'a');
    CHECK(toLowerCopy('A') == 'a');
    CHECK(toLowerCopy('0') == '0');

    CHECK(toUpperCopy("123 abc ABC") == "123 ABC ABC");
    CHECK(toLowerCopy("123 abc ABC") == "123 abc abc");
}
