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
#include "matrix.h"
#include <cmath>
#include <vector>


////////////////////////////////////////////////////////////////////////////////////////////////////
class Ray
{
  public:
    Ray(Tuple origin, Tuple direction);
    [[nodiscard]] Tuple getOrigin() const;
    [[nodiscard]] Tuple getDirection() const;
    /// Get the position at the given distance t along the ray
    Tuple position(double t);
    /// Intersect this Ray() with a Sphere(). Returns collection of t values where intersections occur.
    Intersections intersect(Sphere& sphere);
    /// Apply a Transform() Matrix() to this ray.
    Ray transform(Matrix<double, 4>& t);


  private:
    Tuple origin;
    Tuple direction;
};


