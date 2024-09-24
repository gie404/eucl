#include "iostream"
#include <algorithm>
#include <iomanip>
#include "builder.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "intersect.h"

using namespace std;

bool Builder::isContained(const Curve *p1, const Curve *p2, std::array<const Point *, 2> &binding)
{
    if (p1->type == p2->type)
    {
        std::array<const Point *, 2> nb1 = binding;
        std::array<const Point *, 2> nb2 = binding;

        return isContained(p1->par1, p2->par1, nb1) &&
                   isContained(p1->par2, p2->par2, nb1) ||
               isContained(p1->par1, p2->par2, nb2) &&
                   isContained(p1->par2, p2->par1, nb2);
    }
    else
    {
        return false;
    }
}

bool Builder::isContained(const Point *p1, const Point *p2, std::array<const Point *, 2> &binding)
{
    if (p1->par1 == nullptr && p2->par1 != nullptr)
    {
        return false;
    }
    if (p2->par1 == nullptr)
    {
        if (binding[p2->id] == nullptr)
        {
            binding[p2->id] = p1;
            return true;
        }
        if (binding[p2->id] != p1)
        {
            return false;
        }
        return true;
    }

    std::array<const Point *, 2> nb1 = binding;
    std::array<const Point *, 2> nb2 = binding;

    return isContained(p1->par1, p2->par1, nb1) &&
               isContained(p1->par2, p2->par2, nb1) ||
           isContained(p1->par1, p2->par2, nb2) &&
               isContained(p1->par2, p2->par1, nb2);
}

void Builder::stat()
{
    cout << "Bases p(" << basePoints.size() << ") l(" << baseLines.size() << ") c(" << baseCircles.size() << ")\n";
    size_t pls = 0, lls = 0, cls = 0;
    for (const auto &l: pointLoops) {
        pls += l.second.size();
    }
    for (const auto &l: lineLoops) {
        lls += l.second.size();
    }
    for (const auto &l: circleLoops) {
        cls += l.second.size();
    }
    cout << "Loops p(" << pointLoops.size() << "/" << pls <<  ")";
    cout << " l(" << lineLoops.size() << "/" << lls <<  ")";
    cout << " c(" << circleLoops.size() << "/" << cls << ")" << endl;
}

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

void Builder::processLoop(const Point &p, const Point &basePoint)
{
    for (const auto &loopBase : pointLoops)
    {
        for (const auto &loop : loopBase.second)
        {
            const Point np(p.x, p.y, loop.first, loop.second);
            array<const Point *, 2> binding = {nullptr, nullptr};
            if (isContained(&p, &np, binding))
            {
                // cout << "contained " << p << endl;
                return;
            }
        }
    }
    printSubTree(&p, 0);
    printSubTree(&basePoint, 0);
    pointLoops[basePoint.id].push_back(make_pair(p.par1, p.par2));
}

void Builder::processLoop(const Line &l, const Line &baseLine)
{
    for (const auto &loopBase : lineLoops)
    {
        for (const auto &loop : loopBase.second)
        {
            const Line nl(*loop.first, *loop.second);
            array<const Point *, 2> binding = {nullptr, nullptr};
            if (isContained(&l, &nl, binding))
            {
                // cout << "contained " << p << endl;
                return;
            }
        }
    }
    printSubTree(&l, 0);
    printSubTree(&baseLine, 0);
    lineLoops[baseLine.id].push_back(make_pair(l.par1, l.par2));
}

void Builder::processLoop(const Circle &c, const Circle &baseCircle)
{
    for (const auto &loopBase : circleLoops)
    {
        for (const auto &loop : loopBase.second)
        {
            const Circle nc(*loop.first, *loop.second);
            array<const Point *, 2> binding = {nullptr, nullptr};
            if (isContained(&c, &nc, binding))
            {
                // cout << "contained " << p << endl;
                return;
            }
        }
    }
    printSubTree(&c, 0);
    printSubTree(&baseCircle, 0);
    circleLoops[baseCircle.id].push_back(make_pair(c.par1, c.par2));
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

void Builder::printPointLoop(size_t pos)
{
    auto el = Point(*basePoints[pos]);
    cout << "loopbase " << el << ", loops " << pointLoops[pos].size() << endl;
    cout << "base path\n";
    printSubTree(basePoints[pos], 0);
    for (auto p : pointLoops[pos])
    {
        cout << "alt path\n";
        el.par1 = p.first;
        el.par2 = p.second;

        printSubTree(&el, 0);
    }
}

void Builder::printLineLoop(size_t pos)
{
    Line line = Line(*baseLines[pos]);
    cout << "loopbase " << line << ", loops " << lineLoops[pos].size() << endl;
    line.par1 = lineLoops[pos][0].first;
    line.par2 = lineLoops[pos][0].second;
    printSubTree(baseLines[pos], 0);
    printSubTree(&line, 0);
}

void Builder::printCircleLoop(size_t pos)
{
    auto el = Circle(*baseCircles[pos]);
    cout << "loopbase " << el << ", loops " << circleLoops[pos].size() << endl;
    el.par1 = circleLoops[pos][0].first;
    el.par2 = circleLoops[pos][0].second;
    printSubTree(baseCircles[pos], 0);
    printSubTree(&el, 0);
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
    p.id = basePoints.size();
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
        l->id = baseLines.size();
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
        c->id = baseCircles.size();
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
    int i = 0;
    for (const auto sp : stagePoints)
    {
        addPointToBase(*sp);
        cout << "step " << i++ << "/" << stagePoints.size() << " newbasepoints " << newStagePoints.size() << endl;
        stat();
    }
    // cout << "len " << stagePoints.size() << " " << newStagePoints.size() << endl;
    stagePoints = newStagePoints;
    newStagePoints.clear();
}
