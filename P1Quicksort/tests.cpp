#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "main.cpp"

template<typename T, typename Compare>
bool isSorted(const T* array, int size, Compare comp) {
    if (size == 0)
        return true;   // Edge case

    T previousValue = *array;
    ++array;

    while (size) {
        if (!comp(*array, previousValue))
            return false;
        previousValue = *array;

        ++array;
        --size;
    }
    return true;
}

TEST_CASE() {
    int array[] = { 53, 2, 22, 63, 85, 89, 20, 7, 24, 39, 38, 47, 73, 78, 31, 99, 50, 26 };
    int size = std::size(array);

    SECTION("unsorted array test section") {
        sort(array, array + size - 1, intComparator);

        REQUIRE(isSorted(array, size, intComparator));
    }
}

TEST_CASE()
{
    int array[] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int size = std::size(array);

    SECTION("desc sorted array test section") {
        sort(array, array + size - 1, intComparator);

        REQUIRE(isSorted(array, size, intComparator));
    }
}

TEST_CASE()
{
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    int size = std::size(array);

    SECTION("asc sorted array test section") {
        sort(array, array + size - 1, intComparator);

        REQUIRE(isSorted(array, size, intComparator));
    }
}

TEST_CASE()
{
    int array[] = { 53, 2, 22, 63, 85, 89, 20, 7, 99, 39, 38, 47, 73, 78, 31, 24, 50, 98 };
    int size = std::size(array);

    SECTION("left partition is the biggest test section") {
        sort(array, array + size - 1, intComparator);

        REQUIRE(isSorted(array, size, intComparator));
    }
}

TEST_CASE()
{
    int array[] = { 53, 2, 22, 63, 85, 89, 20, 7, 99, 39, 38, 47, 73, 78, 31, 24, 50, 98 };
    int size = std::size(array);

    SECTION("left partition is the biggest test section") {
        sort(array, array + size - 1, intComparator);

        REQUIRE(isSorted(array, size, intComparator));
    }
}

TEST_CASE()
{
    int* array = new int[0];
    int size = 0;

    SECTION("single element array test section") {
        sort(array, array + size - 1, intComparator);

        REQUIRE(isSorted(array, size, intComparator));
    }
}
