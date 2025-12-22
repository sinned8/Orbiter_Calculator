#ifndef BODY_H
#define BODY_H

#include <cstring>
#include <string>

using namespace std;

class Body
{
private:
    char *name;
    double mu; // mu denotes the standard gravitational parameter: mass * universal grav. constant 
    double radius;

public:


    //default and primary contructors
    Body()
    {
        name = new char[1];
        mu = 0.0;
        radius = 0.0;

    }

    Body(const char *n, double mu, double r)
    {
        name = new char[strlen(n) + 1];
        strcpy(name , n);
        mu = mu;
        radius = r;
    }

    ~Body()
    {
        delete [] name;
    }
};


#endif