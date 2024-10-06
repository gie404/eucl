#ifndef EUCL_POINT
#define EUCL_POINT
#include <ostream>
#include "element.h"

class Curve;

class Point : public Element
{
public:
    double x;
    double y;
    const Curve *par1;
    const Curve *par2;
    mutable size_t id = 123456;

    Point();

    Point(double x, double y,const Curve *par1, const Curve *par2);

    bool operator==(const Point &p) const;

    friend std::ostream &operator<<(std::ostream &output, const Point &p);
};


#endif /* EUCL_POINT */
