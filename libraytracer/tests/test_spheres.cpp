#include "intersection.h"
#include "shapes.h"
#include "matrix.h"
#include "rays.h"
#include "gtest/gtest.h"

#include <numbers>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Ray-Sphere intersections
////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SphereIntersections, IntersectingScaledSphereWithRay)
{
    Sphere s{};
    Ray r{ Point{0, 0, -5}, Vector{0, 0, 1} };
    s.setTransform(Transform::scale(2., 2., 2.));
    auto xs{ s.intersect(r) };
    EXPECT_EQ(xs.count(), 2);
    EXPECT_EQ(xs(0).t, 3.);
    EXPECT_EQ(xs(1).t, 7.);
}

TEST(SphereIntersections, IntersectingTranslatedSphereWithRay)
{
    Sphere s{};
    Ray r{ Point{0, 0, -5}, Vector{0, 0, 1} };
    s.setTransform(Transform::translation(5., 0., 0.));
    auto xs{ s.intersect(r) };
    EXPECT_EQ(xs.count(), 0);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Calculating Normals to a Sphere
////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SphereNormals, NormalAtPointOnXAxis)
{
    Sphere s{};
    auto n = s.normalAt(Point{1, 0, 0});
    EXPECT_EQ(n, Vector(1, 0, 0));
}

TEST(SphereNormals, NormalAtPointOnYAxis)
{
    Sphere s{};
    auto n = s.normalAt(Point{0, 1, 0});
    EXPECT_EQ(n, Vector(0, 1, 0));
}

TEST(SphereNormals, NormalAtPointOnZAxis)
{
    Sphere s{};
    auto n = s.normalAt(Point{0, 0, 1});
    EXPECT_EQ(n, Vector(0, 0, 1));
}

TEST(SphereNormals, NormalAtNonAxialPoint)
{
    using namespace std::numbers;
    Sphere s{};
    auto n = s.normalAt(Point{sqrt3/3., sqrt3/3., sqrt3/3.});
    EXPECT_EQ(n, Vector(sqrt3/3., sqrt3/3., sqrt3/3.));
}

TEST(SphereNormals, IsNormalizedVector)
{
    using namespace std::numbers;
    Sphere s{};
    auto n = s.normalAt(Point{sqrt3/3., sqrt3/3., sqrt3/3.});
    EXPECT_EQ(n, n.normalize());
}

TEST(SphereNormals, NormalOnTranslatedSphere)
{
    Sphere s{};
    s.setTransform(Transform::translation(0., 1., 0.));
    auto n = s.normalAt(Point{0, 1.70711, -0.70711});
    EXPECT_EQ(n, Vector(0, 0.70711, -0.70711));
}

TEST(SphereNormals, NormalOnTransformedSphere)
{
    using namespace std::numbers;
    Sphere s{};
    auto M = Transform::scale(1., 0.5, 1.) * Transform::rotateZ(pi/5.0);
    s.setTransform(M);
    auto n = s.normalAt(Point{0., sqrt2/2.0, -sqrt2/2.0});
    EXPECT_EQ(n, Vector(0, 0.97014, -0.24254));
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sphere Materials
////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SphereMaterials, SphereHasDefaultMaterial)
{
    Sphere s{};
    Material m{s.getMaterial()};
    EXPECT_EQ(m, Material());
}

TEST(SphereMaterials, AssigningMaterialToSphere)
{
    Sphere s{};
    Material m{};
    m.ambient = 1.0;
    s.setMaterial(m);
    EXPECT_EQ(m, s.getMaterial());
}