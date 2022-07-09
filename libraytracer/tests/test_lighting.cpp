#include "lighting.h"
#include "gtest/gtest.h"

TEST(PointLighting, PointHasPositionAndIntensity)
{
    Colour intensity{1, 1, 1};
    Point position{0, 0, 0};
    PointLight light{position, intensity};
    EXPECT_EQ(light.position, position);
    EXPECT_EQ(light.intensity, intensity);
}



