#include "catch.hpp"

#include "../src/structs.h"
#include "../src/constants.h"

TEST_CASE("Color"){

    SECTION("Default parameters"){
        Color c;
        REQUIRE(c.r == 0);
        REQUIRE(c.g == 0);
        REQUIRE(c.b == 0);
    }

    SECTION("Constructor"){
        Color c(34,82,102);
        REQUIRE(c.r == 34);
        REQUIRE(c.g == 82);
        REQUIRE(c.b == 102);
    }

    SECTION("kRed constant"){
        Color c = constants::kRed;
        REQUIRE(c.r == 255);
        REQUIRE(c.g == 0);
        REQUIRE(c.b == 0);
    }

}

TEST_CASE("FaceBounds"){

    SECTION("Default parameters"){
        FaceBounds fb;
        REQUIRE(fb.x == 0);
        REQUIRE(fb.y == 0);
        REQUIRE(fb.upper_x == 0);
        REQUIRE(fb.upper_y == 0);
    }

    SECTION("Constructor"){
        FaceBounds fb(25,40,135,92);
        REQUIRE(fb.x == 25);
        REQUIRE(fb.y == 40);
        REQUIRE(fb.upper_x == 135);
        REQUIRE(fb.upper_y == 92);
    }

    SECTION("kNoFaceBounds constant"){
        FaceBounds fb = constants::kNoFaceBounds;
        REQUIRE(fb.x == -1);
        REQUIRE(fb.y == -1);
        REQUIRE(fb.upper_x == -1);
        REQUIRE(fb.upper_y == -1);
    }

    SECTION("operator== "){
        FaceBounds a(2,4,56,20);
        FaceBounds b(2,4,56,20);
        REQUIRE(a == b);

        b = FaceBounds(2,4,55,20);
        REQUIRE(!(a == b));
    }
}
