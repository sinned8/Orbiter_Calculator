#ifndef ROCKET_H
#define ROCKET_H

#include <iostream>
#include <string>

using namespace std;


class Rocket
{

private:
string name;
double dryMass;
double fuelMass;
double isp; // in seconds



public:

Rocket()
    : name(),dryMass(), fuelMass() , isp() {}

Rocket(const string &name,double dry, double fuel, double isp)
    : name (name), dryMass(dry), fuelMass(fuel) , isp(isp) {}

double getDeltaV() const;
string getName() const;
double getDryMass() const;
double getFuelMass() const;
double getISP() const;

};



#endif