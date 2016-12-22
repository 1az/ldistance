#include "catch.hpp"

#include "fuzzy_search.h"

#include <sstream>
#include <string>
#include <vector>
#include <utility>

class TStacker {
public:
    using TResult = std::vector<std::pair<int, std::string>>;
    TResult Result;

public:
    void operator()(int pos, const std::string& match) {
        Result.emplace_back(pos, match);
    }
};

TEST_CASE( "Fuzzy search correctness", "[fuzzy_search]" ) {
    REQUIRE_THROWS( NLDistance::TFuzzySearch fsearch("a", 1, TStacker()) );
    REQUIRE_THROWS( NLDistance::TFuzzySearch fsearch("", 0, TStacker()) );

    SECTION( "Empty haystack" ) {
        TStacker stacker;
        NLDistance::TFuzzySearch fsearch("horse", 3, std::ref(stacker));
        fsearch.Feed("");

        TStacker::TResult result{};
        REQUIRE( stacker.Result == result);
    }

    SECTION( "One char needle" ) {
        TStacker stacker;
        NLDistance::TFuzzySearch fsearch("a", 0, std::ref(stacker));
        fsearch.Feed("amknfamemaama");

        TStacker::TResult result{{0, "a"}, {5, "a"}, {9, "a"}, {10, "a"}, {12, "a"}};
        REQUIRE( stacker.Result == result);
    }

    SECTION( "Exact match" ) {
        TStacker stacker;
        NLDistance::TFuzzySearch fsearch("abc", 0, std::ref(stacker));
        fsearch.Feed("acbcbabcabccbacbabccabab");

        TStacker::TResult result{{5, "abc"}, {8, "abc"}, {16, "abc"}};
        REQUIRE( stacker.Result == result);
    }

    SECTION( "Some long string" ) {
        TStacker stacker;
        NLDistance::TFuzzySearch fsearch("horse", 2, std::ref(stacker));
        fsearch.Feed("ophrsahorhsporhsohporspossapo");

        TStacker::TResult result{{2, "hrs"}, {2, "hrsa"}, {6, "hor"}, {6, "horh"},
                                 {6, "horhs"}, {6, "horhsp"}, {18, "pors"}, {18, "porsp"}};
        REQUIRE( stacker.Result == result);
    }

    SECTION( "Long needle and short haystack" ) {
        TStacker stacker;
        NLDistance::TFuzzySearch fsearch("horse", 4, std::ref(stacker));
        fsearch.Feed("pos");

        TStacker::TResult result{{0, "po"}, {0, "pos"}};
        REQUIRE( stacker.Result == result);
    }
}

TEST_CASE( "Fuzzy search feeding", "[fuzzy_search]" ) {
    TStacker::TResult result{{2, "hrs"}, {2, "hrsa"}, {6, "hor"}, {6, "horh"},
                             {6, "horhs"}, {6, "horhsp"}, {18, "pors"}, {18, "porsp"}};
    SECTION( "Dual feed" ) {
        TStacker stacker;
        NLDistance::TFuzzySearch fsearch("horse", 2, std::ref(stacker));
        fsearch.Feed("ophrsahor");
        fsearch.Feed("hsporhsohporspossapo");
        REQUIRE( stacker.Result == result);
    }
    SECTION( "Stream feed" ) {
        TStacker stacker;
        NLDistance::TFuzzySearch fsearch("horse", 2, std::ref(stacker));
        std::istringstream stream("ophrsahorhsporhsohporspossapo");
        fsearch.Feed(stream);
        REQUIRE( stacker.Result == result);
    }
}

TEST_CASE( "Fuzzy search reset", "[fuzzy_search]" ) {
    TStacker::TResult result{{2, "hrs"}, {2, "hrsa"}, {6, "hor"}, {9, "pors"}, {9, "porsp"}};
    TStacker stacker;
    NLDistance::TFuzzySearch fsearch("horse", 2, std::ref(stacker));
    fsearch.Feed("ophrsahor");
    fsearch.Reset();
    fsearch.Feed("hsporhsohporspossapo");
    REQUIRE( stacker.Result == result);
}
