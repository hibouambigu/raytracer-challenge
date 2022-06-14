#include <iostream>
#include <libraytracer/tuples.h>
#include <libraytracer/matrix_2d.h>


struct Projectile
{
    Projectile(Tuple pos, Tuple v) : pos(pos), v(v) {};
    Tuple pos, v;
    double getX() { return pos.x; };
    double getY() { return pos.y; };
};

struct Environment
{
    Environment(Vector gravity, Vector wind) : g(gravity), f(wind){};
    Vector g, f;

    /// returns a new projectile after 1 unit of time has passed
    static Projectile tick(const Environment& e, const Projectile& p)
    {
        return {p.pos + p.v, p.v + e.g + e.f};
    }
};

void run_projectile()
{
    auto p = Projectile(
                 Point(0, 1, 0),
                 Tuple::normalize(Vector(2, 2, 0))
                 );

    auto e = Environment(
                 Vector(0, -0.01, 0),
                 Vector(-0.01, 0, 0)
                 );

    while (p.getY() > 0)
    {
        std::cout << "Pos: (" << p.getX() << ", " << p.getY() <<")\n";
        p = Environment::tick(e, p);
    };
}

int main()
{
//    run_projectile();
    auto matrix = Matrix2D<Colour>(5, 10);
    matrix.set(4, 8, Colour{.25, .5, .6667});
    matrix.set(3, 7, Colour{.75, .2, .3});
    std::cout << matrix.get(4, 8) << "\n" << matrix.get(3, 7) << "\n";


    return 1;
}