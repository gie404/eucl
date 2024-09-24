#include <cmath>
#include <iostream>
#include "intersect.h"
#include "point.h"
#include "curve.h"
#include "line.h"
#include "circle.h"
#include "config.h"

int intersect(const Line &l1, const Line &l2, Point &res)
{
    const double d = l1.nx * l2.ny - l1.ny * l2.nx;
    if (fabs(d) < EPS)
    {
        return 0;
    }
    res.x = (-l1.ny * l2.c + l2.ny * l1.c) / d;
    res.y = (-l2.nx * l1.c + l1.nx * l2.c) / d;
    res.par1 = &l1;
    res.par2 = &l2;
    return 1;
}
/*
X = <X,N>N + <X,T>T
<X,N> = c
<X,X> - 2<X,O> + <O,O> - r^2 = 0
c^2 + t^2 -2c<N,O>-2t<T,O> + <O,O> - r^2 = 0
*/
int intersect(const Line &l, const Circle &c, Point &res1, Point &res2)
{
    const double a1 = l.ny * c.par1->x - l.nx * c.par1->y;
    const double a2 = c.par1->x * c.par1->x + c.par1->y * c.par1->y + l.c * l.c - c.rSq - 2 * l.c * (l.nx * c.par1->x + l.ny * c.par1->y);
    const double d = a1 * a1 - a2;
    if (d < -EPS)
    {
        return 0;
    }
    if (fabs(d) < EPS)
    {
        res1.x = l.c * l.nx + a1 * l.ny;
        res1.y = l.c * l.ny - a1 * l.nx;
        res1.par1 = &l;
        res1.par2 = &c;
        return 1;
    }
    const double sqrtd = std::sqrt(d);
    const double t1 = -a1 - sqrtd;
    const double t2 = -a1 + sqrtd;

    res1.x = l.c * l.nx - t1 * l.ny;
    res1.y = l.c * l.ny + t1 * l.nx;
    res1.par1 = &l;
    res1.par2 = &c;

    res2.x = l.c * l.nx - t2 * l.ny;
    res2.y = l.c * l.ny + t2 * l.nx;
    res2.par1 = &l;
    res2.par2 = &c;
    return 2;
}

int intersect(const Circle &c1, const Circle &c2, Point &res1, Point &res2)
{
    if (*c1.par1 == *c2.par1) {
        return 0;
    }
    
    double nx = c2.par1->x - c1.par1->x;
    double ny = c2.par1->y - c1.par1->y;
    double n = hypot(nx, ny);
    nx /= n;
    ny /= n;
    double c = c2.par1->x * c2.par1->x + c2.par1->y * c2.par1->y - c1.par1->x * c1.par1->x - c1.par1->y * c1.par1->y + c1.rSq - c2.rSq;
    c /= 2 * n;
    Line l = Line(nx, ny, c);
    int count = intersect(l, c2, res1, res2);
    res1.par1 = &c1;
    res2.par1 = &c1;
    return count;
}