#include "rays.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
Ray::Ray(Tuple origin, Tuple direction)
: origin(origin),
  direction(direction)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple Ray::getOrigin() const
{
    return origin;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple Ray::getDirection() const
{
    return direction;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple Ray::position(double t)
{
    return origin + direction * t;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Intersections Ray::intersect(Sphere& sphere)
{
    Intersections intersections;
    // we use the sphere-transformed ray's direction and
    //  origin in our calculations (*not* *this)
    Ray rayT = transform(sphere.getTransform().inverse());
    const Tuple rayDirection{ rayT.getDirection() };
    const Tuple rayOrigin{ rayT.getOrigin() };
    const auto vSphereToRay = rayOrigin - sphere.getPosition();
    const auto a = Tuple::dot(rayDirection, rayDirection);
    const auto b = 2.0 * Tuple::dot(rayDirection, vSphereToRay);
    const auto c = Tuple::dot(vSphereToRay, vSphereToRay) - 1.0;
    const auto discriminant = b * b - 4.0 * a * c;
    const auto SQRT_D = std::sqrt(discriminant);
    const auto TWO_A = a * 2.0;
    if (discriminant >= 0)
    {
        Intersection i1{ (-b - SQRT_D) / TWO_A, sphere };
        Intersection i2{ (-b + SQRT_D) / TWO_A, sphere };
        intersections.add( i1 );
        intersections.add( i2 );
    }
    return intersections;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ray Ray::transform(Matrix<double, 4> t) const
{
    auto o = t * origin;
    auto d = t * direction;
    return {o, d};
}
