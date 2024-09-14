#include "iostream"
#include <algorithm>
#include "builder.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "intersect.h"

using namespace std;

Builder::Builder()
{
    stagePoints.push_back(Point(0, 0, nullptr, nullptr));
    stagePoints.push_back(Point(1, 0, nullptr, nullptr));
}

void Builder::processLoop(const Point &p1, const Point &p2)
{
    cout << "Loop " << p1 << " " << p2 << endl;
}

void Builder::processLoop(const Line &l1, const Line &l2)
{
    cout << "Loop " << l1 << " " << l2 << endl;
}

void Builder::processLoop(const Circle &c1, const Circle &c2)
{
    cout << "Loop " << c1 << " " << c2 << endl;
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

void Builder::addPointToBase(const Point &p)
{
    for (const Point &bp : basePoints)
    {
        addLineToBase(Line(p, bp));
        addCircleToBase(Circle(p, bp));
        cout << "here0\n";
        for (const auto cir : baseCircles)
        {
            cout << cir << endl;
        }
        addCircleToBase(Circle(bp, p));
        cout << "here1\n";
        for (const auto cir : baseCircles)
        {
            cout << cir << endl;
        }
    }
    cout << "here2\n";
    for (const auto cir : baseCircles)
    {
        cout << cir << endl;
    }
    if (basePoints.size() == 0)
        basePoints.push_back(p);
    cout << "here3\n";
    for (const auto cir : baseCircles)
    {
        cout << cir << endl;
    }
}

void Builder::addLineToBase(const Line &l)
{
    if (isNewLine(l))
    {
        for (const Line &bline : baseLines)
        {
            const size_t count = intersect(l, bline, res1);
            if (count == 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(res1);
            }
        }
        for (const Circle &bcircle : baseCircles)
        {
            const size_t count = intersect(l, bcircle, res1, res2);
            if (count == 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(res1);
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(res2);
            }
        }
        baseLines.push_back(l);
    }
}

void Builder::addCircleToBase(const Circle &c)
{
    if (isNewCircle(c))
    {
        for (const Line &bline : baseLines)
        {
            const size_t count = intersect(bline, c, res1, res2);
            if (count == 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(res1);
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(res2);
            }
        }
        for (const Circle &bcircle : baseCircles)
        {
            const size_t count = intersect(c, bcircle, res1, res2);
            if (count == 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(res1);
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(res2);
            }
        }
        cout << "adding circle " << c << " pars " << *c.par1 << " " << *c.par2 << baseCircles.size() << endl;
        baseCircles.push_back(c);
    }
}

void Builder::doStep()
{
    for (const Point &sp : stagePoints)
    {
        addPointToBase(sp);
    }
    for (const auto cir : baseCircles)
    {
        cout << cir << endl;
    }
    stagePoints = newStagePoints;
    newStagePoints.clear();
    for (const auto cir : baseCircles)
    {
        cout << cir << endl;
    }
}
