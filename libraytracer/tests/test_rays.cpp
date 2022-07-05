#include "intersection.h"
#include "rays.h"
#include "shapes.h"
#include "matrix.h"
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
    auto ray = Ray(Point{2, 3, 4}, Vector{1, 0, 0});
    EXPECT_EQ(ray.position(0), Point(2, 3, 4));
    EXPECT_EQ(ray.position(1), Point(3, 3, 4));
    EXPECT_EQ(ray.position(-1), Point(1, 3, 4));
    EXPECT_EQ(ray.position(2.5), Point(4.5, 3, 4));
}

TEST(Raycasting, IntersectsSphereAtTwoPoints)
{
    Ray ray{Point{0, 0, -5}, Vector{0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_DOUBLE_EQ(xs(0).t, 4);
    EXPECT_DOUBLE_EQ(xs(1).t, 6);
}

TEST(Raycasting, TangentialIntersectionOfSphere)
{
    Ray ray{Point{0, 1, -5}, Vector{0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_DOUBLE_EQ(xs(0).t, 5);
    EXPECT_DOUBLE_EQ(xs(1).t, 5);
}

TEST(Raycasting, RayMissesASphere)
{
    Ray ray{Point{0, 2, -5}, Vector{0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 0);
}

TEST(Raycasting, RayOriginInsideSphere)
{
    Ray ray{Point{0, 0, 0}, Vector{0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_DOUBLE_EQ(xs(0).t, -1);
    EXPECT_DOUBLE_EQ(xs(1).t, 1);
}

TEST(Raycasting, RayIsBehindSphere)
{
    Ray ray{Point{0, 0, 5}, Vector{0, 0, 1}};
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
    Ray ray{Point{0, 0, -5}, Vector{0, 0, 1}};
    Sphere s{};
    auto xs = ray.intersect(s);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_EQ(xs(0).shape, s);
    EXPECT_EQ(xs(1).shape, s);
}

TEST(Intersections, SortedByIncreasingT)
{
    Sphere s{};
    Intersection i1{5, s};
    Intersection i2{7, s};
    Intersection i3{-3, s};
    Intersection i4{2, s};
    Intersections xs{ {i1, i2, i3, i4} };
    EXPECT_EQ(xs(0).t, -3);
    EXPECT_EQ(xs(1).t, 2);
    EXPECT_EQ(xs(2).t, 5);
    EXPECT_EQ(xs(3).t, 7);
}

TEST(Intersections, FindHitWhenWithAllPositiveT)
{
    Sphere s{};
    Intersection i1{1, s};
    Intersection i2{2, s};
    Intersections xs{};
    xs.add(i2);
    xs.add(i1);
    auto i = xs.findHit();
    EXPECT_TRUE(i.isHit);
    EXPECT_EQ(i, i1);
}

TEST(Intersections, FindHitWhenWithSomeNegativeT)
{
    Sphere s{};
    Intersection i1{-1, s};
    Intersection i2{1, s};
    Intersections xs{};
    xs.add(i2);
    xs.add(i1);
    auto i = xs.findHit();
    EXPECT_TRUE(i.isHit);
    EXPECT_EQ(i, i2);
}

TEST(Intersections, FindHitWhenWithAllNegativeT)
{
    Sphere s{};
    Intersection i1{-2, s};
    Intersection i2{-1, s};
    Intersections xs{};
    xs.add(i2);
    xs.add(i1);
    auto i = xs.findHit();
    // i should be a miss
    EXPECT_FALSE(i.isHit);

}

TEST(Intersections, HitIsAlwaysLowestNonNegative)
{
    Sphere s{};
    Intersection i1{5, s};
    Intersection i2{7, s};
    Intersection i3{-3, s};
    Intersection i4{2, s};
    Intersections xs{};
    xs.add(i1);
    xs.add(i2);
    xs.add(i3);
    xs.add(i4);
    auto i = xs.findHit();
    EXPECT_TRUE(i.isHit);
    EXPECT_EQ(i, i4);
}

TEST(Raycasting, TranslatingRays)
{
    Ray r{ Point{1, 2, 3}, Vector{0, 1, 0} };
    auto t = Transform::translation(3., 4., 5.);
    auto r2 = r.transform(t);
    EXPECT_EQ(r2.getOrigin(), Point(4, 6, 8));
    EXPECT_EQ(r2.getDirection(), Vector(0, 1, 0));
}

TEST(Raycasting, ScalingRays)
{
    Ray r{ Point{1, 2, 3}, Vector{0, 1, 0} };
    auto t = Transform::scale(2., 3., 4.);
    auto r2 = r.transform(t);
    EXPECT_EQ(r2.getOrigin(), Point(2, 6, 12));
    EXPECT_EQ(r2.getDirection(), Vector(0, 3, 0));
}

