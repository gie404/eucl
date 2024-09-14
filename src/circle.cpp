#include <cmath>

#include "circle.h"
#include "point.h"
#include "config.h"

using namespace std;

Circle::Circle(Point &c, double rSq)
{
    par1 = &c;
    this->rSq = rSq;
    par2 = nullptr;

}

Circle::Circle(const Point &parent1, const Point &parent2)
{
    // parent1 is always a center of the circle, no need to store it separately
    rSq = (parent1.x - parent2.x)*(parent1.x - parent2.x) + (parent1.y - parent2.y)*(parent1.y - parent2.y);
    par1 = &parent1;
    par2 = &parent2;
    type = 1;
}

bool Circle::operator==(const Circle &c) const
{
    return fabs(par1->x - c.par1->x) < EPS && fabs(par1->y - c.par1->y) < EPS && fabs(rSq - c.rSq) < EPS;
}

ostream &operator<<(ostream &output, const Circle &c) {
    output << "c(" << c.par1->x << ", " << c.par1->y << ", " << c.rSq << ")";
    return output;
}