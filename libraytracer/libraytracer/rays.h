////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Rays, Raycasting and Intersections
///     Provides Rays, raycasting and intersection geometry
///     Stacy Gaudreau
///     03.07.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <cmath>
#include "tuples.h"
#include "sphere.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
class Ray
{
  public:
    Ray(Point origin, Vector direction);
    [[nodiscard]] Point getOrigin() const;
    [[nodiscard]] Vector getdirection() const;
    /// Get the position at the given distance t along the ray
    Tuple position(double t);
    /// Intersect this Ray() with a Sphere(). Returns collection of t values where intersections occur.
    std::vector<double> intersect(Sphere sphere);

  private:
    Point origin;
    Vector direction;
};


