#include "materials.h"

#include <cmath>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Material
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
Material::Material()
:   colour(Colour{1, 1, 1}),
    ambient(0.1),
    diffuse(0.9),
    specular(0.9),
    shininess(200.0)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool operator==(const Material& a, const Material& b)
{
    return    a.colour == b.colour
           && a.ambient == b.ambient
           && a.diffuse == b.diffuse
           && a.specular == b.specular
           && a.shininess == b.shininess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Colour Material::getPixel(Light lighting, Tuple point, Tuple vEye, Tuple vNormal)
{
    // add together the material's ambient, diffuse and specular components.
    // components are weighted by the angles between the different vectors.
    // combine surface colour w. the light's colour
    const Colour effectiveColour = colour * lighting.colour;
    // direction to the light source
    Tuple vLight = (lighting.position - point).normalize();
    // the ambient contribution
    Colour ambientColour = effectiveColour * ambient;
    // compute diffuse and specular lighting components...
    Colour diffuseColour{}, specularColour{};
    // cosine of the angle btwn the light and normal vectors
    // a negative # means the light is on the other side of the surface.
    const double lightDotNormal = Tuple::dot(vLight, vNormal);
    if (lightDotNormal >= 0) {
        // light is on this side of the surface, so compute the diffuse
        diffuseColour = effectiveColour * diffuse * lightDotNormal;
        // a negative number means the light reflects away from the eye
        Tuple vReflect = Vector::reflect(-vLight, vNormal);
        const double reflectDotEye = Tuple::dot(vReflect, vEye);
        if (reflectDotEye >= 0) {
            // reflection is visible to the eye, so compute the specular component
            const double reflectAmt = pow(reflectDotEye, shininess);
            specularColour = lighting.colour * specular * reflectAmt;
        }
    }
    // add the three components together for our final shaded pixel result
    return ambientColour + diffuseColour + specularColour;
}
