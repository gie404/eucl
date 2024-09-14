#ifndef EUCL_INTERSECT
#define EUCL_INTERSECT
class Point;
class Line;
class Circle;

int intersect(const Line &l1, const Line &l2, Point &res);
int intersect(const Line &l, const Circle &c, Point &res1, Point &res2);
int intersect(const Circle &c1, const Circle &c2, Point &res1, Point &res2);

#endif /* EUCL_INTERSECT */
