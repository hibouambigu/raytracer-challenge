////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Intersections
///     Tracks intersections between rays and shape geometry in a scene
///     Stacy Gaudreau
///     03.07.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "shapes.h"
#include <vector>
#include <list>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Intersection
{
    /// Contains the time (t) an intersection takes place at with a Shape().
    Intersection(double t, Shape& shape);
    bool operator<(const Intersection& b) const;
    double t;
    Shape& shape;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Intersections
{
  public:
    /// Construct a collection of intersection objects.
    Intersections();
    Intersections(std::vector<Intersection> ints);
    /// Add a new intersection to the collection.
    void add(Intersection& intersection);
    /// Get the nth intersection in the collection.
    Intersection operator()(size_t n) const;
    /// Get the number of intersections.
    [[nodiscard]] size_t count() const;

  private:
    std::vector<Intersection> intersections;
    /// Sorts intersections vector in ascending order of t.
    void sortIntersections();
};