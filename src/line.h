#ifndef EUCL_LINE
#define EUCL_LINE
#include <ostream>

#include "curve.h"

class Point;

class Line : public Curve
{
public:
    double nx;
    double ny;
    double c;

    Line(double _nx, double _ny, double _c);

    Line(const Point &parent1, const Point &parent2);

    bool operator==(const Line &l) const;

    friend std::ostream &operator<<(std::ostream &output, const Line &l);
};

#endif /* EUCL_LINE */
