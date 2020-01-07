#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Array.cpp"

TEST_CASE() {
    Array<int> array = Array<int>();

    SECTION("insertion test") {
        array.insert(1);

        REQUIRE(array[0] == 1);
        REQUIRE(array.size() == 1);

        array.insert(2);

        REQUIRE(array[1] == 2);
        REQUIRE(array.size() == 2);

        array.insert(1, 3);

        REQUIRE(array.size() == 3);
        REQUIRE(array[1] == 3);
    }

    SECTION("removal test") {
        array.insert(1);
        array.insert(2);

        array.remove(0);

        REQUIRE(array[0] == 2);
        REQUIRE(array.size() == 1);
    }
}

TEST_CASE() {
    Array<int> array = Array<int>();

    SECTION("iterator test") {
        array.insert(1);
        array.insert(2);
        array.insert(3);

        auto it = array.iterator();
        REQUIRE(it.get() == 1);
        REQUIRE(it.hasNext());
        REQUIRE(!it.hasPrev());

        it.set(2);

        REQUIRE(it.get() == 2);

        it.next();

        REQUIRE(it.get() == 2);
        REQUIRE(it.hasNext());
        REQUIRE(it.hasPrev());

        it.next();

        REQUIRE(it.get() == 3);
        REQUIRE(!it.hasNext());
        REQUIRE(it.hasPrev());

        it.insert(4);

        REQUIRE(it.get() == 4);
        REQUIRE(it.hasPrev());
        REQUIRE(it.hasNext());
    }
}