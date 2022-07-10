#include "intersection.h"
#include "shapes.h"
#include "matrix.h"
#include "gtest/gtest.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Basic Shape Properties
////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ShapeBasics, SetShapeColour)
{
    // can set the material colours of a shape
    Sphere s{};
    Colour c{1, 0, 1};
    s.setColour(c);
    EXPECT_EQ(s.getMaterial().colour, c);
}