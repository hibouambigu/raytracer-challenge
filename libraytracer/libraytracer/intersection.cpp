#include "intersection.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
Intersection::Intersection(double t, Shape& shape)
: t(t), shape(shape), isHit(false)
{}

//////////////////////////////////////////////////////////////////////////////////////////////////////
bool Intersection::operator<(const Intersection& b) const
{
    return t < b.t;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
bool Intersection::operator==(const Intersection& b) const
{
    return t == b.t && shape == b.shape;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Intersection Intersection::makeMissedHit()
{
    Sphere s{};
    Intersection i{0, s};
    i.isHit = false;
    return {0, s};
}


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
Intersections::Intersections()
: intersections({})
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
Intersections::Intersections(std::vector<Intersection> ints)
: intersections({})
{
    for (const auto& i: ints) {
        intersections.push_back(i);
    }
    sortIntersections();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Intersections::add(Intersection& intersection)
{
    intersections.push_back(intersection);
    sortIntersections();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Intersection Intersections::operator()(size_t n) const
{
    return intersections.at(n);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t Intersections::count() const
{
    return intersections.size();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
Intersection Intersections::findHit()
{
    for (auto& i: intersections) {
        if (i.t >= 0) {
            i.isHit = true;
            return i;
        }
    }
    // if we've reached here, there is no hit..
    // so, we create a new missed hit intersection
    // and return that.
    return Intersection::makeMissedHit();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Intersections::sortIntersectionsAscendingTime(std::vector<Intersection>& intersections)
{
    // 1. convert to list
    std::list<Intersection> listOfInts{};
    for (const auto& i: intersections) {
        listOfInts.push_back(i);
    }
    // 2. sort in place
    listOfInts.sort();
    // 3. write back to vector
    // (this might be faster if iterate and copy to orig. vector?? -> need to profile.)
    intersections.clear();
    for (const auto& i: listOfInts) {
        intersections.push_back(i);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Intersections::sortIntersections()
{
    sortIntersectionsAscendingTime(intersections);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Intersections operator+(const Intersections& A, const Intersections& B)
{
    Intersections AB{};
    for (const auto& i: A.intersections) {
        AB.intersections.push_back(i);
    }
    for (const auto& i: B.intersections) {
        AB.intersections.push_back(i);
    }
    AB.sortIntersections();
    return AB;
}
