#pragma once

#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Approximate equivalence for doubles. Handles float errors (via Epsilon).
inline bool APPROX_EQ(const double a, const double b)
{
    constexpr double EPSILON{ 0.00001 };
    return fabs(a - b) < EPSILON;
}
