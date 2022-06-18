#pragma once

#include <vector>
#include "colours.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Matrix2D
{
  public:
    Matrix2D(size_t width, size_t height);
    size_t getWidth();
    size_t getHeight();
    bool isBlank();
    T get(size_t x, size_t y);
    void set(size_t x, size_t y, T value);
    const std::vector<std::vector<T>>& getMatrix() const;
    std::vector<T> getCol(size_t x) const;

  private:
    size_t width, height;
    std::vector<std::vector<T>> matrix;
};