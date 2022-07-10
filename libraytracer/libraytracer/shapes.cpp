#include "shapes.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Shape
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
Shape::Shape(Tuple position)
:   position(position),
    transformation(TransformationMatrix::identity())
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool operator==(const Shape& a, const Shape& b)
{
    return &a == &b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple Shape::getPosition() const
{
    return position;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TransformationMatrix Shape::getTransform() const
{
    return transformation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Shape::setTransform(TransformationMatrix t)
{
    transformation = t;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Shape::setMaterial(Material newMaterial) {
    material = newMaterial;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Material Shape::getMaterial() const
{
    return material;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Shape::setColour(Colour colour)
{
    material.colour = colour;
}
Colour Shape::lightPixel(Light lighting, Tuple point, Tuple eyeV, Tuple normalV)
{
    return material.getPixel(lighting, point, eyeV, normalV);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sphere
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple Sphere::normalAt(Tuple worldPoint)
{
    const TransformationMatrix inverseTransform = transformation.inverse();
    const auto objectPoint = inverseTransform * worldPoint;
    const auto objectNormal = objectPoint - Point{};
    auto worldNormal = inverseTransform.transposed() * objectNormal;
    worldNormal.w = 0.0; // hacky way of avoiding having another submatrix operation
    return worldNormal.normalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Intersections Sphere::intersect(Ray ray)
{
    Intersections intersections;
    // we use the sphere-transformed ray's direction and
    //  origin in our calculations
    Ray rayT = ray.transform(transformation.inverse());
    const Tuple rayDirection{ rayT.getDirection() };
    const Tuple rayOrigin{ rayT.getOrigin() };
    const auto vSphereToRay = rayOrigin - position;
    const auto a = Tuple::dot(rayDirection, rayDirection);
    const auto b = 2.0 * Tuple::dot(rayDirection, vSphereToRay);
    const auto c = Tuple::dot(vSphereToRay, vSphereToRay) - 1.0;
    const auto discriminant = b * b - 4.0 * a * c;
    const auto SQRT_D = std::sqrt(discriminant);
    const auto TWO_A = a * 2.0;
    if (discriminant >= 0)
    {
        Intersection i1{ (-b - SQRT_D) / TWO_A, *this };
        Intersection i2{ (-b + SQRT_D) / TWO_A, *this };
        intersections.add( i1 );
        intersections.add( i2 );
    }
    return intersections;
}
