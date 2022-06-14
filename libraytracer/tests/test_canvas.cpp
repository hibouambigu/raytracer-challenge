#include "gtest/gtest.h"
#include <canvas.h>
#include <string>

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

TEST_F(CanvasBasics, GeneratesPPMHeader)
{
    // canvas can construct a PPM format header
    auto c = Canvas(5, 3);
    auto ppm = c.generatePPMHeader();
    EXPECT_EQ(ppm, "P3\n5 3\n255\n");
}

TEST_F(CanvasBasics, GeneratesPPMPixelData)
{
    // canvas can generate the pixel data in PPM format
    auto canvas = Canvas(5, 3);
    auto c1 = Colour{ 1.5, 0., 0. };
    auto c2 = Colour{ 0., .5, 0. };
    auto c3 = Colour{ -.5, 0., 1. };
    canvas.writePixel(0, 0, c1);
    canvas.writePixel(2, 1, c2);
    canvas.writePixel(4, 2, c3);
    auto ppm = c.generatePPMData();
    const char* expected =
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255";
    EXPECT_EQ(ppm, expected);
}

TEST_F(CanvasBasics, PPMFileIsWritten)
{
    // writing to PPM file is a success
    auto c = Canvas(5, 3);
    c.writePPMToFile();
}
