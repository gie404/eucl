#ifndef EUCL_BUILDER
#define EUCL_BUILDER
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "point.h"
#include "line.h"
#include "circle.h"
#include "loopStorage.h"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 2, bg::cs::cartesian> bPoint;
typedef std::pair<bPoint, const Point*> treeValue;
typedef bgi::rtree< treeValue, bgi::rstar<16> > tree;

class Builder
{
public:
    std::vector<const Point *> basePoints;
    std::vector<const Line *> baseLines;
    std::vector<const Circle *> baseCircles;

    LoopStorage loops;
    std::vector<std::pair<const Point *, const Point *>> pointLoops;
    std::vector<std::pair<const Line *, const Line *>> lineLoops;
    std::vector<std::pair<const Circle *, const Circle *>> circleLoops;
    std::vector<std::string> pointLoopRepr;

    std::vector<const Point *> stagePoints;
    std::vector<const Point *> newStagePoints;
    tree newStagePointsIndex;

    Point res1, res2;
    const Point pointR0 = Point(0, 0, nullptr, nullptr);
    const Point pointR1 = Point(1, 0, nullptr, nullptr);

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
    bool findLoop(const Point &p, const tree &points);
    bool findLoop(const Line &l, const std::vector<const Line *> &lines);
    bool findLoop(const Circle &c, const std::vector<const Circle *> &circles);

    void printPointLoop(size_t pos);
    void printLineLoop(size_t pos);
    void printCircleLoop(size_t pos);

    bool isContained(const Curve *p1, const Curve *p2, std::vector<std::array<const Point *, 2>> &bindings);
    bool isContained(const Point *p1, const Point *p2, std::vector<std::array<const Point *, 2>> &bindings);

    void insertToRepr(const Point &point, std::string &repr, int pos);
    void insertToRepr(const Curve &curve, std::string &repr, int pos);

    void stat();
};

#endif /* EUCL_BUILDER */
