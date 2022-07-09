////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Shapes
///     Provides geomtetric shapes (Sphere, etc.)
///     Stacy Gaudreau
///     03.07.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "tuples.h"
#include "matrix.h"
#include "materials.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
class Shape
{
  public:
    /// Construct a new Shape object.
    explicit Shape(Tuple position);
    /// Compare identity. Are a and b the same shape?
    friend bool operator== (const Shape& a, const Shape& b);
    /// Get current position of this Shape
    Tuple getPosition() const;
    /// Get the transformation matrix applied to this Shape
    [[nodiscard]] TransformationMatrix getTransform() const;
    /// Set the transformation matrix applied to this Shape
    void setTransform(TransformationMatrix t);
    /// Set the material for this Shape to be rendered with
    void setMaterial(Material newMaterial);
    /// Get the material this Shape is rendered with
    [[nodiscard]] Material getMaterial() const;
    /// Calculate the normal vector at a specified **world** point on this shape
    virtual Tuple normalAt(Tuple worldPoint) = 0;
    /// Set the colour of this Shape's material.
    virtual void setColour(Colour colour);

  protected:
    Tuple position; /// position of the Shape in the Scene right now
    TransformationMatrix transformation;    /// the transformation to be applied during raycasting
    Material material;  /// The surface material to render this shape with.
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Sphere : public Shape
{
    Sphere() : Shape( Point{} ) {};
    explicit Sphere(Tuple position) : Shape(position) {};
    /// Calculate the normal vector at a specified **world** point on the Sphere.
    Tuple normalAt(Tuple worldPoint) override;
};
