#include "catch.h"

#include "../C1.h"

TEST_CASE("Test that ReturnTwo does infact return 2", "[SampleTag]") {
    C1 c1;

    REQUIRE(c1.ReturnTwo() == 2); // Abort test if it fails
}

TEST_CASE("Test that ReturnFour does infact return 4", "[SampleTag]") {
    C1 c1;

    REQUIRE(c1.ReturnFour() == 4); // Abort test if it fails


}

