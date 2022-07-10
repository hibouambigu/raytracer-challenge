////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: World
///     Contains arbitrary scene geometry and raycasting methods
///     Stacy Gaudreau
///     09.07.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>

#include "shapes.h"
#include "lighting.h"
#include "rays.h"
#include "intersection.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IntersectionState
////////////////////////////////////////////////////////////////////////////////////////////////////
struct IntersectionState
{
    IntersectionState(Intersection& i, Ray& ray);
    double t;
    Shape& shape;
    Tuple point;
    Tuple eye;
    Tuple normal;
    bool isInsideShape;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// World
////////////////////////////////////////////////////////////////////////////////////////////////////
class World
{
  public:
    World();
    /// True if there are no objects in the World.
    [[nodiscard]] bool isEmpty() const;
    /// False if no lights have been added to the World, yet.
    [[nodiscard]] bool hasLighting() const;
    /// Add a Light() to the World.
    void addLight(Light* light);
    /// Add a Shape() to the World.
    void addShape(Shape* shape);
    /// Set the first Light() in the World.
    void setLight(Light* light);
    /// Get the first Light() for this world.
    Light getLight();
    /// Check if an object exists in this World or not.
    bool containsObject(const Shape& shape);
    /// Intersect this World() with a Ray() and return the sorted Intersections.
    Intersections intersect(Ray ray);
    /// Encapsulate some pre-computed state about an intersection, for use in shading pixels.
    static IntersectionState computeIntersectionState(Intersection i, Ray ray);
    /// Compute shading at a given Intersection() with a Ray().
    Colour shadeIntersection(Intersection i, Ray ray);
    /// Cast a Ray() and compute a given pixel Colour() for it.
    Colour traceRayToPixel(Ray ray);

  private:
    Colour shadeIntersectionState(IntersectionState iState);
    std::vector<Light*> lights;
    std::vector<Shape*> objects;
};
