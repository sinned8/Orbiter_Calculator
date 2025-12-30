#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>



#include "Body.h"
#include "Orbit.h"

const double PI = 3.14159265358979323846;

using namespace std;

void addAPlanet( vector <Body> &PlanetBodies);

void listAllPlanets(const vector<Body> &PlanetBodies);

void circularOrbitInfo(const vector<Body> &PlanetBodies);

int main()
{
    
    int choice;
    cout << "=== ORBITAL PLANNER PROJECT ===\n";
    
    
    vector <Body> PlanetBodies = { Body("Sun",   1.327e20, 695700),
                                Body("Earth", 3.986e14, 6371),
                                Body("Moon",  4.903e12, 1737.4)};

    
            
    do
    {
        cout <<"\nPlease select one of the following options: "
        <<"\n1) List Bodies."
        <<"\n2) Add a new planet / body."
        <<"\n3) Compute the circular orbit and display info."
        <<"\n4) Plan a Hohmann transfer."
        <<"\n5) Rocket delta-v calculator."
        <<"\n6) Check if rocket can do trasnfer."
        <<"\n7) Exit ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            listAllPlanets(PlanetBodies);
            break;

        case 2:
            addAPlanet(PlanetBodies);
            break;

        case 3:
            circularOrbitInfo(PlanetBodies);
            break;

        case 4:
            
            break;

        case 5:
            
            break;

        case 6:
            
            break;
        
        default:
            break;
    }
    
    } while (choice != 7);
        

 
    return 0;
}


void addAPlanet( vector<Body> &PlanetBodies)
{

    
    string name;
    double mu;
    double r;

    cout << "You have selected to add a planet!"
        <<"\nPlease enter the planets name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Now enter the planets standard graviational constant (mu (m^3/s^-2)): ";
    cin >> mu;

    cout << "Finally enter the planets radius (km): ";
    cin >> r;


    PlanetBodies.emplace_back(name, mu, r);

}

void listAllPlanets(const vector<Body> &PlanetBodies)
{
    for(int i = 0; i < PlanetBodies.size(); ++i)
    {
        Body const &body = PlanetBodies[i];
        cout <<"\nPlanet name: " << body.getName();
        cout <<"\nPlanet mu: " << body.getMU();
        cout <<"\nPlanet radius: " << body.getRadius(); 
    }


}

void circularOrbitInfo(const vector<Body> &PlanetBodies)
{
    int choice;

    double orbitalRadius, 
        orbitalRadiusInMeters, 
        orbitalSpeed, 
        orbitalPeriod, 
        userAltitude;
    
    cout << "\nPlease selector the planet that you want to display the circular orbit info of:";
    for(int i = 0; i < PlanetBodies.size(); ++i)
    {        
        Body const &body = PlanetBodies[i];
        
        cout << "\n" << i + 1 << ") " << body.getName();
    }
    cout << "\nInput: ";
    cin >> choice;
    Body const &body = PlanetBodies[choice - 1];

    
    cout << "You have selected the " << body.getName() << " as your planet."
        << "\nWhat would be the orbital altitude in kilometers? ";
    
    cin >> userAltitude;

    cout << "\nGiven the planet is " << body.getName() << " and the orbital altitude is " << fixed << setprecision(2) << userAltitude 
        << " km, here is the relevant information (Note: all calculations are rounded to the nearest hundredth): ";
        
    orbitalRadius = body.getRadius() + userAltitude; //in km
    orbitalRadiusInMeters = orbitalRadius * 1000;
    orbitalSpeed = sqrt((body.getMU() / orbitalRadiusInMeters));
    orbitalPeriod = 2 * PI * sqrt((( orbitalRadiusInMeters * orbitalRadiusInMeters * orbitalRadiusInMeters) / body.getMU()));


    //
    cout << "\nThe orbital radius is: " << orbitalRadius << " km";
    cout << "\nThe orbital speed is: " << orbitalSpeed << " m/s";
    cout << "\nThe orbital Period is: " << orbitalPeriod << " s";

}
