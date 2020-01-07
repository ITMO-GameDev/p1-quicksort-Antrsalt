#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Dictionary.cpp"

TEST_CASE() {
    Dictionary<int, bool> dictionary = Dictionary<int, bool>();

    SECTION("test put") {
        dictionary.put(1, false);

        REQUIRE(dictionary.size() == 1);
        REQUIRE(dictionary.contains(1));
        REQUIRE(!dictionary[1]);

        dictionary.put(2, true);

        REQUIRE(dictionary.size() == 2);
        REQUIRE(dictionary.contains(2));
        REQUIRE(dictionary[2]);
    }

    SECTION("test remove") {
        dictionary.put(1, false);
        dictionary.put(2, true);

        REQUIRE(dictionary.size() == 2);
        REQUIRE(dictionary.contains(1));
        REQUIRE(dictionary[2]);
        REQUIRE(!dictionary[1]);

        dictionary.remove(1);

        REQUIRE(dictionary.size() == 1);
        REQUIRE(!dictionary.contains(1));
        REQUIRE(dictionary.contains(2));
        REQUIRE(dictionary[2]);

        dictionary.remove(2);

        REQUIRE(dictionary.size() == 0);
        REQUIRE(!dictionary.contains(2));
        REQUIRE(!dictionary[2]);
        REQUIRE(!dictionary[1]);
    }
}

TEST_CASE() {
    Dictionary<int, int> dictionary = Dictionary<int, int>();

    SECTION("iterator test") {
        dictionary.put(1, 4);
        dictionary.put(2, 5);
        dictionary.put(3, 6);

        auto it = dictionary.iterator();
        REQUIRE(it.get() == 5);
        REQUIRE(it.key() == 2);
        REQUIRE(it.hasNext());
        REQUIRE(!it.hasPrev());

        it.set(2);

        REQUIRE(it.get() == 2);

        it.next();

        REQUIRE(it.get() == 4);
        REQUIRE(it.key() == 1);
        REQUIRE(it.hasNext());
        REQUIRE(it.hasPrev());

        it.next();

        REQUIRE(it.get() == 6);
        REQUIRE(it.key() == 3);
        REQUIRE(!it.hasNext());
        REQUIRE(it.hasPrev());
    }
}

