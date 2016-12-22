#include "catch.hpp"

#include "ring_buffer.h"

#include <string>

TEST_CASE( "Ring buffer correctness", "[ring_buffer]" ) {
    REQUIRE_THROWS( NLDistance::TRingBuffer<char>(0) );

    NLDistance::TRingBuffer<char> rBuf(3);
    REQUIRE_THROWS( rBuf[0] );
    REQUIRE_THROWS( rBuf[1] );

    rBuf.Insert('a');
    REQUIRE( rBuf[0] == 'a' );
    REQUIRE_THROWS( rBuf[1] );

    rBuf.Insert('b');
    REQUIRE( rBuf[0] == 'a' );
    REQUIRE( rBuf[1] == 'b' );
    REQUIRE_THROWS( rBuf[3] );

    rBuf.Insert('c');
    REQUIRE( rBuf[0] == 'a' );
    REQUIRE( rBuf[1] == 'b' );
    REQUIRE( rBuf[2] == 'c' );
    REQUIRE_THROWS( rBuf[3] );

    rBuf.Insert('d');
    REQUIRE_THROWS( rBuf[0] );
    REQUIRE( rBuf[1] == 'b' );
    REQUIRE( rBuf[2] == 'c' );
    REQUIRE( rBuf[3] == 'd' );
    REQUIRE_THROWS( rBuf[4] );

    rBuf.Insert('e');
    REQUIRE_THROWS( rBuf[0] );
    REQUIRE_THROWS( rBuf[1] );
    REQUIRE( rBuf[2] == 'c' );
    REQUIRE( rBuf[3] == 'd' );
    REQUIRE( rBuf[4] == 'e' );
    REQUIRE_THROWS( rBuf[5] );

    rBuf.Insert('f');
    REQUIRE_THROWS( rBuf[0] );
    REQUIRE_THROWS( rBuf[1] );
    REQUIRE_THROWS( rBuf[2] );
    REQUIRE( rBuf[3] == 'd' );
    REQUIRE( rBuf[4] == 'e' );
    REQUIRE( rBuf[5] == 'f' );
    REQUIRE_THROWS( rBuf[6] );
}

TEST_CASE( "Ring buffer iterators", "[ring_buffer]" ) {
    NLDistance::TRingBuffer<char> rBuf(5);
    REQUIRE( std::string(rBuf.Begin(), rBuf.End()) == "" );

    for (auto c : std::string("abcdefgh")) {
        rBuf.Insert(c);
    }
    REQUIRE( std::string(rBuf.Begin(), rBuf.End()) == "defgh" );
    REQUIRE( std::string(rBuf.IteratorAt(5), rBuf.End()) == "fgh" );
    REQUIRE( std::string(rBuf.IteratorAt(3), rBuf.IteratorAt(5)) == "de" );    
    REQUIRE_THROWS( rBuf.IteratorAt(2) );
    REQUIRE( rBuf.End() - rBuf.Begin() == rBuf.Capacity() );
}

