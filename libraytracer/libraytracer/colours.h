#pragma once

#include <iostream>
#include "utils.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Colour
{
    Colour(double red, double green, double blue);
    Colour() = default;

    /// subtract two colours
    friend Colour operator-(const Colour& a, const Colour& b);
    /// add two colours
    friend Colour operator+(const Colour& a, const Colour& b);
    /// multiply a colour by a scalar
    friend Colour operator*(const Colour& c, const double s);
    /// multiply two colours (Hadamard Product)
    friend Colour operator*(const Colour& a, const Colour& b);
    /// colour equivalence
    friend bool operator==(const Colour& a, const Colour& b);
    /// print a stream representing this colour
    friend std::ostream& operator<<(std::ostream& os, const Colour& c);

    /// print a representation of this colour to stdout
    static void print(const Colour& colour)
    {
        std::cout << "RGB: " << colour.R << "/" << colour.G << "/" << colour.B << "\n";
    }

    double R, G, B;
};



