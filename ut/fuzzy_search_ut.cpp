#include "catch.hpp"

#include "fuzzy_search.h"

#include <string>
#include <vector>
#include <utility>

       #include <iostream>

class TStacker {
public:
    std::vector<std::pair<int, std::string>> Matches;

public:
    void operator()(int pos, const std::string& match) {
        Matches.emplace_back(pos, match);
std::cout << pos << " " << match << std::endl;
    }
};

TEST_CASE( "Fuzzy search correctness", "[fuzzy_search]" ) {
    TStacker stacker;
    NLDistance::TFuzzySearch fsearch("horse", 3, stacker);
    fsearch.Feed("aaaaposa");
}

