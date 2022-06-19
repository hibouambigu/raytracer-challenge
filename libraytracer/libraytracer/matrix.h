////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Matrix
///     Provides square matrices (of n by n dimensions)
///     Stacy Gaudreau
///     18.06.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include "utils.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
class Matrix
{
  public:
    Matrix() = default;
    Matrix(std::array<std::array<T, N>, N> initialValues);
    size_t getSize() const;
    T& operator()(size_t row, size_t col);
    T operator()(size_t row, size_t col) const;
    /// Equality of matrices
    friend bool operator==(const Matrix<T, N>& a, const Matrix<T, N>& b) {
        for (size_t row{}; row < a.getSize(); row++) {
            for (size_t col{}; col < a.getSize(); col++)
                if (a(row, col) != b(row, col)) return false;
        }
        return true;
    };

  private:
    std::array<std::array<T, N>, N> M{};
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
Matrix<T, N>::Matrix(std::array<std::array<T, N>, N> initialValues)
: M(initialValues)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
size_t Matrix<T, N>::getSize() const
{
    return M.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
T& Matrix<T, N>::operator()(size_t row, size_t col)
{
    return M[row][col];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
T Matrix<T, N>::operator()(size_t row, size_t col) const
{
    return M[row][col];
}
