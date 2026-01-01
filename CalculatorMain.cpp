#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>



#include "Body.h"
#include "Orbit.h"
#include "Rocket.h"

const double PI = 3.14159265358979323846;

const double g0 = 9.80665; // force of gravity 

using namespace std;

struct Missions
{
    // will store final delta v , the body , and orbit info and then store that into a vector
    int missionNumber;
    double finalDeltaV;
    string PlanetName;

  
};

void addAPlanet( vector <Body> &PlanetBodies);

void listAllPlanets(const vector<Body> &PlanetBodies);

void circularOrbitInfo(const vector<Body> &PlanetBodies);

void hohmannTransfer(const vector<Body> &PlanetBodies);

void createRocketFromUser(vector <Rocket> &ProgramRockets);

void checkMissionFeasibility(const vector <Rocket> &ProgramRockets, const vector <Missions> &userMission);

int main()
{
    
    int choice;
    cout << "=== ORBITAL PLANNER PROJECT ===\n";
    
    
    vector <Body> PlanetBodies = { Body("Sun",   1.327e20, 695700),
                                Body("Earth", 3.986e14, 6371),
                                Body("Moon",  4.903e12, 1737.4)};

    // uses struct to store user missions will possibly use this in a text file or 
    vector <Missions> UserMissions = {{1,120,"Earth"}};

    vector <Rocket> ProgramRockets = {Rocket("TesterMK1" , 1200, 4800, 300)};

    
            
    do
    {
        cout <<"\n\nPlease select one of the following options: "
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
            createRocketFromUser(ProgramRockets);
            break;

        case 6:
            checkMissionFeasibility(ProgramRockets,UserMissions);
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
    
    int choice,userMissionNumber;
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

    cout << "To store this mission, please enter the mission number (integer): ";
    cin >> userMissionNumber;

    newMission.missionNumber = userMissionNumber;
    newMission.finalDeltaV = dvTotal;
    newMission.PlanetName = body.getName();
}

void createRocketFromUser(vector <Rocket> &Rockets)
{
    
    string userRocketName;
    double userDryMass, 
        userFuelMass, 
        userISP,
        dvTotal;
    
    cout << "\nYou have selected to create a rocket, what is the dry mass of the rocket in kg? ";
    cin >> userDryMass;
    cout << "What is the fuel mass in kg? ";
    cin >> userFuelMass;
    cout << "What is the ISP? ";
    cin >> userISP;
    cout << "And what do you want to name your rocket? ";
    cin.ignore();
    getline(cin,userRocketName);

    Rocket newUserRocket(userRocketName,userDryMass, userFuelMass ,userISP);

    
    dvTotal = newUserRocket.getDeltaV();

    Rockets.emplace_back(userRocketName,userDryMass,userFuelMass,userISP);

    cout << "Based on your rocket, here is the total delta v available: " << dvTotal;
   

}

void checkMissionFeasibility(const vector <Rocket> &ProgramRockets, const vector <Missions> &userMission)
{
    int userMissionChoice,userRocketChoice;
    
    cout << "\nPlease select the mission you want to check:";
    for(int i = 0; i < userMission.size(); ++i)
    {
        cout << "\nMission #: " << userMission[i].missionNumber;
        cout << "\nDelta V Cost: " << userMission[i].finalDeltaV;
        cout << "\nOrbiting on: " << userMission[i].PlanetName;
    }
    cin >> userMissionChoice;

    cout << "\nNow select the rocket you want to use: ";
    for(int i = 0; i <ProgramRockets.size(); ++i)
    {
        int counter = 1;
        Rocket const &Rocket = ProgramRockets[i];
        cout << "\nNumber: " << counter;
        cout << "\nName: " << Rocket.getName();
        cout << "\nDry Mass: " << Rocket.getDryMass();
        cout << "\nFuel Mass: " << Rocket.getFuelMass();
        cout << "\nTotal delta V: " << Rocket.getDeltaV();
        counter++;
    }
    cin >> userRocketChoice;
    Rocket const &Rocket = ProgramRockets[userRocketChoice - 1];

    cout << "\nThe delta v cost for the mission is: " << userMission[userMissionChoice - 1].finalDeltaV
        <<"\nThe available delta v for the rocket is: " << Rocket.getDeltaV();
    if(userMission[userMissionChoice - 1].finalDeltaV > Rocket.getDeltaV())
    {
        cout << "The rocket cannot preform this maneuver.";
    }
    else
    {
        cout << "The rocket can preform this maneuver.";
    }


}