#include "catch.hpp"

#include "utilz/flat-map.hpp"

#include <algorithm>
#include <string>

using namespace utilz;

TEST_CASE("Default Constructor Creates Empty Container", "[defaultConstructor]")
{
    FlatMap<std::string, std::string> map;

    CHECK(map.empty());
    CHECK(map.size() == 0);
    CHECK_THROWS(map.at(""));
}

TEST_CASE("Empty/Size/Clear", "[emptySizeClear]")
{
    FlatMap<int, int> map;

    CHECK(map.empty());
    CHECK(map.size() == 0);

    map.clear(); // should not error or throw on clear when empty

    CHECK(map.empty());
    CHECK(map.size() == 0);

    map.append(0, 0);

    CHECK(map.empty() == false);
    CHECK(map.size() == 1);

    map.clear();

    CHECK(map.empty());
    CHECK(map.size() == 0);

    for (int i(0); i < 100; ++i)
    {
        map.append(i, (i * i));
    }

    CHECK(map.empty() == false);
    CHECK(map.size() == 100);

    map.clear();

    CHECK(map.empty());
    CHECK(map.size() == 0);
}

TEST_CASE("reserve/capacity/shrink", "[reserve/capacity/shrink]")
{
    FlatMap<int, int> map;

    // assume no std::vector will start with capacity > 1000 seems safe
    for (int i(0); i < 999; ++i)
    {
        map.append(i, (i * i));
    }

    CHECK(map.size() == 999);
    CHECK(map.capacity() > 999); // again, seems a safe bet

    map.reserve(2000);

    CHECK(map.size() == 999);
    CHECK(map.capacity() >= 2000);

    map.shrinkToFit();

    CHECK(map.size() == 999);
    CHECK(map.capacity() == 999);
}

TEST_CASE("append/at", "[append/at]")
{
    FlatMap<int, int> map;

    for (int i(0); i < 10; ++i)
    {
        map.append(i, (i * i));
    }

    for (int i(0); i < 10; ++i)
    {
        REQUIRE(map.at(i) == (i * i));
    }

    REQUIRE_THROWS(map.at(10));
}

TEST_CASE("operator[]", "[indexOperator]")
{
    FlatMap<int, int> map;

    for (int i(0); i < 3; ++i)
    {
        map.append(i, (i * i));
    }

    CHECK(map[0] == 0);
    CHECK(map[1] == 1);
    CHECK(map[2] == 4);

    CHECK(map.size() == 3);
    CHECK(map[3] == 0);
    CHECK(map.size() == 4);

    // even when empty it should work
    map.clear();
    CHECK(map.size() == 0);
    CHECK(map[0] == 0);
    CHECK(map.size() == 1);
}

TEST_CASE("find/exists", "[find/exists]")
{
    FlatMap<int, int> map;

    for (int i(0); i < 3; ++i)
    {
        map.append(i, (i * i));
    }

    for (int i(0); i < 3; ++i)
    {
        REQUIRE(map.find(i) != std::end(map));
        REQUIRE(map.exists(i));
    }

    REQUIRE(map.find(3) == std::end(map));
    REQUIRE(map.exists(3) == false);
}

TEST_CASE("erase", "[erase]")
{
    FlatMap<int, std::string> map;

    map.reserve(1000);

    for (int i(0); i < 1000; ++i)
    {
        map.append(i, std::to_string(i));
    }

    map.erase(std::begin(map), std::end(map));

    REQUIRE(map.empty());

    for (int i(0); i < 1000; ++i)
    {
        map.append(i, std::to_string(i));
    }

    // This creates a lot of duplicate keys...
    for (auto & pair : map)
    {
        pair.first = 0;
    }

    //...but this should delete them ALL.
    map.erase(0);

    REQUIRE(map.empty());

    for (int i(0); i < 1000; ++i)
    {
        map.append(i, std::to_string(i));
    }

    map.erase(
        std::remove_if(
            std::begin(map),
            std::end(map),
            [&](const FlatMap<int, std::string>::value_t & pair) { return (pair.first < 500); }),
        std::end(map));

    REQUIRE(map.size() == 500);
}

TEST_CASE("compares", "[compares]")
{
    FlatMap<int, std::string> map1;
    FlatMap<int, std::string> map2;

    CHECK(map1 == map2);
    CHECK((map1 != map2) == false);
    CHECK(map1 <= map2);
    CHECK(map1 >= map2);
    CHECK((map1 < map2) == false);
    CHECK((map1 > map2) == false);

    map1.reserve(100);

    for (int i(0); i < 100; ++i)
    {
        map1.append(i, std::to_string(i));
    }

    CHECK((map1 == map2) == false);
    CHECK(map1 != map2);
    CHECK((map1 <= map2) == false);
    CHECK(map1 >= map2);
    CHECK((map1 < map2) == false);
    CHECK(map1 > map2);

    map2.reserve(100);

    for (int i(0); i < 100; ++i)
    {
        map2.append(i, std::to_string(i));
    }

    CHECK(map1 == map2);
    CHECK((map1 != map2) == false);
    CHECK(map1 <= map2);
    CHECK(map1 >= map2);
    CHECK((map1 < map2) == false);
    CHECK((map1 > map2) == false);
}

TEST_CASE("sortAndUnique", "[sortAndUnique]")
{
    FlatMap<int, int> map1;

    map1.append(4, 0);
    map1.append(3, 0);
    map1.append(3, 0);
    map1.append(4, 0);
    map1.append(1, 0);
    map1.append(0, 0);
    map1.append(2, 0);
    map1.append(4, 0);
    map1.append(3, 0);

    FlatMap<int, int> map2;

    for (int i(0); i < 5; ++i)
    {
        map2.append(i, 0);
    }

    CHECK(map1 != map2);

    map1.sortAndUnique();

    CHECK(map1 == map2);
}
