#ifndef EUCL_CURVE
#define EUCL_CURVE
class Point;

class Curve
{
public:
    int type;
    const Point *par1;
    const Point *par2;
};


#endif /* EUCL_CURVE */
