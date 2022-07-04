////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Shapes
///     Provides geomtetric shapes (Sphere, etc.)
///     Stacy Gaudreau
///     03.07.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "tuples.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

class Shape
{
  public:
    /// Construct a new Shape() object.
    explicit Shape(Point position);
    /// Compare identity. Are a and b the same shape?
    friend bool operator== (const Shape& a, const Shape& b);

    Point position; /// position of the Shape in the Scene right now
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Sphere : public Shape
{
    Sphere() : Shape({}) {};
    explicit Sphere(Point position) : Shape(position) {};
};
