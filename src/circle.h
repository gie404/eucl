#ifndef EUCL_CIRCLE
#define EUCL_CIRCLE
#include <ostream>

#include "curve.h"

class Circle : public Curve
{
public:
    double rSq;

    Circle(Point &c, double r);

    Circle(const Point &parent1, const Point &parent2);

    bool operator==(const Circle &c) const;

    friend std::ostream &operator<<(std::ostream &output, const Circle &c);
};


#endif /* EUCL_CIRCLE */
