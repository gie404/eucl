#ifndef EUCL_POINT
#define EUCL_POINT
#include <ostream>

class Curve;

class Point
{
public:
    double x;
    double y;
    const Curve *par1;
    const Curve *par2;

    Point();

    Point(double x, double y, Curve *par1, Curve *par2);

    bool operator==(const Point &p) const;

    friend std::ostream &operator<<(std::ostream &output, const Point &p);
};


#endif /* EUCL_POINT */
