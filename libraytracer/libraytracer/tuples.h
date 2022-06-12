#pragma once

#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Approximate equivalence for doubles. Handles float errors (via Epsilon).
inline bool ApproxEqual(const double& a, const double& b)
{
    constexpr double EPSILON{ 0.00001 };
    return fabs(a - b) < EPSILON;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Tuple
{
    Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w){};
    Tuple() = default;

    friend bool operator==(const Tuple& a, const Tuple& b);
    friend Tuple operator+(const Tuple& a, const Tuple& b);
    friend Tuple operator*(const Tuple& a, const double& s);
    friend Tuple operator/(const Tuple& a, const double& s);
    friend Tuple operator-(const Tuple& a, const Tuple& b);

    /// negate the tuple (ie: subtract it from the zero vector)
    Tuple operator-() const;
    double magnitude() const;
    static Tuple normalize(const Tuple& t);
    static double dot(const Tuple& a, const Tuple& b);
    bool isPoint() const;
    bool isVector() const;

    double x, y, z, w;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Vector : public Tuple
{
    Vector(double x, double y, double z) : Tuple(x, y, z, 0.0) {};
    Vector() : Tuple(0.0, 0.0, 0.0, 0.0) {};
};


////////////////////////////////////////////////////////////////////////////////////////////////////
struct Point : public Tuple
{
    Point(double x, double y, double z) : Tuple(x, y, z, 1.0) {};
    Point() : Tuple(0.0, 0.0, 0.0, 1.0) {};
};


////////////////////////////////////////////////////////////////////////////////////////////////////
Tuple cross(const Tuple& a, const Tuple& b);
