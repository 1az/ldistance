#include "catch.hpp"

#include "ldistance.h"

#include <array>
#include <list>
#include <string>
#include <vector>

TEST_CASE( "Essential correctness", "[ldistance]" ) {
    REQUIRE( NLDistance::LDistance("", "") == 0 );
    REQUIRE( NLDistance::LDistance("aaa", "") == 3 );
    REQUIRE( NLDistance::LDistance("", "aaa") == 3 );
    REQUIRE( NLDistance::LDistance("aaa", "aaa") == 0 );
    REQUIRE( NLDistance::LDistance("aaa", "bbb") == 3 );
    REQUIRE( NLDistance::LDistance("a", "bba") == 2 );
    REQUIRE( NLDistance::LDistance("bba", "a") == 2 );

    REQUIRE( NLDistance::LDistance("abcdef", "abc") == 3 );
    REQUIRE( NLDistance::LDistance("abc", "abcdef") == 3 );
    REQUIRE( NLDistance::LDistance("bcd", "abcde") == 2 );
    REQUIRE( NLDistance::LDistance("afjdhsgahd", "dahagsfdgf") == 9 );
    REQUIRE( NLDistance::LDistance("dahagsfdgf", "afjdhsgahd") == 9 );

    REQUIRE( NLDistance::LDistance("book", "back") == 2 );
    REQUIRE( NLDistance::LDistance("back", "book") == 2 );
    REQUIRE( NLDistance::LDistance("horse", "ros") == 3 );
    REQUIRE( NLDistance::LDistance("ros", "horse") == 3 );
    REQUIRE( NLDistance::LDistance("polynomial", "exponential") == 6 );
}

TEST_CASE( "Overloaded versions", "[ldistance]" ) {
    std::string left("horse");
    std::string right("ros");

    REQUIRE( NLDistance::LDistance(left, right) == 3 );
    REQUIRE( NLDistance::LDistance(left.begin(), left.end(), right.begin(), right.end()) == 3 );
    REQUIRE( NLDistance::LDistance(left.begin(), left.size(), right.begin(), right.size()) == 3 );
}

TEST_CASE( "Various containers", "[ldistance]" ) {
    SECTION( "vector" ) {
        std::vector<int> left = {0, 1, 2, 3, 4};
        std::vector<int> right = {2, 1, 3};
        REQUIRE( NLDistance::LDistance(left, right) == 3 );
    }
    SECTION( "string" ) {
        REQUIRE( NLDistance::LDistance(std::string(), std::string()) == 0 );
        REQUIRE( NLDistance::LDistance(std::string("aaa"), std::string()) == 3 );
        REQUIRE( NLDistance::LDistance(std::string("horse"), std::string("ros")) == 3 );
    }
    SECTION( "list" ) {
        REQUIRE( NLDistance::LDistance(std::list<int>(), std::list<int>()) == 0 );
        REQUIRE( NLDistance::LDistance(std::list<int>({1, 2, 3}), std::list<int>()) == 3 );
        REQUIRE( NLDistance::LDistance(std::list<int>({0, 1, 2, 3, 4}), std::list<int>({2, 1, 3})) == 3 );
    }
}

TEST_CASE( "Cross containers", "[ldistance]" ) {
    SECTION( "stl containers" ) {
        REQUIRE( NLDistance::LDistance(std::vector<int>({0, 1, 2, 3, 4}), std::vector<long int>({2, 1, 3})) == 3 );
        REQUIRE( NLDistance::LDistance(std::vector<int>({0, 1, 2, 3, 4}), std::list<char>({2, 1, 3})) == 3 );
        REQUIRE( NLDistance::LDistance(std::array<int, 5>({0, 1, 2, 3, 4}), std::array<int, 3>({2, 1, 3})) == 3 );
    }

    SECTION( "C arrays" ) {
        int left[5] = {0, 1, 2, 3, 4};
        int right[3] = {2, 1, 3};
        REQUIRE( NLDistance::LDistance(left, right) == 3 );
    }

    SECTION( "C strings" ) {
        REQUIRE( NLDistance::LDistance("horse", "ros") == 3 );
        REQUIRE( NLDistance::LDistance(std::string("horse"), "ros") == 3 );
        REQUIRE( NLDistance::LDistance("horse", std::string("ros")) == 3 );

        char left[5] = {'h', 'o', 'r', 's', 'e'};
        REQUIRE( NLDistance::LDistance(left, "ros") == 3 );
    }
}
