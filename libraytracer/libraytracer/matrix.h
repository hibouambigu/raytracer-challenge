////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Matrix
///     Provides square matrices (of n by n dimensions)
///     Stacy Gaudreau
///     18.06.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <vector>
#include "utils.h"
#include "tuples.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
class Matrix
{
  public:
    Matrix() = default;
    explicit Matrix(std::array<std::array<T, N>, N> initialValues);
    [[nodiscard]] size_t getSize() const;
    T& operator()(size_t row, size_t col);
    T operator()(size_t row, size_t col) const;
    /// Construct an identity matrix of the given matrix size.
    static Matrix<T, N> identity();
    /// Transposed version of this matrix. Returns a new, transposed matrix.
    Matrix<T, N> transposed() const;
    /// Compute the determinant of this matrix.
    T determinant() const;
    /// Derive a submatrix from this matrix.
    Matrix<T, N-1> subMatrix(size_t row, size_t col);


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// Equality of matrices
    friend bool operator==(const Matrix<T, N>& a, const Matrix<T, N>& b) {
        for (size_t row{}; row < a.getSize(); row++) {
            for (size_t col{}; col < a.getSize(); col++)
                if (a(row, col) != b(row, col)) return false;
        }
        return true;
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// Matrix multiplication
    friend Matrix<T, N> operator*(const Matrix<T, N>& A, const Matrix<T, N>& B) {
        auto X = Matrix<T, N>{};
        for(size_t row{}; row < A.getSize(); row++) {
            for (size_t col{}; col < A.getSize(); col++) {
                T element{};
                for (size_t i{}; i < A.getSize(); i++)
                    element += A(row, i) * B(i, col);
                X(row, col) = element;
            }
        }
        return X;
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

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
Matrix<T, N> Matrix<T, N>::identity()
{
    Matrix<T, N> M{};
    for (size_t i{}; i < M.getSize(); i++)
        M(i, i) = 1.;
    return M;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
Matrix<T, N> Matrix<T, N>::transposed() const
{
    Matrix<T, N> t{};
    for (size_t row{}; row < N; row++) {
        for (size_t col{}; col < N; col++) {
           t(col, row) = M[row][col];
        }
    }
    return t;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
T Matrix<T, N>::determinant() const
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t N>
Matrix<T, N-1> Matrix<T, N>::subMatrix(size_t row, size_t col)
{
    Matrix<T, N-1> sub{};
    std::vector<std::vector<T>> toCopy{};
    // make the toCopy vector from source matrix
    for (size_t r{}; r < N; ++r) {
        // make a new row vector
        std::vector<T> rowVec{};
        for (size_t c{}; c < N; ++c) {
            if (r != row && c != col)
                rowVec.push_back(M[r][c]);
        }
        // push it onto copy vector matrix if it belongs there
        if (r != row)
            toCopy.push_back(rowVec);
    }
    // now copy the vector into our new submatrix
    for (size_t r{}; r < toCopy.size(); ++r) {
        for (size_t c{}; c < toCopy.size(); ++c) {
            sub(r, c) = toCopy[r][c];
        }
    }
    return sub;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
/// Linear Algebra functions which don't (or can't) belong in any one class in particular
//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Linear {

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Multiply a 4x4 matrix with a Tuple()
template <typename T>
Tuple mult(const Matrix<T, 4>& M, const Tuple& t)
{
    auto X = Tuple{};
    constexpr auto SIZE{4};
    for(size_t row{}; row < SIZE; row++) {
        for (size_t col{}; col < SIZE; col++) {
            T element{};
            for (size_t i{}; i < SIZE; i++)
                element += M(row, i) * t(i);
            X(row) = element;
        }
    }
    return X;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
} // END namespace Linear
//////////////////////////////////////////////////////////////////////////////////////////////////////


