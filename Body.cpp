#include "Body.h"
#include <iostream>
#include <string>

using namespace std;

string Body :: getName() const
{
 return name;
}

double Body :: getMU() const
{
    return mu;
}

double Body :: getRadius() const
{
    return radius;
}


