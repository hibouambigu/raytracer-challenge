#include "gtest/gtest.h"
#include "matrix.h"
#include "tuples.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
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
    Matrix<double, 4> A = Matrix<double, 4> ({
         {
             { 1., 2., 3., 4. },
             { 5., 6., 7., 8. },
             { 9., 8., 7., 6. },
             { 5., 4., 3., 2. }
        }
    });

    Matrix<double, 4> B = Matrix<double, 4> ({
         {
             { 1., 2., 3., 4. },
             { 5., 6., 7., 8. },
             { 9., 8., 7., 6. },
             { 5., 4., 3., 2. }
        }
    });

    Matrix<double, 4> C = Matrix<double, 4> ({
         {
             { 2., 3., 4., 5. },
             { 6., 7., 8., 9. },
             { 8., 7., 6., 5. },
             { 4., 3., 2., 1. }
        }
    });
};

////////////////////////////////////////////////////////////////////////////////////////////////////

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

TEST_F(MatrixBasics, MatrixEqualityIdenticalIsTrue)
{
    EXPECT_EQ(A, B);
}

TEST_F(MatrixBasics, MatrixEqualityDifferentIsFalse)
{
    EXPECT_NE(A, C);
}

TEST_F(MatrixBasics, MatrixMultiplication)
{
    auto B = Matrix<double, 4> ({
        {
            { -2., 1., 2., 3. },
            { 3., 2., 1., -1. },
            { 4., 3., 6., 5. },
            { 1., 2., 7., 8. }
        }
    });

    auto expected = Matrix<double, 4> ({
        {
            { 20., 22., 50., 48. },
            { 44., 54., 114., 108. },
            { 40., 58., 110., 102. },
            { 16., 26., 46., 42. }
        }
    });

    EXPECT_EQ(A * B, expected);
}

TEST_F(MatrixBasics, Matrix4x4MultipliedByTuple)
{
    auto A = Matrix<double, 4> ({
        {
            { 1., 2., 3., 4. },
            { 2., 4., 4., 2 },
            { 8., 6., 4., 1. },
            { 0., 0., 0., 1. }
        }
    });
    auto b = Tuple{1., 2., 3., 1.};
    auto expected = Tuple{ 18., 24., 33., 1. };
    auto res = Linear::mult(A, b);
    EXPECT_EQ(res, expected);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MatrixAdvanced, IdentityMatrix)
{
    auto I2 = Matrix<double, 2> ({
        {
            {1., 0.},
            {0., 1.}
        }
    });
    auto I3 = Matrix<double, 3> ({
        {
            {1., 0., 0.},
            {0., 1., 0.},
            {0., 0., 1.},
        }
    });
    auto I4 = Matrix<double, 4> ({
        {
            {1., 0., 0., 0.},
            {0., 1., 0., 0.},
            {0., 0., 1., 0.},
            {0., 0., 0., 1.},
        }
    });
    auto M2 = Matrix<double, 2>::identity();
    auto M3 = Matrix<double, 3>::identity();
    auto M4 = Matrix<double, 4>::identity();
    EXPECT_EQ(M2, I2);
    EXPECT_EQ(M3, I3);
    EXPECT_EQ(M4, I4);
}



