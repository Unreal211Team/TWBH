#include "Factory.h"

using namespace std;
int Factory::makeRandomInt(int start, int end)
{
    random_device rd;
    uniform_int_distribution<int> random(start, end);
    return random(rd);
}
