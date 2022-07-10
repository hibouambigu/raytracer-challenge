#include "gtest/gtest.h"
#include "materials.h"
#include "matrix.h"
#include "world.h"
#include "rays.h"


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
        s2.setTransform(Transform::scale(.5, .5, .5));
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

TEST_F(WorldBasics, RayIntersectsWorld)
{
    Ray ray{Point{0, 0, -5}, Vector{0, 0, 1}};
    Intersections xs = w.intersect(ray);
    ASSERT_EQ(xs.count(), 4);
    EXPECT_DOUBLE_EQ(xs(0).t, 4.0);
    EXPECT_DOUBLE_EQ(xs(1).t, 4.5);
    EXPECT_DOUBLE_EQ(xs(2).t, 5.5);
    EXPECT_DOUBLE_EQ(xs(3).t, 6.0);
}