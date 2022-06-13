#pragma once

#include <string>

#include <colours.h>
#include <matrix_2d.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
class Canvas
{
  public:
    Canvas(size_t width, size_t height);
    size_t getWidth();
    size_t getHeight();
    bool isBlank();
    void writePixel(size_t x, size_t y, Colour& colour);
    Colour pixelAt(size_t x, size_t y);
    std::string generatePPMHeader() const;

  private:
    size_t width, height;
    Matrix2D<Colour> pixels;

};
