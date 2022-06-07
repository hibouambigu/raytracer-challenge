#include <iostream>
#include <libraytracer/tuples.h>


struct Projectile
{
    Projectile(Tuple pos, Tuple v) : pos(pos), v(v) {};
    Tuple pos, v;
    double getX() { return pos.tuple[0]; };
    double getY() { return pos.tuple[1]; };
};

struct Environment
{
    Environment(Tuple gravity, Tuple wind) : g(gravity), f(wind){};
    Tuple g, f;

    /// returns a new projectile after 1 unit of time has passed
    static Projectile tick(const Environment& e, const Projectile& p)
    {
        return {p.pos + p.v, p.v + e.g + e.f};
    }

};

int main()
{
    auto p = Projectile(
                 Tuple::Point(0, 1, 0),
                 Tuple::normalize(Tuple::Vector(2, 2, 0))
                 );

    auto e = Environment(
                 Tuple::Vector(0, -0.01, 0),
                 Tuple::Vector(-0.01, 0, 0)
                 );

    while (p.getY() > 0)
    {
        std::cout << "Pos: (" << p.getX() << ", " << p.getY() <<")\n";
        p = Environment::tick(e, p);
    };
    return 1;
}