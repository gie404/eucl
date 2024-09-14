#ifndef EUCL_BUILDER
#define EUCL_BUILDER
#include <vector>

#include "point.h"
#include "line.h"
#include "circle.h"

class Builder
{
public:
    std::vector<Point> basePoints;
    std::vector<Line> baseLines;
    std::vector<Circle> baseCircles;

    std::vector<Point> stagePoints;
    std::vector<Line> stageLines;
    std::vector<Circle> stageCircles;
    std::vector<Point> newStagePoints;

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
    bool findLoop(const Point &p, const std::vector<Point> &points);
    bool findLoop(const Line &l, const std::vector<Line> &lines);
    bool findLoop(const Circle &c, const std::vector<Circle> &circles);
};

#endif /* EUCL_BUILDER */
