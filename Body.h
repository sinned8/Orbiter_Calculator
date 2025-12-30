#ifndef BODY_H
#define BODY_H

#include <cstring>
#include <string>

using namespace std;

class Body
{
private:
    string name;
    double mu; // mu denotes the standard gravitational parameter: mass * universal grav. constant m^3/s^-2
    double radius; // in km

public:


    string getName() const;

    double getMU() const;

    double getRadius() const;


    //default and primary contructors
    Body()
        : name() , mu() , radius() {}

    Body(const string &name, double mu, double r)
        : name(name), mu(mu), radius(r) {}

    
};


#endif