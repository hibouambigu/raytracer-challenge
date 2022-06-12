#include "gtest/gtest.h"
#include <matrix_2d.h>
#include <colours.h>

class Matrix2DBasics : public ::testing::Test
{
  protected:
    Matrix2D<Colour> pixels = Matrix2D<Colour>(10, 20);
};

TEST_F(Matrix2DBasics, CreatesPixelMatrix)
{
    auto black = Colour{ };
    EXPECT_EQ(pixels.get(0, 0), black);
}

TEST_F(Matrix2DBasics, BasicGeometry)
{
    EXPECT_EQ(pixels.getWidth(), 10);
    EXPECT_EQ(pixels.getHeight(), 20);
}

TEST_F(Matrix2DBasics, AllElementsInitAsZero)
{
    EXPECT_EQ(pixels.get(0, 0), Colour{});
    EXPECT_EQ(pixels.get(pixels.getWidth(), pixels.getHeight()), Colour{});
}

TEST_F(Matrix2DBasics, IsBlank)
{
    EXPECT_TRUE(pixels.isBlank());
}

TEST_F(Matrix2DBasics, IsNotBlank)
{
    pixels.set(0, 0, Colour{ 1.f, 0.f, 1.f });
    EXPECT_FALSE(pixels.isBlank());
}

TEST_F(Matrix2DBasics, SettingAndGetting)
{
    auto c = Colour{ .5f, .2f, .75f };
    size_t x = pixels.getWidth(), y = pixels.getHeight();
    pixels.set(x, y, c);
    EXPECT_EQ(pixels.get(x, y), c);
    pixels.set(5, 5, Colour{});
    EXPECT_EQ(pixels.get(5, 5), Colour{});
}