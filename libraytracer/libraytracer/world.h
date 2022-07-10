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
    void addLight(Light* newLight);
    /// Add a Shape() to the World.
    void addShape(Shape* shape);
    /// Get the lighting for this world.
    Light getLight();
    /// Check if an object exists in this World or not.
    bool containsObject(const Shape& shape);
    /// Intersect this World() with a Ray() and return the sorted Intersections.
    Intersections intersect(Ray ray);


  private:
    Light* light;
    std::vector<Shape*> objects;
};
