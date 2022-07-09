#include "materials.h"
#include "colours.h"
#include "gtest/gtest.h"

TEST(MaterialsBasics, DefaultMaterialConstructed)
{
    // the default material is constructed with default values
    Material m{};
    EXPECT_EQ(m.colour, Colour(1, 1, 1));
    EXPECT_DOUBLE_EQ(m.ambient, 0.1);
    EXPECT_DOUBLE_EQ(m.diffuse, 0.9);
    EXPECT_DOUBLE_EQ(m.specular, 0.9);
    EXPECT_DOUBLE_EQ(m.shininess, 200.0);

}


