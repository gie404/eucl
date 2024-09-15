#include "iostream"
#include <algorithm>
#include <iomanip>
#include "builder.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "intersect.h"

using namespace std;

void printSubTree(const Curve *node, int indent);

void printSubTree(const Point *node, int indent)
{
    if (node != nullptr)
    {
        cout << string(indent, ' ') << *node << endl;
        printSubTree(node->par1, indent + 4);
        printSubTree(node->par2, indent + 4);
    }
}
void printSubTree(const Curve *node, int indent)
{
    if (node != nullptr)
    {
        cout << string(indent, ' ');
        if (node->type == 0)
        {
            cout << *static_cast<const Line *>(node);
        }
        if (node->type == 1)
        {
            cout << *static_cast<const Circle *>(node);
        }
        cout << endl;
        printSubTree(node->par1, indent + 4);
        printSubTree(node->par2, indent + 4);
    }
}

Builder::Builder()
{
    stagePoints.push_back(Point(0, 0, nullptr, nullptr));
    stagePoints.push_back(Point(1, 0, nullptr, nullptr));
}

void Builder::processLoop(const Point &p1, const Point &p2)
{
    cout << "Loop " << p1 << " " << p2 << endl;
    printSubTree(&p1, 0);
    printSubTree(&p2, 0);
}

void Builder::processLoop(const Line &l1, const Line &l2)
{
    cout << "Loop " << l1 << " " << l2 << endl;
    cout << "basep\n";
    for(auto &p: basePoints){
        cout << p << endl;
    }
    cout << "basel\n";
    for(auto &p: baseLines){
        cout << p << " " << *p.par1 << " " << *p.par2 << endl;
    }
    printSubTree(&l1, 0);
    printSubTree(&l2, 0);
}

void Builder::processLoop(const Circle &c1, const Circle &c2)
{
    cout << "Loop " << c1 << " " << c2 << endl;
    printSubTree(&c1, 0);
    printSubTree(&c2, 0);
}

bool Builder::findLoop(const Point &p, const std::vector<Point> &points)
{
    const auto match = find(points.begin(), points.end(), p);
    if (match != points.end())
    {
        processLoop(p, *match);
        return false;
    }
    return true;
}

bool Builder::findLoop(const Line &l, const std::vector<Line> &lines)
{
    const auto match = find(lines.begin(), lines.end(), l);
    if (match != lines.end())
    {
        processLoop(l, *match);
        return false;
    }
    return true;
}

bool Builder::findLoop(const Circle &c, const std::vector<Circle> &circles)
{
    const auto match = find(circles.begin(), circles.end(), c);
    if (match != circles.end())
    {
        processLoop(c, *match);
        return false;
    }
    return true;
}

bool Builder::isNewPoint(const Point &p)
{
    return findLoop(p, basePoints) &&
           findLoop(p, stagePoints) &&
           findLoop(p, newStagePoints);
}

bool Builder::isNewLine(const Line &l)
{
    return findLoop(l, baseLines) &&
           findLoop(l, stageLines);
}

bool Builder::isNewCircle(const Circle &c)
{
    return findLoop(c, baseCircles) &&
           findLoop(c, stageCircles);
}

void Builder::addPointToBase(const Point &point)
{
    basePoints.push_back(point);
    const Point &p = basePoints.back();

    for (size_t i = 0; i < basePoints.size() - 1; ++i)
    {
        const Point &bp = basePoints[i];
        addLineToBase(Line(p, bp));
        addCircleToBase(Circle(p, bp));
        addCircleToBase(Circle(bp, p));
    }
}

void Builder::addLineToBase(const Line &line)
{
    if (isNewLine(line))
    {
        baseLines.push_back(line);
        const Line &l = baseLines.back();

        for (size_t i = 0; i < baseLines.size() - 1; ++i)
        {
            const size_t count = intersect(l, baseLines[i], res1);
            if (count == 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(res1);
            }
        }
        for (const Circle &bcircle : baseCircles)
        {
            const size_t count = intersect(l, bcircle, res1, res2);
            if (count >= 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(res1);
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(res2);
            }
        }
    }
}

void Builder::addCircleToBase(const Circle &circle)
{
    if (isNewCircle(circle))
    {
        baseCircles.push_back(circle);
        const Circle &c = baseCircles.back();
        // cout << "circle " << c << " basel " << baseLines.size() << " basec " << baseCircles.size() << endl;

        for (const Line &bline : baseLines)
        {
            const size_t count = intersect(bline, c, res1, res2);
            // cout << "inter " << bline << " " << c << " count " << count << endl;
            if (count >= 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(res1);
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(res2);
            }
        }
        for (size_t i = 0; i < baseCircles.size() - 1; ++i)
        {
            const size_t count = intersect(c, baseCircles[i], res1, res2);
            // cout << "inter " << c << " " << baseCircles[i] << " count " << count << endl;
            if (count >= 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(res1);
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(res2);
            }
        }
    }
}

void Builder::doStep()
{
    for (const Point &sp : stagePoints)
    {
        addPointToBase(sp);
    }
    stagePoints = newStagePoints;
    newStagePoints.clear();
}
