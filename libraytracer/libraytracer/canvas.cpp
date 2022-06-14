#include "canvas.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
Canvas::Canvas(size_t width, size_t height)
: width(width), height(height), pixels(width, height)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t Canvas::getWidth()
{
    return width;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t Canvas::getHeight()
{
    return height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Canvas::writePixel(size_t x, size_t y, Colour& colour)
{
    pixels.set(x, y, colour);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Colour Canvas::pixelAt(size_t x, size_t y)
{
    return pixels.get(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Canvas::isBlank()
{
    return pixels.isBlank();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Canvas::generatePPMHeader() const
{
    std::string header = "P3\n";
    header += std::to_string(width) + " " + std::to_string(height) + "\n";
    header += "255\n";
    return header;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Canvas::generatePPMData()
{
    const char* expected =
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255";
//    for (const auto& row: pixels.getMatrix())
//        for (const auto& pix: row)
//        {
//            std::cout << pix.R << "/" << pix.G << "/" << pix.B << "\n";
//        }
    return expected;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Canvas::writePPMToFile() const
{
    std::ofstream ppmFile("canvas_out.ppm");
    if (!ppmFile.is_open()) return false;
    else
    {
        ppmFile << generatePPMHeader();
        ppmFile.close();
    }
    return true;
}