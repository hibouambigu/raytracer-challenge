#include "gtest/gtest.h"
#include <tuples.h>

TEST(TupleBasics, ZeroWIsAPoint)
{
    // a tuple created with w=1.0 is a point
    Tuple a{4.3, -4.2, 3.1, 1.0};
}

//#define CATCH_CONFIG_MAIN
//
//#include "catch.hpp"
//#include "Tuples/Tuples.h"
//
//
//TEST_CASE("Tuple Basics")
//{
//    SECTION("a tuple created with w=1.0 is a point")
//    {
//        Tuple a{ 4.3, -4.2, 3.1, 1.0 };
//        REQUIRE(a.tuple[0] == Approx(4.3));
//        REQUIRE(a.tuple[1] == Approx(-4.2));
//        REQUIRE(a.tuple[2] == Approx(3.1));
//        REQUIRE(a.tuple[3] == Approx(1.0));
//        REQUIRE(a.isPoint() == true);
//        REQUIRE(a.isVector() == false);
//    }
//    SECTION("a tuple created with w=0.0 is a vector")
//    {
//        Tuple a{ 4.3, -4.2, 3.1, 0.0 };
//        REQUIRE(a.tuple[0] == Approx(4.3));
//        REQUIRE(a.tuple[1] == Approx(-4.2));
//        REQUIRE(a.tuple[2] == Approx(3.1));
//        REQUIRE(a.tuple[3] == Approx(0.0));
//        REQUIRE(a.isPoint() == false);
//        REQUIRE(a.isVector() == true);
//    }
//    SECTION("point() creates tuples with w=1")
//    {
//        auto p = Tuple::Point(4, -4, 3);
//        auto t = Tuple{ 4, -4, 3, 1 };
//        REQUIRE(p == t);
//    }
//    SECTION("vector() creates tuples with w=0")
//    {
//        auto p = Tuple::Vector(4, -4, 3);
//        auto t = Tuple{ 4, -4, 3, 0 };
//        REQUIRE(p == t);
//    }
//}
//
//TEST_CASE("Tuple Arithmetic")
//{
//    SECTION("adding a point and a vector results in a vector")
//    {
//        Tuple p{ 3, -2, 5, 1 };
//        Tuple v{ -2, 3, 1, 0 };
//        REQUIRE(p + v == Tuple{ 1, 1, 6, 1 });
//    }
//    SECTION("subtracting two points results in a vector")
//    {
//        auto p1 = Tuple::Point(3, 2, 1);
//        auto p2 = Tuple::Point(5, 6, 7);
//        REQUIRE(p1 - p2 == Tuple::Vector(-2, -4, -6));
//    }
//    SECTION("subtracting a vector from a point results in a point")
//    {
//        auto p1 = Tuple::Point(3, 2, 1);
//        auto p2 = Tuple::Vector(5, 6, 7);
//        REQUIRE(p1 - p2 == Tuple::Point(-2, -4, -6));
//    }
//    SECTION("subtracting two vectors results in a vector")
//    {
//        auto v1 = Tuple::Vector(3, 2, 1);
//        auto v2 = Tuple::Vector(5, 6, 7);
//        REQUIRE(v1 - v2 == Tuple::Vector(-2, -4, -6));
//    }
//    SECTION("negating a tuple")
//    {
//        auto v1 = Tuple{ 1, -2, 3, -4 };
//        REQUIRE(-v1 == Tuple{ -1, 2, -3, 4 });
//    }
//    SECTION("multiplying a tuple by a scalar")
//    {
//        auto a = Tuple{ 1, -2, 3, -4 };
//        // auto v2 = Tuple::Vector(5, 6, 7);
//        REQUIRE(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
//    }
//    SECTION("multiplying a tuple by a fraction")
//    {
//        auto a = Tuple{ 1, -2, 3, -4 };
//        // auto v2 = Tuple::Vector(5, 6, 7);
//        REQUIRE(a * .5 == Tuple(0.5, -1, 1.5, -2));
//    }
//    SECTION("multiplying a tuple by a scalar")
//    {
//        auto a = Tuple{ 1, -2, 3, -4 };
//        // auto v2 = Tuple::Vector(5, 6, 7);
//        REQUIRE(a / 2 == Tuple(0.5, -1, 1.5, -2));
//    }
//}
//
//TEST_CASE("Vector Magnitude")
//{
//    SECTION("magnitude of vector (1, 0, 0)")
//    {
//        auto v = Tuple::Vector(1, 0, 0);
//        REQUIRE(v.magnitude() == 1);
//    }
//    SECTION("magnitude of vector (0, 1, 0)")
//    {
//        auto v = Tuple::Vector(0, 1, 0);
//        REQUIRE(v.magnitude() == 1);
//    }
//    SECTION("magnitude of vector (0, 0, 1)")
//    {
//        auto v = Tuple::Vector(0, 0, 1);
//        REQUIRE(v.magnitude() == 1);
//    }
//    SECTION("magnitude of vector (1, 2, 3)")
//    {
//        auto v = Tuple::Vector(1, 2, 3);
//        REQUIRE(v.magnitude() == sqrt(14));
//    }
//    SECTION("magnitude of vector (-1, -2, -3)")
//    {
//        auto v = Tuple::Vector(-1, -2, -3);
//        REQUIRE(v.magnitude() == sqrt(14));
//    }
//}
//TEST_CASE("Normalising Vectors")
//{
//    SECTION("normalising vector (4, 0, 0) yields (1, 0, 0)")
//    {
//        auto v = Tuple::Vector(4, 0, 0);
//        REQUIRE(Tuple::normalize(v) == Tuple::Vector(1, 0, 0));
//    }
//}

