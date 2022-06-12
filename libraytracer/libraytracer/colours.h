#pragma once

struct Colour
{
    Colour(double x, double y, double z, double w) : x(x), y(y), z(z), w(w){};
    Colour() = default;

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
        return Tuple{ a.x - b.x, a.y - b.y, a.z - b.z,a.w - b.w };
    }

    /// negate the tuple (ie: subtract it from the zero vector)
    Tuple operator-() const { return Tuple{ 0 - x, 0 - y, 0 - z, 0 - w }; }

    double magnitude() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    };

    static Tuple normalize(const Tuple& t)
    {
        auto const M = t.magnitude();
        return Tuple{ t.x / M, t.y / M, t.z / M, t.w / M };
    }

    static double dot(const Tuple& a, const Tuple& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    inline bool isPoint() const { return w == 1.0; };
    inline bool isVector() const { return w == 0.0; };

    double x, y, z, w;
};


