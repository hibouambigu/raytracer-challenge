#include "gtest/gtest.h"
#include "materials.h"
#include "matrix.h"
#include "world.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// World Basics
////////////////////////////////////////////////////////////////////////////////////////////////////
class WorldBasics: public ::testing::Test
{
  protected:
    World w{};
    PointLight light{Point{-10, 10, -10}, Colour{1, 1, 1}};
    Material m1{{0.8, 1.0, 0.6}, 0.1, 0.7, 0.2};
    Sphere s1{}, s2{};

    void SetUp() override {
        s1.setMaterial(m1);
        s2.setTransform(Transform::translation(.5, .5, .5));
        w.addShape(&s1);
        w.addShape(&s2);
    }

};

TEST_F(WorldBasics, WorldIsConstructed)
{
    World w{};
    EXPECT_TRUE(w.isEmpty());
    EXPECT_FALSE(w.hasLighting());
}

TEST_F(WorldBasics, DefaultWorld)
{
    EXPECT_TRUE(w.hasLighting());
    EXPECT_FALSE(w.isEmpty());
    EXPECT_TRUE(w.containsObject(s1));
    EXPECT_TRUE(w.containsObject(s2));
}
