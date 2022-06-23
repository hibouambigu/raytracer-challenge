#include "tuples.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
bool operator==(const Tuple& a, const Tuple& b)
{
    return APPROX_EQ(a.x, b.x) && APPROX_EQ(a.y, b.y) && APPROX_EQ(a.z, b.z) && APPROX_EQ(a.w, b.w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple operator+(const Tuple& a, const Tuple& b)
{
    return Tuple{ a.x + b.x, a.y + b.y, a.z + b.z,
                  a.w + b.w };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple operator*(const Tuple& a, const double& s)
{
    return Tuple{ a.x * s, a.y * s, a.z * s, a.w * s };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple operator/(const Tuple& a, const double& s)
{
    return Tuple{ a.x / s, a.y / s, a.z / s, a.w / s };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple operator-(const Tuple& a, const Tuple& b)
{
    return Tuple{ a.x - b.x, a.y - b.y, a.z - b.z,a.w - b.w };
}


////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple Tuple::operator-() const
{
    return Tuple{ 0 - x, 0 - y, 0 - z, 0 - w };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
double Tuple::magnitude() const
{
    return sqrt(x * x + y * y + z * z + w * w);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple Tuple::normalize(const Tuple& t)
{
    auto const M = t.magnitude();
    return Tuple{ t.x / M, t.y / M, t.z / M, t.w / M };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
double Tuple::dot(const Tuple& a, const Tuple& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Tuple::isPoint() const { return w == 1.0; };

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Tuple::isVector() const { return w == 0.0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple cross(const Tuple& a, const Tuple& b)
{
    return Vector(
        (a.y * b.z - a.z * b.y),
        (a.z * b.x - a.x * b.z),
        (a.x * b.y - a.y * b.x)
    );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
double& Tuple::operator()(size_t i)
{
    switch(i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        return x;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
double Tuple::operator()(size_t i) const
{
    switch(i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        return x;
    }
}
