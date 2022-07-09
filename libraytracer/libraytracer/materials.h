////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Materials
///     Surface materials for objects
///     Stacy Gaudreau
///     08.07.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "tuples.h"
#include "lighting.h"
#include "colours.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Material
////////////////////////////////////////////////////////////////////////////////////////////////////
class Material
{
  public:
    Material();
    /// Compare equality.
    friend bool operator== (const Material& a, const Material& b);
    /// Apply lighting to this material and compute a single pixel from it.
    Colour getPixel(Light lighting, Tuple point, Tuple eyeV, Tuple normalV);

    Colour colour;
    double ambient, diffuse, specular, shininess;
};