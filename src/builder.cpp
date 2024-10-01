#include "iostream"
#include <algorithm>
#include <iomanip>
#include "builder.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "intersect.h"

using namespace std;

bool Builder::isContained(const Curve *p1, const Curve *p2, vector<array<const Point *, 2>> &bindings)
{
    // cout << "cont curve " << p1->type << " " << p2->type << " " << binding[0] << " " << binding[1] << endl;
    if (p1->type == p2->type)
    {
        vector<array<const Point *, 2>> nb1 = bindings;
        vector<array<const Point *, 2>> nb2 = bindings;

        if (isContained(p1->par1, p2->par1, nb1) && isContained(p1->par2, p2->par2, nb2))
        {
            for (const auto &b1 : nb1)
            {
                for (const auto &b2 : nb2)
                {
                    if (b1[0] != nullptr && b2[0] != nullptr && b1[0] != b2[0] ||
                        b1[1] != nullptr && b2[1] != nullptr && b1[1] != b2[1])
                    {
                        continue;
                    }
                    array<const Point *, 2> b;
                    b[0] = b1[0] != nullptr ? b1[0] : b2[0];
                    b[1] = b1[1] != nullptr ? b1[1] : b2[1];
                    if (find(bindings.begin(), bindings.end(), b) == bindings.end())
                    {
                        bindings.push_back(b);
                    };
                }
            }
        }

        nb1.clear();
        nb2.clear();

        if (p1->type == 0 && isContained(p1->par1, p2->par2, nb1) && isContained(p1->par2, p2->par1, nb2))
        {
            for (const auto &b1 : nb1)
            {
                for (const auto &b2 : nb2)
                {
                    // cout << "----------- " << b1[0] << " " << b1[1] << " " << b2[0] << " " << b2[1] << endl;
                    if (b1[0] != nullptr && b2[0] != nullptr && b1[0] != b2[0] ||
                        b1[1] != nullptr && b2[1] != nullptr && b1[1] != b2[1])
                    {
                        continue;
                    }
                    array<const Point *, 2> b;
                    b[0] = b1[0] != nullptr ? b1[0] : b2[0];
                    b[1] = b1[1] != nullptr ? b1[1] : b2[1];
                    if (find(bindings.begin(), bindings.end(), b) == bindings.end())
                    {
                        bindings.push_back(b);
                    };
                }
            }
        };
    }
    // if (p1->type == 0)
    // {
    //     cout << *(Line *)p1;
    // }
    // else
    // {
    //     cout << *(Circle *)p1;
    // }
    // cout << " vs ";
    // if (p2->type == 0)
    // {
    //     cout << *(Line *)p2;
    // }
    // else
    // {
    //     cout << *(Circle *)p2;
    // }
    // cout << endl;
    // for (auto &b : bindings)
    // {
    //     cout << "binding ";
    //     if (b[0])
    //     {
    //         cout << *b[0];
    //     }
    //     else
    //     {
    //         cout << "null";
    //     }
    //     cout << " ";
    //     if (b[1])
    //     {
    //         cout << *b[1];
    //     }
    //     else
    //     {
    //         cout << "null";
    //     }
    //     cout << endl;
    // }
    return bindings.size() > 0;
}

bool Builder::isContained(const Point *p1, const Point *p2, vector<array<const Point *, 2>> &bindings)
{
    // cout << "checking point " << *p1 << " " << *p2  << endl;
    if (p1->par1 == nullptr && p2->par1 != nullptr)
    {
        return false;
    }
    if (p2 == &pointR0)
    {
        bindings.push_back({p1, nullptr});
        return true;
    }
    if (p2 == &pointR1)
    {
        bindings.push_back({nullptr, p1});
        return true;
    }

    vector<array<const Point *, 2>> nb1 = bindings;
    vector<array<const Point *, 2>> nb2 = bindings;

    if (isContained(p1->par1, p2->par1, nb1) && isContained(p1->par2, p2->par2, nb2))
    {
        for (const auto &b1 : nb1)
        {
            for (const auto &b2 : nb2)
            {
                if (b1[0] != nullptr && b2[0] != nullptr && b1[0] != b2[0] ||
                    b1[1] != nullptr && b2[1] != nullptr && b1[1] != b2[1])
                {
                    continue;
                }
                array<const Point *, 2> b;
                b[0] = b1[0] != nullptr ? b1[0] : b2[0];
                b[1] = b1[1] != nullptr ? b1[1] : b2[1];
                if (find(bindings.begin(), bindings.end(), b) == bindings.end())
                {
                    bindings.push_back(b);
                };
            }
        }
    }

    nb1.clear();
    nb2.clear();

    if (isContained(p1->par1, p2->par2, nb1) && isContained(p1->par2, p2->par1, nb2))
    {
        for (const auto &b1 : nb1)
        {
            for (const auto &b2 : nb2)
            {
                if (b1[0] != nullptr && b2[0] != nullptr && b1[0] != b2[0] ||
                    b1[1] != nullptr && b2[1] != nullptr && b1[1] != b2[1])
                {
                    continue;
                }
                array<const Point *, 2> b;
                b[0] = b1[0] != nullptr ? b1[0] : b2[0];
                b[1] = b1[1] != nullptr ? b1[1] : b2[1];
                if (find(bindings.begin(), bindings.end(), b) == bindings.end())
                {
                    bindings.push_back(b);
                };
            }
        }
    }
    // cout << *p1 << " vs " << *p2 << endl;
    // for (auto &b : bindings)
    // {
    //     cout << "binding ";
    //     if (b[0])
    //     {
    //         cout << *b[0];
    //     }
    //     else
    //     {
    //         cout << "null";
    //     }
    //     cout << " ";
    //     if (b[1])
    //     {
    //         cout << *b[1];
    //     }
    //     else
    //     {
    //         cout << "null";
    //     }
    //     cout << endl;
    // }
    return bindings.size() > 0;
}

void Builder::stat()
{
    cout << "Bases p(" << basePoints.size() << ") l(" << baseLines.size() << ") c(" << baseCircles.size() << ")\n";
    size_t pls = 0, lls = 0, cls = 0;
    cout << "Loops p(" << pointLoops.size() << "/" << pls << ")";
    cout << " l(" << lineLoops.size() << "/" << lls << ")";
    cout << " c(" << circleLoops.size() << "/" << cls << ")" << endl;
}

void printSubTree(const Curve *node, int indent);

void printSubTree(const Point *node, int indent)
{
    if (node != nullptr)
    {
        if (node->par1 == nullptr) {
            cout << string(indent, ' ') << "r(" << node->x << ", " << node->y << ")" << endl;
            return;
        }
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
    stagePoints.push_back(&pointR0);
    stagePoints.push_back(&pointR1);
}

void Builder::insertToRepr(const Point &point, string &repr, int pos)
{
    // cout << "ins point " << point << " " << pos << " " << repr << " " << repr.size() << endl;
    if (repr.size() <= pos)
    {
        repr.resize(pos + 1, 'N');
    }
    if (&point == &pointR0)
    {
        repr[pos] = 'X';
        return;
    }
    if (&point == &pointR1)
    {
        repr[pos] = 'Y';
        return;
    }
    repr[pos] = 'P';
    string par1repr;
    string par2repr;
    insertToRepr(*point.par1, par1repr, 0);
    insertToRepr(*point.par2, par2repr, 0);
    // cout << par1repr << " --- " << par2repr << ", " << par1repr.compare(par2repr) << endl;
    if (par1repr.compare(par2repr) < 0)
    {
        insertToRepr(*point.par1, repr, 2 * pos + 1);
        insertToRepr(*point.par2, repr, 2 * pos + 2);
    }
    else
    {
        insertToRepr(*point.par2, repr, 2 * pos + 1);
        insertToRepr(*point.par1, repr, 2 * pos + 2);
    }
}

void Builder::insertToRepr(const Curve &curve, string &repr, int pos)
{
    // cout << "ins curve " << curve.type << " " << pos << " " << repr << " " << repr.size() << endl;
    if (repr.size() <= pos)
    {
        repr.resize(pos + 1, 'N');
    }
    if (curve.type == 0)
    {
        repr[pos] = 'L';

        string par1repr;
        string par2repr;
        insertToRepr(*curve.par1, par1repr, 0);
        insertToRepr(*curve.par2, par2repr, 0);
        // cout << par1repr << " --- " << par2repr << ", " << par1repr.compare(par2repr) << endl;
        if (par1repr.compare(par2repr) < 0)
        {
            insertToRepr(*curve.par1, repr, 2 * pos + 1);
            insertToRepr(*curve.par2, repr, 2 * pos + 2);
        }
        else
        {
            insertToRepr(*curve.par2, repr, 2 * pos + 1);
            insertToRepr(*curve.par1, repr, 2 * pos + 2);
        }
    }
    else
    {
        repr[pos] = 'C';
        insertToRepr(*curve.par1, repr, 2 * pos + 1);
        insertToRepr(*curve.par2, repr, 2 * pos + 2);
    }
}

void Builder::processLoop(const Point &point, const Point &basePoint)
{
    const Point *p = new Point(point);
    Line l1(1, 0, 0);
    l1.par1 = p;
    l1.par2 = &basePoint;
    Line l2(*p, basePoint);
    for (const auto &loop : pointLoops)
    {
        l2.par1 = loop.first;
        l2.par2 = loop.second;
        vector<array<const Point *, 2>> bindings;
        if (isContained(&l1, &l2, bindings))
        {
            // cout << "contained " << *p << endl;
            // printSubTree(p, 0);
            // printSubTree(&basePoint, 0);
            // cout << "in-----------" << endl;
            // printSubTree(l2.par1, 0);
            // printSubTree(l2.par2, 0);

            delete (p);
            return;
        }
    }
    cout << "loop found " << endl;
    printSubTree(p, 0);
    printSubTree(&basePoint, 0);
    pointLoops.push_back(make_pair(p, &basePoint));
    // string repr;
    // insertToRepr(l1, repr, 0);
    // bool needReplace = false;
    // for (auto &ch: repr){
    //     if(ch == 'X'){
    //         break;
    //     }
    //     if (ch == 'Y') {
    //         needReplace = true;
    //         break;
    //     }
    // }
    // if (needReplace) {
    //     replace(repr.begin(), repr.end(), 'Y', 'Q');
    //     replace(repr.begin(), repr.end(), 'X', 'Y');
    //     replace(repr.begin(), repr.end(), 'Q', 'X');
    // }
    // pointLoopRepr.push_back(repr);
    // cout << repr << endl;
}

void Builder::processLoop(const Line &line, const Line &baseLine)
{
    const Line *l = new Line(line);
    const Point p1(0, 0, l, &baseLine);
    Point p2(0, 0, l, &baseLine);

    for (const auto &loop : lineLoops)
    {
        p2.par1 = loop.first;
        p2.par2 = loop.second;
        vector<array<const Point *, 2>> bindings;
        if (isContained(&p1, &p2, bindings))
        {
            // cout << "contained " << *l << endl;
            // printSubTree(l, 0);
            // printSubTree(&baseLine, 0);
            // cout << "in-----------" << endl;
            // printSubTree(p2.par1, 0);
            // printSubTree(p2.par2, 0);

            delete (l);
            return;
        }
    }
    cout << "loop found" << endl;
    printSubTree(l, 0);
    printSubTree(&baseLine, 0);
    lineLoops.push_back(make_pair(l, &baseLine));
}

void Builder::processLoop(const Circle &circle, const Circle &baseCircle)
{
    const Circle *c = new Circle(circle);
    const Point p1(0, 0, c, &baseCircle);
    Point p2(0, 0, c, &baseCircle);

    for (const auto &loop : circleLoops)
    {
        p2.par1 = loop.first;
        p2.par2 = loop.second;
        vector<array<const Point *, 2>> bindings;
        if (isContained(&p1, &p2, bindings))
        {
            // cout << "contained " << *c << endl;
            // printSubTree(c, 0);
            // printSubTree(&baseCircle, 0);
            // cout << "in-----------" << endl;
            // printSubTree(p2.par1, 0);
            // printSubTree(p2.par2, 0);

            delete (c);
            return;
        }
    }
    cout << "loop found" << endl;
    printSubTree(c, 0);
    printSubTree(&baseCircle, 0);
    circleLoops.push_back(make_pair(c, &baseCircle));
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

bool Builder::findLoop(const Point &el, const tree &elps)
{
    std::vector<treeValue> returned_values;
    elps.query(bgi::nearest(bPoint(el.x, el.y), 1), std::back_inserter(returned_values));

    if (returned_values.size() > 0 && *returned_values[0].second == el)
    {
        processLoop(el, *returned_values[0].second);
        return false;
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
    cout << "loopbase " << *pointLoops[pos].second << endl;
    cout << "base path\n";
    printSubTree(pointLoops[pos].second, 0);
    cout << "alt path\n";
    printSubTree(pointLoops[pos].first, 0);
}

void Builder::printLineLoop(size_t pos)
{
    cout << "loopbase " << *lineLoops[pos].second << endl;
    cout << "base path\n";
    printSubTree(lineLoops[pos].second, 0);
    cout << "alt path\n";
    printSubTree(lineLoops[pos].first, 0);
}

void Builder::printCircleLoop(size_t pos)
{
    cout << "loopbase " << *circleLoops[pos].second << endl;
    cout << "base path\n";
    printSubTree(circleLoops[pos].second, 0);
    cout << "alt path\n";
    printSubTree(circleLoops[pos].first, 0);
}

bool Builder::isNewPoint(const Point &p)
{
    // if(findLoop(p, newStagePoints) != findLoop(p, newStagePointsIndex)) throw("error!!!-------------------------------\n");
    return findLoop(p, basePoints) &&
           findLoop(p, stagePoints) &&
           //    findLoop(p, newStagePoints);
           findLoop(p, newStagePointsIndex);
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
                const Point *newStagePoint = new Point(res1);
                newStagePoints.push_back(newStagePoint);
                newStagePointsIndex.insert(std::make_pair(bPoint(newStagePoint->x, newStagePoint->y), newStagePoint));
            }
        }
        for (const auto bc : baseCircles)
        {
            const size_t count = intersect(*l, *bc, res1, res2);
            if (count >= 1 && isNewPoint(res1))
            {
                const Point *newStagePoint = new Point(res1);
                newStagePoints.push_back(newStagePoint);
                newStagePointsIndex.insert(std::make_pair(bPoint(newStagePoint->x, newStagePoint->y), newStagePoint));
            }
            if (count == 2 && isNewPoint(res2))
            {
                const Point *newStagePoint = new Point(res2);
                newStagePoints.push_back(newStagePoint);
                newStagePointsIndex.insert(std::make_pair(bPoint(newStagePoint->x, newStagePoint->y), newStagePoint));
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
                const Point *newStagePoint = new Point(res1);
                newStagePoints.push_back(newStagePoint);
                newStagePointsIndex.insert(std::make_pair(bPoint(newStagePoint->x, newStagePoint->y), newStagePoint));
            }
            if (count == 2 && isNewPoint(res2))
            {
                const Point *newStagePoint = new Point(res2);
                newStagePoints.push_back(newStagePoint);
                newStagePointsIndex.insert(std::make_pair(bPoint(newStagePoint->x, newStagePoint->y), newStagePoint));
            }
        }
        for (const auto bc : baseCircles)
        {
            const size_t count = intersect(*c, *bc, res1, res2);
            if (count >= 1 && isNewPoint(res1))
            {
                const Point *newStagePoint = new Point(res1);
                newStagePoints.push_back(newStagePoint);
                newStagePointsIndex.insert(std::make_pair(bPoint(newStagePoint->x, newStagePoint->y), newStagePoint));
            }
            if (count == 2 && isNewPoint(res2))
            {
                const Point *newStagePoint = new Point(res2);
                newStagePoints.push_back(newStagePoint);
                newStagePointsIndex.insert(std::make_pair(bPoint(newStagePoint->x, newStagePoint->y), newStagePoint));
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
    newStagePointsIndex.clear();
}
