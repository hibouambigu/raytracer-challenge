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

class MatrixAdvanced : public ::testing::Test
{
  protected:

    Matrix<double, 4> I4 = Matrix<double, 4> ({
        {
            {1., 0., 0., 0.},
            {0., 1., 0., 0.},
            {0., 0., 1., 0.},
            {0., 0., 0., 1.},
        }
    });
};


TEST_F(MatrixAdvanced, IdentityMatrix)
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

TEST_F(MatrixAdvanced, TransposingMatrices)
{
    auto A = Matrix<double, 4>({
        {
            {0., 9., 3., 0.},
            {9., 8., 0., 8.},
            {1., 8., 5., 3.},
            {0., 0., 5., 8.}
        }
    });
    auto expected = Matrix<double, 4>({
        {
            {0., 9., 1., 0.},
            {9., 8., 8., 0.},
            {3., 0., 5., 5.},
            {0., 8., 3., 8.}
        }
    });
    EXPECT_EQ(A.transposed(), expected);
}

TEST_F(MatrixAdvanced, TransposingIdentityMatrix)
{
    // transposing the identity matrix *IS* the identity matrix
    EXPECT_EQ(I4, I4.transposed());
}

TEST_F(MatrixAdvanced, Determinant2x2)
{
    // calculating the determinant of 2x2 matrix
    auto A = Matrix<double, 2>({
        {
            {1., 5.},
            {-3., 2.}
        }
    });
    EXPECT_DOUBLE_EQ(A.determinant(), 17.);
}

TEST_F(MatrixAdvanced, SubmatrixOf3x3Is2x2)
{
    // the submat. of a 3x3 results in a 2x2 matrix
    auto A = Matrix<double, 3>({
        {
            {1., 5., 0.},
            {-3., 2., 7.},
            {0., 6., -3.}
        }
    });
    auto sub = Matrix<double, 2>({
        {
            {-3., 2.},
            {0., 6.}
        }
    });
    EXPECT_EQ(A.subMatrix(0, 2), sub);
}

TEST_F(MatrixAdvanced, SubmatrixOf4x4is3x3)
{
    // the submat. of a 4x4 results in a 3x3 matrix
    auto A = Matrix<double, 4>({
        {
            {-6., 1., 1., 6.},
            {-8., 5., 8., 6.},
            {-1., 0., 8., 2.},
            {-7., 1., -1., 1.}
        }
    });
    auto sub = Matrix<double, 3>({
        {
            {-6., 1., 6.},
            {-8., 8., 6.},
            {-7., -1., 1.}
        }
    });
    EXPECT_EQ(A.subMatrix(2, 1), sub);
}

TEST_F(MatrixAdvanced, MinorOf3x3Matrix)
{
    // the minor of an element at i,j is
    // the det. of the submat at i,j
    auto A = Matrix<double, 3>({
        {
            {3., 5., 0.},
            {2., -1., -7.},
            {6., -1., 5.}
        }
    });
    auto B = A.subMatrix(1, 0);
    EXPECT_DOUBLE_EQ(B.determinant(), 25.);
    EXPECT_DOUBLE_EQ(A.minor(1, 0), 25.);
}



