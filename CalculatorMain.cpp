#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>



#include "Body.h"
#include "Orbit.h"

const double PI = 3.14159265358979323846;

using namespace std;

struct Missions
{
    // will store final delta v , the body , and orbit info and then store that into a vector
    double finalDeltaV;
    string PlanetName;
  
};

void addAPlanet( vector <Body> &PlanetBodies);

void listAllPlanets(const vector<Body> &PlanetBodies);

void circularOrbitInfo(const vector<Body> &PlanetBodies);

void hohmannTransfer(const vector<Body> &PlanetBodies);

int main()
{
    
    int choice;
    cout << "=== ORBITAL PLANNER PROJECT ===\n";
    
    
    vector <Body> PlanetBodies = { Body("Sun",   1.327e20, 695700),
                                Body("Earth", 3.986e14, 6371),
                                Body("Moon",  4.903e12, 1737.4)};

    // uses struct to store user missions will possibly use this in a text file or 
    vector <Missions> UserMissions = {};

    
            
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
            hohmannTransfer(PlanetBodies);
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
    
    cout << "\nPlease select the planet that you want to display the circular orbit info of:";
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


    //maybe format these so first digit is in line with all outputs.
    cout << "\nThe orbital radius is: " << orbitalRadius << " km";
    cout << "\nThe orbital speed is: " << orbitalSpeed << " m/s";
    cout << "\nThe orbital Period is: " << orbitalPeriod << " s";

}

void hohmannTransfer(const vector<Body> &PlanetBodies)
{
    Missions newMission;
    
    int choice;
    double h1,   // initial alt
        h2,     // final alt
        a,      // transfer orbit semi-major axis
        v1,     // circular speeds
        v2,     // circular speeds
        r1,     // orbital radii
        r2,     // orbital radii
        v_t1,   // transfer orbit speed
        v_t2,   // transfer orbit speed
        dv1,    // burns
        dv2,    // burns 
        dvTotal, // Total delta V
        transferTime;   // transfer time 
    
    cout << "\nPlease select the planet that you are orbitting: ";
    for(int i = 0; i < PlanetBodies.size(); ++i)
    {        
        Body const &body = PlanetBodies[i];
        
        cout << "\n" << i + 1 << ") " << body.getName();
    }
    cout << "\nInput: ";
    cin >> choice;
    Body const &body = PlanetBodies[choice - 1];

    cout << "What is the initial altitude (in km) of the orbit? ";
    cin >> h1;
    cout << "What is the final altitude (in km) of the orbit? ";
    cin >> h2;

    // computing orbital radii
    r1 = body.getRadius() + h1;
    r2 = body.getRadius() + h2;

    // computing transfer orbit semi major axis & circular speeds
    a = (r1 + r2) / 2;
    v1 = sqrt((body.getMU()) / r1);
    v2 = sqrt((body.getMU()) / r2);

    // computing speeds on transfer orbit
    v_t1 = sqrt(body.getMU() * ((2/r1) - (1/a)));
    v_t2 = sqrt(body.getMU() * ((2/r2) - (1/a)));

    // computing burns
    dv1 = v_t1 - v1;
    dv2 = v_t2 - v2;

    // computing total delta v
    dvTotal = abs(dv1) + abs(dv2);

    //computing transfer time
    transferTime = PI * sqrt((a * a * a) / body.getMU());

    cout << "\nBased on your selection, the total delta v necessary for the manuver is: " << dvTotal 
        << "\nThe transfer time is roughly: " << transferTime;

    newMission.finalDeltaV = dvTotal;
    newMission.PlanetName = body.getName();
}