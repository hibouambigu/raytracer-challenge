#include "gtest/gtest.h"
#include <colours.h>

class BasicColours : public ::testing::Test
{
  protected:
    Colour c1{ .9, .6, .75 };
    Colour c2{ .7, .1, .25 };
};

TEST_F(BasicColours, AddingColours)
{
    auto sum = c1 + c2;
    auto expected = Colour{ 1.6, .7, 1.0 };
    EXPECT_EQ(sum, expected);
}

TEST_F(BasicColours, SubtractingColours)
{
    auto sub = c1 - c2;
    auto expected = Colour{ .2, .5, .5 };
    EXPECT_EQ(sub, expected);
}

TEST_F(BasicColours, MultiplyByScalar)
{
    auto c = Colour{ .2, .3, .4 };
    auto expected = Colour{ .4, .6, .8 };
    EXPECT_EQ(c * 2, expected);
}

TEST_F(BasicColours, MultiplyingColours)
{
    auto product = c1 * c2;
    auto expected = Colour{ .63, .06, .1875 };
    EXPECT_EQ(c1 * c2, expected);
}