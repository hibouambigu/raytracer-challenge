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
        w.addLight(&light);
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

TEST_F(WorldBasics, PrecomputesStateOfIntersection)
{
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    Sphere shape{};
    Intersection i{4, shape};
    IntersectionState state = World::computeIntersectionState(i, r);
    EXPECT_EQ(state.t, i.t);
    EXPECT_EQ(state.shape, i.shape);
    EXPECT_EQ(state.point, Point(0, 0, -1));
    EXPECT_EQ(state.eye, Vector(0, 0, -1));
    EXPECT_EQ(state.normal, Vector(0, 0, -1));
}

TEST_F(WorldBasics, HitWhenIntIsOutsideShape)
{
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    Sphere shape{};
    Intersection i{4, shape};
    IntersectionState state = World::computeIntersectionState(i, r);
    EXPECT_FALSE(state.isInsideShape);
}

TEST_F(WorldBasics, HitWhenIntIsInsideShape)
{
    Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
    Sphere shape{};
    Intersection i{1, shape};
    IntersectionState state = World::computeIntersectionState(i, r);
    EXPECT_EQ(state.point, Point(0, 0, 1));
    EXPECT_EQ(state.eye, Vector(0, 0, -1));
    EXPECT_TRUE(state.isInsideShape);
    EXPECT_EQ(state.normal, Vector(0, 0, -1));
}

TEST_F(WorldBasics, ShadingAnIntersectionOutsideShape)
{
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    Intersection i{4, s1};
    Colour pixel = w.shadeIntersection(i, r);
    EXPECT_EQ(pixel, Colour(.38066, .47583, .2855));
}

TEST_F(WorldBasics, ShadingAnIntersectionInsideShape)
{
    Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
    Intersection i{0.5, s2};
    PointLight light{Point{0, .25, 0}, Colour{1, 1, 1}};
    w.setLight(&light);
    Colour pixel = w.shadeIntersection(i, r);
    EXPECT_EQ(pixel, Colour(.90498, .90498, .90498));
}

TEST_F(WorldBasics, PixelWhenTracedRayMisses)
{
    Ray r{Point{0, 0, -5}, Vector{0, 1, 0}};
    Colour pixel{w.traceRayToPixel(r)};
    EXPECT_EQ(pixel, Colour(0, 0, 0));
}

TEST_F(WorldBasics, PixelWhenTracedRayHits)
{
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    Colour pixel{w.traceRayToPixel(r)};
    EXPECT_EQ(pixel, Colour(.38066, .47583, .2855));
}

TEST_F(WorldBasics, PixelWhenHitIsBehindTracedRay)
{
    s1.setAmbient(1.0);
    s2.setAmbient(1.0);
    Ray r{Point{0, 0, .75}, Vector{0, 0, -1}};
    Colour pixel{w.traceRayToPixel(r)};
    EXPECT_EQ(pixel, s2.getMaterial().colour);
}
