#ifndef EUCL_BUILDER
#define EUCL_BUILDER
#include <vector>

#include "point.h"
#include "line.h"
#include "circle.h"

class Builder
{
public:
    std::vector<const Point*> basePoints;
    std::vector<const Line*> baseLines;
    std::vector<const Circle*> baseCircles;

    std::vector<const Point*> stagePoints;
    std::vector<const Point*> newStagePoints;

    Point res1, res2;

    Builder();
    bool isNewPoint(const Point &p);
    bool isNewLine(const Line &l);
    bool isNewCircle(const Circle &c);

    void addPointToBase(const Point &p);
    void addLineToBase(const Line &l);
    void addCircleToBase(const Circle &c);
    void doStep();

    void processLoop(const Point &p1, const Point &p2);
    void processLoop(const Line &l1, const Line &l2);
    void processLoop(const Circle &c1, const Circle &c2);
    bool findLoop(const Point &p, const std::vector<const Point*> &points);
    bool findLoop(const Line &l, const std::vector<const Line*> &lines);
    bool findLoop(const Circle &c, const std::vector<const Circle*> &circles);
};

#endif /* EUCL_BUILDER */
