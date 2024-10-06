#include "loopStorage.h"
#include "point.h"
#include "line.h"
#include "circle.h"

using namespace std;

void LoopStorage::makeRepr(const Point &p, std::string &repr, vector<const Element *> &mapping, int pos)
{
    if (repr.size() <= pos)
    {
        repr.resize(pos + 1, 'N');
        mapping.resize(pos + 1);
    }
    mapping[pos] = &p;
    if (&p == &pointX)
    {
        repr[pos] = 'X';
        return;
    }
    if (&p == &pointY)
    {
        repr[pos] = 'Y';
        return;
    }
    repr[pos] = 'P';

    makeRepr(*p.par1, repr, mapping, 2 * pos + 1);
    makeRepr(*p.par2, repr, mapping, 2 * pos + 2);
}

void LoopStorage::makeRepr(const Curve &curve, std::string &repr, vector<const Element *> &mapping, int pos)
{
    if (repr.size() <= pos)
    {
        repr.resize(pos + 1, 'N');
        mapping.resize(pos + 1);
    }
    if (curve.type == 0)
    {
        repr[pos] = 'L';
    }
    else
    {
        repr[pos] = 'C';
    }
    mapping[pos] = &curve;
    makeRepr(*curve.par1, repr, mapping, 2 * pos + 1);
    makeRepr(*curve.par2, repr, mapping, 2 * pos + 2);
}

void LoopStorage::makeAllReprParents(const Point &par1, const Point &par2, std::vector<std::string> &reprs, int pos, char child)
{
    vector<string> par1reprs;
    vector<string> par2reprs;
    makeAllRepr(par1, par1reprs, 2 * pos + 1);
    makeAllRepr(par2, par2reprs, 2 * pos + 2);

    for (const auto &r1 : par1reprs)
    {
        for (const auto &r2 : par2reprs)
        {
            if (r1.size() >= r2.size())
            {
                reprs.emplace_back(r1);
                string &res = reprs.back();
                res[pos] = child;
                for (int i = 2 * pos + 2; i < r2.size(); ++i)
                {
                    if (r2[i] != 'N')
                    {
                        res[i] = r2[i];
                    }
                }
            }
            else
            {
                reprs.emplace_back(r2);
                string &res = reprs.back();
                res[pos] = child;
                for (int i = 2 * pos + 1; i < r1.size(); ++i)
                {
                    if (r1[i] != 'N')
                    {
                        res[i] = r1[i];
                    }
                }
            }
        }
    }
}

void LoopStorage::makeAllReprParents(const Curve &par1, const Curve &par2, std::vector<std::string> &reprs, int pos, char child)
{
    vector<string> par1reprs;
    vector<string> par2reprs;
    makeAllRepr(par1, par1reprs, 2 * pos + 1);
    makeAllRepr(par2, par2reprs, 2 * pos + 2);

    for (const auto &r1 : par1reprs)
    {
        for (const auto &r2 : par2reprs)
        {
            if (r1.size() >= r2.size())
            {
                reprs.emplace_back(r1);
                string &res = reprs.back();
                res[pos] = child;
                for (int i = 2 * pos + 2; i < r2.size(); ++i)
                {
                    if (r2[i] != 'N')
                    {
                        res[i] = r2[i];
                    }
                }
            }
            else
            {
                reprs.emplace_back(r2);
                string &res = reprs.back();
                res[pos] = child;
                for (int i = 2 * pos + 1; i < r1.size(); ++i)
                {
                    if (r1[i] != 'N')
                    {
                        res[i] = r1[i];
                    }
                }
            }
        }
    }
}

void LoopStorage::makeAllRepr(const Point &p, std::vector<std::string> &reprs, int pos)
{
    if (&p == &pointX)
    {
        reprs.emplace_back(pos + 1, 'N');
        reprs.back()[pos] = 'X';
        return;
    }
    if (&p == &pointY)
    {
        reprs.emplace_back(pos + 1, 'N');
        reprs.back()[pos] = 'Y';
        return;
    }

    makeAllReprParents(*p.par1, *p.par2, reprs, pos, 'P');
    makeAllReprParents(*p.par2, *p.par1, reprs, pos, 'P');
}

void LoopStorage::makeAllRepr(const Curve &c, std::vector<std::string> &reprs, int pos)
{
    if (c.type == 0)
    {
        makeAllReprParents(*c.par1, *c.par2, reprs, pos, 'L');
        makeAllReprParents(*c.par2, *c.par1, reprs, pos, 'L');
    }
    else
    {
        makeAllReprParents(*c.par1, *c.par2, reprs, pos, 'C');
    }
}

LoopStorage::LoopStorage(const Point &pointX, const Point &pointY) : pointX(pointX), pointY(pointY)
{
    head = new Trie();
    cout << "size " << sizeof(*head) << endl;
    loopCount = 0;
    reprCount = 0;
    charCount = 0;
}

bool LoopStorage::isOriginalLoop(const Point &loop)
{
    string repr;
    vector<const Element *> mapping;
    makeRepr(loop, repr, mapping, 0);
    return isContained(repr, mapping, 0, head, nullptr, nullptr);
}

bool LoopStorage::isOriginalLoop(const Line &loop)
{
    string repr;
    vector<const Element *> mapping;
    makeRepr(loop, repr, mapping, 0);
    // cout << "repr " << repr << endl;
    // cout << "count " << loopCount << " " << reprCount << endl;
    return isContained(repr, mapping, 0, head, nullptr, nullptr);
}

bool LoopStorage::isContained(const std::string &repr, vector<const Element *> &mapping, int pos, Trie *node, const Element *bindX, const Element *bindY)
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->isLeaf)
    {
        return true;
    }
    if (repr.size() <= pos)
    {
        return false;
    }

    // cout << "pos " << pos << " " << repr[pos] << " " << bindX << " " << bindY << endl;
    return isContained(repr, mapping, pos + 1, node->character[node->keyToPos(repr[pos])], bindX, bindY) ||
           (bindX == nullptr || bindX == mapping[pos]) &&
               isContained(repr, mapping, pos + 1, node->character[node->keyToPos('X')], mapping[pos], bindY) ||
           (bindY == nullptr || bindY == mapping[pos]) &&
               isContained(repr, mapping, pos + 1, node->character[node->keyToPos('Y')], bindX, mapping[pos]);
}

void LoopStorage::insertLoop(const Point &loop)
{
    vector<string> reprs;
    makeAllRepr(loop, reprs, 0);
    for (auto &repr : reprs)
    {
        head->insert(repr);
        charCount += repr.size();
    }
    loopCount += 1;
    reprCount += reprs.size();
}

void LoopStorage::insertLoop(const Line &loop)
{
    vector<string> reprs;
    makeAllRepr(loop, reprs, 0);
    for (auto &repr : reprs)
    {
        head->insert(repr);
        charCount += repr.size();
    }
    loopCount += 1;
    reprCount += reprs.size();
}

int LoopStorage::size()
{
    return loopCount;
}

int LoopStorage::reprSize()
{
    return reprCount;
}
uint64_t LoopStorage::charSize()
{
    return charCount;
}
