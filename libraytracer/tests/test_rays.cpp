#include "intersection.h"
#include "rays.h"
#include "shapes.h"
#include "gtest/gtest.h"

TEST(Raycasting, RayIsConstructed)
{
    auto origin = Point(1, 2, 3);
    auto dir = Vector(4, 5, 6);
    auto r = Ray(origin, dir);
    EXPECT_EQ(origin, r.getOrigin());
    EXPECT_EQ(dir, r.getDirection());
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
    EXPECT_EQ(xs.count(), 2);
    EXPECT_DOUBLE_EQ(xs(0).t, 4);
    EXPECT_DOUBLE_EQ(xs(1).t, 6);
}

TEST(Raycasting, TangentialIntersectionOfSphere)
{
    Ray ray{{0, 1, -5}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_DOUBLE_EQ(xs(0).t, 5);
    EXPECT_DOUBLE_EQ(xs(1).t, 5);
}

TEST(Raycasting, RayMissesASphere)
{
    Ray ray{{0, 2, -5}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 0);
}

TEST(Raycasting, RayOriginInsideSphere)
{
    Ray ray{{0, 0, 0}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_DOUBLE_EQ(xs(0).t, -1);
    EXPECT_DOUBLE_EQ(xs(1).t, 1);
}

TEST(Raycasting, RayIsBehindSphere)
{
    Ray ray{{0, 0, 5}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_DOUBLE_EQ(xs(0).t, -6);
    EXPECT_DOUBLE_EQ(xs(1).t, -4);
}

TEST(Intersections, IntersectionEncapsulatesObjectAndT)
{
    // the intersection datatype should encapsulate
    // the geometric object and also the time of intersection
    Sphere s{};
    Intersection i{3.5, s};
    EXPECT_EQ(i.t, 3.5);
    EXPECT_EQ(i.shape, s);
}

TEST(Intersections, IntersectSetsObjectOnIntersection)
{
    Ray ray{{0, 0, -5}, {0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_EQ(xs(0).shape, s);
    EXPECT_EQ(xs(1).shape, s);
}
