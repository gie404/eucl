#ifndef EUCL_LOOPSTORAGE
#define EUCL_LOOPSTORAGE
#include <string>
#include <vector>
#include "trie.h"


class Point;
class Circle;
class Line;
class Curve;
class Element;

class LoopStorage
{
private:
    Trie* head;
    int loopCount;
    int reprCount;
    uint64_t charCount;

    const Point& pointX;
    const Point& pointY;
public:
    void makeRepr(const Point &p, std::string &repr, std::vector<const Element*> &mapping, int pos);
    void makeRepr(const Curve &c, std::string &repr, std::vector<const Element*> &mapping, int pos);

    void makeAllRepr(const Point &p, std::vector<std::string> &reprs, int pos);
    void makeAllRepr(const Curve &c, std::vector<std::string> &reprs, int pos);

    void makeAllReprParents(const Point &par1, const Point &par2, std::vector<std::string> &reprs, int pos, char child);
    void makeAllReprParents(const Curve &par1, const Curve &par2, std::vector<std::string> &reprs, int pos, char child);

    LoopStorage(const Point& pointX, const Point& pointY);
    bool isOriginalLoop(const Point &loop);
    bool isOriginalLoop(const Line &loop);
    bool isContained(const std::string &repr, std::vector<const Element*> &mapping, int pos, Trie *node, const Element *bindX, const Element *bindY);
    void insertLoop(const Point &loop);
    void insertLoop(const Line &loop);
    int size();
    int reprSize();
    uint64_t charSize();
};

#endif /* EUCL_LOOPSTORAGE */
