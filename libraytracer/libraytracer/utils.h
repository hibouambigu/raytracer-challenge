#pragma once

#include <cmath>
#include <numbers>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Approximate equivalence for doubles. Handles float errors (via Epsilon).
inline bool APPROX_EQ(const double a, const double b)
{
    constexpr double EPSILON{ 0.00001 };
    return std::abs(a - b) < EPSILON;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Some consts to keep code less noisy
constexpr double PI = std::numbers::pi;
constexpr double HALF_PI = PI / 2.;
constexpr double THIRD_PI = PI / 3.;
constexpr double QUARTER_PI = PI / 4.;
constexpr double SQRT_2 = std::numbers::sqrt2;


