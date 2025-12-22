#ifndef ORBIT_H
#define ORBIT_H

#include <string>
#include "Body.h"
using namespace std;


class Orbit
{
private:
    const Body* centralBody;
    double altitude;

public:
    void setOrbitalRadius(double r , double a);
    
    void setOrbitalSpeed(double mu , double r);

    void setOrbitalPeriod(double r , double mu);


    void getOrbitalRadius() const;

    void getOrbitalSpeed() const;

    void getOrbitalPeriod() const;

};



#endif