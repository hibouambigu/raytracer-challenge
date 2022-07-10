#include "world.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IntersectionState
////////////////////////////////////////////////////////////////////////////////////////////////////
IntersectionState::IntersectionState(Intersection& i, Ray& ray)
:   shape(i.shape),
    t(i.t),
    point(ray.position(t)),
    eye(-ray.getDirection()),
    normal(shape.normalAt(point)),
    isInsideShape(Tuple::dot(normal, eye) < 0)
{
    // invert the normal if we are inside the shape object, so that the shading
    //  will illuminate the surface properly
    if (isInsideShape)
        normal = -normal;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// World
////////////////////////////////////////////////////////////////////////////////////////////////////
World::World() {}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool World::isEmpty() const
{
    return objects.empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool World::hasLighting() const
{
    return !lights.empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void World::addLight(Light* light)
{
    lights.push_back(light);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void World::addShape(Shape* shape)
{
    objects.push_back(shape);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void World::setLight(Light* light)
{
    lights.insert(lights.begin(), light);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Light World::getLight()
{
    if (hasLighting())
        return *lights.front();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool World::containsObject(const Shape& shape)
{
    bool containsObjectOrNot{false};
    for (const auto& o: objects) {
        if (*o == shape) {
            containsObjectOrNot = true;
            break;
        }
    }
    return containsObjectOrNot;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Intersections World::intersect(Ray ray)
{
    // intersect each object in the World with a Ray,
    //  building a collection of aggregated Intersections
    Intersections ints{};
    for(const auto& o: objects) {
        ints = ints + o->intersect(ray);
    }
    return ints;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
IntersectionState World::computeIntersectionState(Intersection i, Ray ray)
{
    return {i, ray};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Colour World::shadeIntersectionState(IntersectionState iState)
{
    return iState.shape.lightPixel(getLight(), iState.point, iState.eye, iState.normal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Colour World::shadeIntersection(Intersection i, Ray ray)
{
    return shadeIntersectionState(computeIntersectionState(i, ray));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Colour World::traceRayToPixel(Ray ray)
{
    Intersection hit = intersect(ray).findHit();
    return hit.isHit ? shadeIntersection(hit, ray) : Colour{};
}
