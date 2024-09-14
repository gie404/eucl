#include <cmath>
#include "point.h"
#include "config.h"

using namespace std;

Point::Point()
{
    x = y = 0;
    par1 = par2 = nullptr;
}

Point::Point(double x, double y, Curve *par1, Curve *par2)
{
    this->x = x;
    this->y = y;
    this->par1 = par1;
    this->par2 = par2;
}

bool Point::operator==(const Point &p) const
{
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
}

ostream &operator<<(ostream &output, const Point &p)
{
    output << "p(" << p.x << ", " << p.y << ")";
    return output;
}