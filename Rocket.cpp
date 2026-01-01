#include "Rocket.h"
#include <iostream>
#include <cmath>

using namespace std;

double Rocket :: getDeltaV() const
{
    double m0 = dryMass + fuelMass;
    double rocketDeltaV = isp * 9.80665 * log(m0 / dryMass);
    return rocketDeltaV;
}

string Rocket :: getName() const
{
    return name;
}


double Rocket :: getDryMass() const
{
    return dryMass;
}
double Rocket :: getFuelMass() const
{
    return fuelMass;
}
double Rocket :: getISP() const
{
    return isp;
}