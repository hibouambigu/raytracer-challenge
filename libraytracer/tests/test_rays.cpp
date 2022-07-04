#include "gtest/gtest.h"
#include "rays.h"
#include "sphere.h"

TEST(Raycasting, RayIsConstructed)
{
    auto origin = Point(1, 2, 3);
    auto dir = Vector(4, 5, 6);
    auto r = Ray(origin, dir);
    EXPECT_EQ(origin, r.getOrigin());
    EXPECT_EQ(dir, r.getdirection());
}

TEST(Raycasting, ComputePointFromDistance)
{
    auto ray = Ray({2, 3, 4}, {1, 0, 0});
    EXPECT_EQ(ray.position(0), Point(2, 3, 4));
    EXPECT_EQ(ray.position(1), Point(3, 3, 4));
    EXPECT_EQ(ray.position(-1), Point(1, 3, 4));
    EXPECT_EQ(ray.position(2.5), Point(4.5, 3, 4));
}

TEST(Raycasting, IntersectsSphereAtTwoPoints)
{
    Ray ray{{0, 0, -5}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_DOUBLE_EQ(xs[0], 4);
    EXPECT_DOUBLE_EQ(xs[1], 6);
}

TEST(Raycasting, TangentialIntersectionOfSphere)
{
    Ray ray{{0, 1, -5}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_DOUBLE_EQ(xs[0], 5);
    EXPECT_DOUBLE_EQ(xs[1], 5);
}

TEST(Raycasting, RayMissesASphere)
{
    Ray ray{{0, 2, -5}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.size(), 0);
}

TEST(Raycasting, RayOriginInsideSphere)
{
    Ray ray{{0, 0, 0}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_DOUBLE_EQ(xs[0], -1);
    EXPECT_DOUBLE_EQ(xs[1], 1);
}

TEST(Raycasting, RayIsBehindSphere)
{
    Ray ray{{0, 0, 5}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_DOUBLE_EQ(xs[0], -6);
    EXPECT_DOUBLE_EQ(xs[1], -4);
}
