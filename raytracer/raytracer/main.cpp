#include <iostream>
#include <libraytracer/tuples.h>
#include <libraytracer/matrix_2d.h>
#include <libraytracer/canvas.h>
#include <libraytracer/rays.h>


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
                 Tuple::normalize(Vector(1, 1.8, 0)) * 11.25
                 );

    auto e = Environment(
                 Vector(0, -0.1, 0),
                 Vector(-0.01, 0, 0)
                 );

    auto c = Canvas(900, 550);

    while (p.getY() > 0)
    {

        std::cout << "Pos: (" << p.getX() << ", " << p.getY() <<")\n";
        auto canvasX = static_cast<size_t>(p.getX());
        auto canvasY = static_cast<size_t>(c.getHeight()) - static_cast<size_t>(p.getY());
        std::cout << "On canvas: (" << canvasX << ", " << canvasY <<")\n";
        c.writePixel(canvasX, canvasY, Colour{.8, 0.0, .8});
        p = Environment::tick(e, p);
    };

    c.writePPMToFile();
}

void run_raycasted_sphere_demo()
{
    // draws a flattened sphere to the canvas in order to demo
    //  the raycaster engine
    std::cout << "Raycasted Sphere Demo\n";
    constexpr size_t CANVAS_SIZE{ 100 };
    constexpr size_t W{CANVAS_SIZE}, H{CANVAS_SIZE};
    constexpr size_t N_RAYS{ W * H };
    Canvas canvas{W, H};
    // sphere at origin
    Sphere s{};
    // transform sphere
    TransformationMatrix T =
        Transform::scale(.5, 1.0, 1.0);
    s.setTransform(T);
    // ray distance away from sphere origin on z-axis
    const Point rayOrigin{0., 0., -5.};
    constexpr double WALL_Z{ 10.0 };
    constexpr double WALL_SIZE{ 7.0 };
    constexpr double HALF_WALL_SIZE{WALL_SIZE / 2.0};
    constexpr double PIXEL_SIZE{ WALL_SIZE / CANVAS_SIZE};
    std::cout << "Begin raytracing..\n";
    size_t nRaysCasted{};
    for (size_t y{}; y < canvas.getHeight(); ++y) {
        const double worldY{ HALF_WALL_SIZE - PIXEL_SIZE * (double)y };
        for (size_t x{}; x < canvas.getWidth(); ++x) {
            const double worldX{ -HALF_WALL_SIZE + PIXEL_SIZE * (double)x };
            const Point rayPosition{
                static_cast<double>(worldX), static_cast<double>(worldY), WALL_Z
            };
            Ray r{ rayOrigin, Tuple::normalize(rayPosition - rayOrigin) };
            Intersections xs = r.intersect(s);
            const auto pixelHitSphere{ xs.findHit().isHit };
            if (pixelHitSphere)
                canvas.writePixel(x, y, Colour{.7, 0., 1.});
            nRaysCasted++;
        }
        double percentComplete{ (static_cast<double>(nRaysCasted) / N_RAYS) * 100. };
        std::cout << percentComplete << "%\n";
    }

    std::cout << "\nRaytracing complete. Rendering to PPM file...";
    // save the canvas to file
    canvas.writePPMToFile();
    std::cout << "\nPPM output file generated!\n";
}

int main()
{
    run_raycasted_sphere_demo();
    return 1;
}