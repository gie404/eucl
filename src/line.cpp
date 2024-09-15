#include <cmath>

#include "line.h"
#include "point.h"
#include "config.h"

using namespace std;

Line::Line(double nx, double ny, double c) {
    this->nx = nx;
    this->ny = ny;
    this->c = c;
    par1 = par2 = nullptr;
    type = 0;
}

Line::Line(const Point &parent1, const Point &parent2)
{
    // line equation <N,X> = c, <N, N> = 1
    nx = parent1.y - parent2.y;
    ny = parent2.x - parent1.x;
    const double n = hypot(nx, ny);
    c = parent1.y * parent2.x - parent1.x * parent2.y;
    nx /= n;
    ny /= n;
    c /= n;
    par1 = &parent1;
    par2 = &parent2;
    type = 0;
}

bool Line::operator==(const Line &l) const
{
    // check if both parents of l satisfy this line equation
    return fabs(nx * l.par1->x + ny * l.par1->y + c) < EPS && fabs(nx * l.par2->x + ny * l.par2->y + c) < EPS;
}

ostream &operator<<(ostream &output, const Line &l)
{
    output << "l(" << l.nx << ", " << l.ny << ", " << l.c << ")";
    return output;
}