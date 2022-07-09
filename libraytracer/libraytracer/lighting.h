////////////////////////////////////////////////////////////////////////////////////////////////////
///     Raytracer Libs: Lighting
///     Point and other types of lighting sources and routines
///     Stacy Gaudreau
///     08.07.2022
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "tuples.h"
#include "colours.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Light
////////////////////////////////////////////////////////////////////////////////////////////////////
class Light
{
  public:
    Light(Tuple position, Colour colour = Colour{1, 1, 1});

    Colour colour;
    Tuple position;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PointLight
////////////////////////////////////////////////////////////////////////////////////////////////////
class PointLight : public Light
{
  public:
    PointLight(Tuple position, Colour colour);
};


