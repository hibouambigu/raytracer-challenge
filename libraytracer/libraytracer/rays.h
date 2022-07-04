////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Rays, Raycasting and Intersections
///     Provides Rays, raycasting and intersection geometry
///     Stacy Gaudreau
///     03.07.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "shapes.h"
#include "tuples.h"
#include "intersection.h"
#include <cmath>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////
class Ray
{
  public:
    Ray(Point origin, Vector direction);
    [[nodiscard]] Point getOrigin() const;
    [[nodiscard]] Vector getDirection() const;
    /// Get the position at the given distance t along the ray
    Tuple position(double t);
    /// Intersect this Ray() with a Sphere(). Returns collection of t values where intersections occur.
    Intersections intersect(Sphere& sphere);

  private:
    Point origin;
    Vector direction;
};


