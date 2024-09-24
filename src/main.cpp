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
    cout << "-----------step3\n";
    builder.doStep();

    builder.stat();
    return 0;
}