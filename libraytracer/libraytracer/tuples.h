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
    Tuple(double x, double y, double z, double w);
    Tuple();

    static Tuple Vector(double x, double y, double z) { return {x, y, z, 0.0}; };
    static Tuple Point(double x, double y, double z) { return {x, y, z, 1.0}; };

    friend bool operator==(const Tuple& a, const Tuple& b)
    {
        for (size_t i{}; i < TUPLE_LENGTH; ++i)
            if (!ApproxEqual(a.tuple[i], a.tuple[i])) return false;
        return true;
    }

    friend Tuple operator+(const Tuple& a, const Tuple& b)
    {
        return Tuple{ a.tuple[0] + b.tuple[0], a.tuple[1] + b.tuple[1], a.tuple[2] + b.tuple[2],
                      a.tuple[3] + b.tuple[3] };
    }

    friend Tuple operator*(const Tuple& a, const double& s)
    {
        return Tuple{ a.tuple[0] * s, a.tuple[1] * s, a.tuple[2] * s, a.tuple[3] * s };
    }

    friend Tuple operator/(const Tuple& a, const double& s)
    {
        return Tuple{ a.tuple[0] / s, a.tuple[1] / s, a.tuple[2] / s, a.tuple[3] / s };
    }

    friend Tuple operator-(const Tuple& a, const Tuple& b)
    {
        return Tuple{ a.tuple[0] - b.tuple[0], a.tuple[1] - b.tuple[1], a.tuple[2] - b.tuple[2],
                      a.tuple[3] - b.tuple[3] };
    }

    /// negate the tuple (ie: subtract it from the zero vector)
    Tuple operator-() { return Tuple{ 0 - tuple[0], 0 - tuple[1], 0 - tuple[2], 0 - tuple[3] }; }

    double magnitude() const
    {
        return sqrt(tuple[0] * tuple[0] + tuple[1] * tuple[1] + tuple[2] * tuple[2] +
                    tuple[3] * tuple[3]);
    };

    static Tuple normalize(const Tuple& t)
    {
        auto const M = t.magnitude();
        return Tuple{ t.tuple[0] / M, t.tuple[1] / M, t.tuple[2] / M, t.tuple[3] / M };
    }

    bool isPoint() { return tuple[3] == 1.0; };
    bool isVector() { return tuple[3] == 0.0; };

    double tuple[4]{};
};