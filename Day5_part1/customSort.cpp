#include "customSort.h"

bool customSort::operator()(const int a, const int b)
{
    auto range = ordering.equal_range(a);
    for (auto i = range.first; i != range.second; ++i)
    {
        if (i->second == b)
        {
            return true;
        }
    }
    return false;
}
