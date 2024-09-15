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
    stagePoints.push_back(new Point(0, 0, nullptr, nullptr));
    stagePoints.push_back(new Point(1, 0, nullptr, nullptr));
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

    printSubTree(&l1, 0);
    printSubTree(&l2, 0);
}

void Builder::processLoop(const Circle &c1, const Circle &c2)
{
    cout << "Loop " << c1 << " " << c2 << endl;
    printSubTree(&c1, 0);
    printSubTree(&c2, 0);
}

bool Builder::findLoop(const Point &el, const std::vector<const Point *> &elps)
{
    for (const auto elp : elps)
    {
        if (el == *elp)
        {
            processLoop(el, *elp);
            return false;
        }
    }
    return true;
}

bool Builder::findLoop(const Line &el, const std::vector<const Line *> &elps)
{
    for (const auto elp : elps)
    {
        if (el == *elp)
        {
            processLoop(el, *elp);
            return false;
        }
    }
    return true;
}

bool Builder::findLoop(const Circle &el, const std::vector<const Circle *> &elps)
{
    for (const auto elp : elps)
    {
        if (el == *elp)
        {
            processLoop(el, *elp);
            return false;
        }
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
    return findLoop(l, baseLines);
}

bool Builder::isNewCircle(const Circle &c)
{
    return findLoop(c, baseCircles);
}

void Builder::addPointToBase(const Point &p)
{
    for (const auto bp : basePoints)
    {
        addLineToBase(Line(p, *bp));
        addCircleToBase(Circle(p, *bp));
        addCircleToBase(Circle(*bp, p));
    }
    basePoints.push_back(&p);
}

void Builder::addLineToBase(const Line &line)
{
    if (isNewLine(line))
    {
        const Line *l = new Line(line);
        for (const auto bl : baseLines)
        {
            const size_t count = intersect(*l, *bl, res1);
            if (count == 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(new Point(res1));
            }
        }
        for (const auto bc : baseCircles)
        {
            const size_t count = intersect(*l, *bc, res1, res2);
            if (count >= 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(new Point(res1));
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(new Point(res2));
            }
        }
        baseLines.push_back(l);
    }
}

void Builder::addCircleToBase(const Circle &circle)
{
    if (isNewCircle(circle))
    {
        const Circle *c = new Circle(circle);
        for (const auto bl : baseLines)
        {
            const size_t count = intersect(*bl, *c, res1, res2);
            if (count >= 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(new Point(res1));
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(new Point(res2));
            }
        }
        for (const auto bc : baseCircles)
        {
            const size_t count = intersect(*c, *bc, res1, res2);
            if (count >= 1 && isNewPoint(res1))
            {
                newStagePoints.push_back(new Point(res1));
            }
            if (count == 2 && isNewPoint(res2))
            {
                newStagePoints.push_back(new Point(res2));
            }
        }
        baseCircles.push_back(c);
    }
}

void Builder::doStep()
{
    for (const auto sp : stagePoints)
    {
        addPointToBase(*sp);
    }
    cout << "len " << stagePoints.size() << " " << newStagePoints.size() << endl;
    stagePoints = newStagePoints;
    newStagePoints.clear();
}
