
#include <catch2/catch.hpp>

#include <iostream>

TEST_CASE("Section showcase") {
    std::cout << '1';
    SECTION("A") {
        std::cout << 'A';
    }
    SECTION("B") {
        std::cout << 'B';
    }
    std::cout << '\n';
}
