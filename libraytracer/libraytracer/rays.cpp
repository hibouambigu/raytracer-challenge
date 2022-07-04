#include "rays.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
Ray::Ray(Point origin, Vector direction)
: origin(origin),
  direction(direction)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Point Ray::getOrigin() const
{
    return origin;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Vector Ray::getdirection() const
{
    return direction;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple Ray::position(double t)
{
    return origin + direction * t;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double> Ray::intersect(Sphere sphere)
{
    std::vector<double> intersections;
    const auto vSphereToRay = origin - sphere.position;
    const auto a = Tuple::dot(direction, direction);
    const auto b = 2.0 * Tuple::dot(direction, vSphereToRay);
    const auto c = Tuple::dot(vSphereToRay, vSphereToRay) - 1.0;
    const auto discriminant = b * b - 4.0 * a * c;
    const auto SQRT_D = std::sqrt(discriminant);
    const auto TWO_A = a * 2.0;
    if (discriminant >= 0)
    {
        intersections.push_back( (-b - SQRT_D) / TWO_A );
        intersections.push_back( (-b + SQRT_D) / TWO_A );
    }
    return intersections;
}
