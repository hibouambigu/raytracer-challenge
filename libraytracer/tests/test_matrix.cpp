#include "gtest/gtest.h"
#include <matrix.h>

class MatrixBasics : public ::testing::Test
{
  protected:
    Matrix<double, 4> M4 = Matrix<double, 4> ({
        {
            { 1., 2., 3., 4. },
            { 5.5, 6.5, 7.5, 8.5 },
            { 9, 10, 11, 12 },
            { 13.5, 14.5, 15.5, 16.5 }
        }
    });
    Matrix<double, 3> M3 = Matrix<double, 3>({
        {
            {-3., 5, 0},
            {1., -2., -7.},
            {0., 1., 1.}
        }
    });
    Matrix<double, 2> M2 = Matrix<double, 2>({
        {
            {-3., 5},
            {1., -2.}
        }
    });
};

TEST_F(MatrixBasics, Matrix4x4IsConstructed)
{
    EXPECT_DOUBLE_EQ(M4(0, 0), 1.);
    EXPECT_DOUBLE_EQ(M4(0, 3), 4.);
    EXPECT_DOUBLE_EQ(M4(1, 0), 5.5);
    EXPECT_DOUBLE_EQ(M4(1, 2), 7.5);
    EXPECT_DOUBLE_EQ(M4(2, 2), 11.);
    EXPECT_DOUBLE_EQ(M4(3, 0), 13.5);
    EXPECT_DOUBLE_EQ(M4(3, 2), 15.5);
}

TEST_F(MatrixBasics, Matrix3x3IsConstructed)
{
    EXPECT_DOUBLE_EQ(M3(0, 0), -3.);
    EXPECT_DOUBLE_EQ(M3(1, 1), -2.);
    EXPECT_DOUBLE_EQ(M3(2, 2), 1.);
}

TEST_F(MatrixBasics, Matrix2x2IsConstructed)
{
    EXPECT_DOUBLE_EQ(M2(0, 0), -3.);
    EXPECT_DOUBLE_EQ(M2(0, 1), 5.);
    EXPECT_DOUBLE_EQ(M2(1, 0), 1.);
    EXPECT_DOUBLE_EQ(M2(1, 1), -2.);
}
