#pragma once

#include <colours.h>
#include <matrix_2d.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
class Canvas
{
  public:
    Canvas(size_t width, size_t height);
    size_t getWidth();
    size_t getHeight();

  private:
    size_t width, height;
    Matrix2D<Colour> pixels;

};
