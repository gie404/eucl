#ifndef EUCL_BUILDER
#define EUCL_BUILDER
#include <vector>
#include <unordered_map>

#include "point.h"
#include "line.h"
#include "circle.h"

class Builder
{
public:
    std::vector<const Point *> basePoints;
    std::vector<const Line *> baseLines;
    std::vector<const Circle *> baseCircles;
    std::unordered_map<size_t, std::vector<std::pair<const Curve *, const Curve *>>> pointLoops;
    std::unordered_map<size_t, std::vector<std::pair<const Point *, const Point *>>> lineLoops;
    std::unordered_map<size_t, std::vector<std::pair<const Point *, const Point *>>> circleLoops;

    std::vector<const Point *> stagePoints;
    std::vector<const Point *> newStagePoints;

    Point res1, res2;
    // std::array<Point *, 2> binding;

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
    bool findLoop(const Point &p, const std::vector<const Point *> &points);
    bool findLoop(const Line &l, const std::vector<const Line *> &lines);
    bool findLoop(const Circle &c, const std::vector<const Circle *> &circles);

    void printPointLoop(size_t pos);
    void printLineLoop(size_t pos);
    void printCircleLoop(size_t pos);

    bool isContained(const Curve *p1, const Curve *p2 ,std::array<const Point *, 2> &binding);
    bool isContained(const Point *p1, const Point *p2, std::array<const Point *, 2> &binding);
};

#endif /* EUCL_BUILDER */
