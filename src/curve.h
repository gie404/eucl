#ifndef EUCL_CURVE
#define EUCL_CURVE
#include "element.h"

class Point;

class Curve : public Element
{
public:
    int type;
    mutable size_t id;
    const Point *par1;
    const Point *par2;
};


#endif /* EUCL_CURVE */
