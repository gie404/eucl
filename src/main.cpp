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
    cout << "basepoints\n";
    for (const auto p : builder.basePoints)
    {
        cout << p << endl;
    }
    cout << "baselines\n";
    for (const auto l : builder.baseLines)
    {
        cout << l << endl;
    }
    cout << "basecircles\n";
    for (const auto cir : builder.baseCircles)
    {
        cout << cir << endl;
    }

    return 0;
}