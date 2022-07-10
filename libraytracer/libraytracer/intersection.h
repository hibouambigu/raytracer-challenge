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

////////////////////////////////////////////////////////////////////////////////////////////////////
class Shape;
struct Intersection
{
    /// Contains the time (t) an intersection with a Shape() takes place at.
    Intersection(double t, Shape& shape);
    bool operator<(const Intersection& b) const;
    bool operator==(const Intersection& b) const;
    /// Move assignment
    //Intersection& operator=(Intersection&& b);
    /// Copy assignment
    //Intersection& operator=(const Intersection& b);
    /// Make a new Intersection() where the hit has missed, with a unit Sphere().
    ///     For use in hit detection.
    static Intersection makeMissedHit();

    double t;
    Shape& shape;
    bool isHit; // true if this Intersection() is a visible "hit" in the scene
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Intersections
{
  public:
    /// Construct a collection of intersection objects.
    Intersections();
    explicit Intersections(std::vector<Intersection> ints);
    /// Concatenate two collections of Intersections.
    friend Intersections operator+(const Intersections& A, const Intersections& B);
    /// Add a new intersection to the collection.
    void add(Intersection& intersection);
    /// Get the nth intersection in the collection.
    Intersection operator()(size_t n) const;
    /// Get the number of intersections.
    [[nodiscard]] size_t count() const;
    /// Find the significant visible intersection, aka: "hit".
    [[nodiscard]] Intersection findHit();
    /// Sort a vector of intersections by ascending t value.
    static void sortIntersectionsAscendingTime(std::vector<Intersection>& intersections);

  private:
    std::vector<Intersection> intersections;
    /// Sorts intersections vector in ascending order of t.
    void sortIntersections();
};