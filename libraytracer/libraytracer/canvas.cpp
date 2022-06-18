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
std::string Canvas::toPPM()
{
    std::string ppm{};
    for (size_t y{}; y < pixels.getHeight(); y++)
        ppm += generatePPMDataRow(y);
    return ppm;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Canvas::generatePPMDataRow(size_t y)
{
    constexpr size_t CHAR_LIMIT{ 70 };  // PPM image format specification for length of lines
    std::string rowData{};
    size_t nChars{};
    for (size_t x{}; x < pixels.getWidth(); x++)
    {
        auto const pixel = pixels.get(x, y);
        std::vector<std::string> rgb;
        rgb.push_back(std::to_string(Colour::rgbToPPM(pixel.R)));
        rgb.push_back(std::to_string(Colour::rgbToPPM(pixel.G)));
        rgb.push_back(std::to_string(Colour::rgbToPPM(pixel.B)));
        for (const auto& p: rgb)
        {
            if ((nChars + p.length()+1) > CHAR_LIMIT)
            {
                rowData.replace(rowData.size()-1, 1, "\n");
                nChars = p.length() + 1;
            }
            else
            {
                nChars += p.length()+1;
            }
            rowData += p + " ";
        }
    }
    rowData.replace(rowData.size()-1, 1, "\n");
    return rowData;
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
