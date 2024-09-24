#include <iostream>
#include <vector>
#include <ostream>
#include <cmath>

#include "builder.h"

using namespace std;

int main()
{
    Builder builder;
    builder.doStep();
    cout << "-----------step2\n";
    builder.doStep();
    // cout << "-----------step3\n";
    // builder.doStep();
    // cout << "basepoints\n";
    // for (const auto p : builder.basePoints)
    // {
    //     cout << *p << endl;
    // }
    // cout << "baselines\n";
    // for (const auto l : builder.baseLines)
    // {
    //     cout << *l << endl;
    // }
    // cout << "basecircles\n";
    // for (const auto cir : builder.baseCircles)
    // {
    //     cout << *cir << endl;
    // }
    cout << "Bases p(" << builder.basePoints.size() << ") l(" << builder.baseLines.size() << ") c(" << builder.baseCircles.size() << ")\n";
    cout << "Loops p(" << builder.pointLoops.size() << ") l(" << builder.lineLoops.size() << ") c(" << builder.circleLoops.size() << ")\n";
    // builder.printPointLoop(0);
    // builder.printPointLoop(1);
    // for (const auto p: builder.pointLoops) {
        // cout << *p << endl;
    // }
    // cout << *((Circle*)(builder.stagePoints[4]->par1)) << " " << *((Circle*)(builder.stagePoints[4]->par2)) << endl;

    return 0;
}