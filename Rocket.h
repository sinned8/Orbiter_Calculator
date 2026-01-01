#ifndef ROCKET_H
#define ROCKET_H

#include <iostream>
#include <string>

using namespace std;


class Rocket
{

private:
double dryMass;
double fuelMass;
double isp; // in seconds



public:
Rocket(double dry, double fuel, double isp)
    : dryMass(dry), fuelMass(fuel) , isp(isp) {}


};



#endif