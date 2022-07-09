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


////////////////////////////////////////////////////////////////////////////////////////////////////
/// World
////////////////////////////////////////////////////////////////////////////////////////////////////
class World
{
  public:
    World();
    /// True if there are no objects in the World.
    bool isEmpty() const;
    /// False if no lights have been added to the World, yet.
    bool hasLighting() const;
    /// Add a Light() to the World.
    void addLight(Light* newLight);
    /// Add a Shape() to the World.
    void addShape(Shape* shape);
    /// Get the lighting for this world.
    Light getLight();
    /// Check if an object is in this World or not.
    bool containsObject(const Shape& shape);

  private:
    Light* light;
    std::vector<Shape*> objects;
};
