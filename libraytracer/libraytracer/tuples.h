#pragma once

#include <cmath>

constexpr double EPSILON{ 0.00001 };
/// Approximate equivalence for doubles. Handles float errors (via Epsilon).
inline bool ApproxEqual(const double& a, const double& b)
{
    return fabs(a - b) < EPSILON;
}


constexpr size_t TUPLE_LENGTH{ 4 };

struct Tuple
{
    Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w){};
    Tuple() = default;

    static Tuple Vector(double x, double y, double z) { return { x, y, z, 0.0 }; };
    static Tuple Point(double x, double y, double z) { return { x, y, z, 1.0 }; };

    friend bool operator==(const Tuple& a, const Tuple& b)
    {
        return !(a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
    }

    friend Tuple operator+(const Tuple& a, const Tuple& b)
    {
        return Tuple{ a.x + b.x, a.y + b.y, a.z + b.z,
                      a.w + b.w };
    }

    friend Tuple operator*(const Tuple& a, const double& s)
    {
        return Tuple{ a.x * s, a.y * s, a.z * s, a.w * s };
    }

    friend Tuple operator/(const Tuple& a, const double& s)
    {
        return Tuple{ a.x / s, a.y / s, a.z / s, a.w / s };
    }

    friend Tuple operator-(const Tuple& a, const Tuple& b)
    {
        return Tuple{ a.x - b.x, a.y - b.y, a.z - b.z,
                      a.w - b.w };
    }

    /// negate the tuple (ie: subtract it from the zero vector)
    Tuple operator-() { return Tuple{ 0 - x, 0 - y, 0 - z, 0 - w }; }

    double magnitude() const
    {
        return sqrt(x * x + y * y + z * z +
                    w * w);
    };

    static Tuple normalize(const Tuple& t)
    {
        auto const M = t.magnitude();
        return Tuple{ t.x / M, t.y / M, t.z / M, t.w / M };
    }

    static double dot(const Tuple& a, const Tuple& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z +
               a.w * b.w;
    }

    static Tuple cross(const Tuple& a, const Tuple& b)
    {
        constexpr int X{0}, Y{1}, Z{2};
        return Tuple::Vector(
            (a.y * b.z - a.z * b.y),
            (a.z * b.x - a.x * b.z),
            (a.x * b.y - a.y * b.x)
        );
    }

    bool isPoint() { return w == 1.0; };
    bool isVector() { return w == 0.0; };

    double x, y, z, w;
};