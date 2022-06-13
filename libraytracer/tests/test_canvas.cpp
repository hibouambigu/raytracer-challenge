#include "gtest/gtest.h"
#include <canvas.h>

class CanvasBasics : public ::testing::Test
{
  protected:
    Canvas c = Canvas{ 10, 20 };
};

TEST_F(CanvasBasics, CreateCanvas)
{
    EXPECT_EQ(c.getWidth(), 10);
    EXPECT_EQ(c.getHeight(), 20);
}

TEST_F(CanvasBasics, WritePixels)
{
    // test writing pixels to the canvas
    auto red = Colour{ 1.f, 0.f, 0.f };
    c.writePixel(2, 3, red);
    EXPECT_EQ(c.pixelAt(2, 3), red);
}

TEST_F(CanvasBasics, ConstructsPPMHeader)
{
    // canvas can construct a PPM format header
    auto c = Canvas(5, 3);
    auto ppm = c.generatePPMHeader();
    EXPECT_EQ(ppm, "P3\n5 3\n255\n");
}
