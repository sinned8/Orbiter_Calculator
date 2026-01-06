#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <cmath>

#include "Body.h"
#include "Rocket.h"

const double PI = 3.14159265358979323846;

using namespace std;

enum Validation {BODYMU, BODYR, ORBITALT, ROCKETDRYM, ROCKETFUELM, ROCKETISP, MAINMENU, LISTS};

struct Missions
{
    
    int missionNumber;
    double finalDeltaV;
    string PlanetName;

  
};

void validateUserInput(double &input, Validation);

void validateUserMenuInput(int &input, Validation);

void addAPlanet(vector <Body> &PlanetBodies);

void listAllPlanets(const vector<Body> &PlanetBodies);

void listAllMissions( const vector<Missions> &UserMissions);

void listAllRockets(const vector<Rocket> &ProgramRockets);

void circularOrbitInfo(const vector<Body> &PlanetBodies);

void hohmannTransfer(const vector<Body> &PlanetBodies, vector<Missions>& UserMissions);

void createRocketFromUser(vector <Rocket> &ProgramRockets);

void checkMissionFeasibility(const vector <Rocket> &ProgramRockets, const vector <Missions> &userMission);

int main()
{
    
    int choice;
    cout << "\n\t=== ORBITAL PLANNER PROJECT ===\n";
    
    
    vector <Body> PlanetBodies = { Body("Sun",   1.327e20, 695700),
                                Body("Earth", 3.986e14, 6371),
                                Body("Moon",  4.903e12, 1737.4)};

  
    vector <Missions> UserMissions = {{1,120,"Earth"},{2,670,"Earth"}};

    vector <Rocket> ProgramRockets = {Rocket("TesterMK1" , 1200, 4800, 300)};

    
            
    do
    {
        cout <<"\nPlease select one of the following options: "
        <<"\n1) List all bodies."
        <<"\n2) List all missions."
        <<"\n3) List all rockets."
        <<"\n4) Add a new planet / body."
        <<"\n5) Compute the circular orbit and display info."
        <<"\n6) Plan a Hohmann transfer."
        <<"\n7) Create a rocket."
        <<"\n8) Check if a rocket can do transfer."
        <<"\n9) Exit"
        <<"\nInput: ";
        cin >> choice;
        validateUserMenuInput(choice, Validation :: MAINMENU);

        switch (choice)
        {
        case 1:
            listAllPlanets(PlanetBodies);
            break;
        case 2:
            listAllMissions(UserMissions);
            break;
        case 3:
            listAllRockets(ProgramRockets);
            break;

        case 4:
            addAPlanet(PlanetBodies);
            break;

        case 5:
            circularOrbitInfo(PlanetBodies);
            break;

        case 6:
            hohmannTransfer(PlanetBodies,UserMissions);
            break;

        case 7:
            createRocketFromUser(ProgramRockets);
            break;

        case 8:
            checkMissionFeasibility(ProgramRockets,UserMissions);
            break;
        
        default:
            break;
    }
    
    } while (choice != 9);
        

 
    return 0;
}

void validateUserMenuInput(int &input, Validation v)
{
    const char* msg = "Invalid input, please enter a # > 0: ";

    switch (v)
    {
    case MAINMENU:
        
        while (true)
        {
            if (cin.fail())
            {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> input;
                continue;
            }
            else if (input <=0 && input > 9)
            {
                cout << "Please select a number between 1 and 9... ";
                cin >> input;
            }
            

            if (input >= 1 || input <=9) 
                return;

            cout << msg;
            cin >> input;
        }
        break;
    case LISTS:
        while (true)
        {
            if (cin.fail())
            {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> input;
                continue;
            }
             if (input > 0) 
                return;

            cout << msg;
            cin >> input;
        }
        break;  
    
    default:
        break;
    }
    

}

void validateUserInput(double &input, Validation v)
{
    const char* msg = "Invalid input, please enter a # > 0: ";
    
    switch (v)
    {
   
    
    case BODYMU:
        msg = "Invalid input, please enter mu > 0: ";
        break;
    
    case BODYR:
        msg = "Invalid input, please enter r > 0: ";
        break;

    case ORBITALT:
        msg = "Invalid altitude, please enter altitude > 0: ";
        break;
    case ROCKETDRYM:
        msg = "Invalid input, please enter a value > 0: ";
        break;
    case ROCKETFUELM:
        msg = "Invalid input, please enter a value > 0: ";
        break;
    case ROCKETISP:
        msg = "Invalid input, please enter a value > 0: ";
        break;
        
    default:
        break;
    }

    while (true)
    {
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << msg;
            cin >> input;
            continue;
        }

        if (input > 0) 
            return;

        cout << msg;
        cin >> input;
    }



}


void addAPlanet( vector<Body> &PlanetBodies)
{

    
    string name;
    double mu; // standard grav constant
    double r; // planet radius

    cout << "You have selected to add a planet!"
        <<"\nPlease enter the planets name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Now enter the planets standard graviational constant mu (m^3/s^-2): ";
    cin >> mu;
    validateUserInput(mu, Validation :: BODYMU);

    cout << "Finally enter the planets radius (km): ";
    cin >> r;
    validateUserInput(r,Validation :: BODYR);

    PlanetBodies.emplace_back(name, mu, r);

}


void listAllPlanets(const vector<Body> &PlanetBodies)
{
    cout <<"\n\tHere is a list of all of the planets...";
    for(int i = 0; i < PlanetBodies.size(); ++i)
    {
        Body const &body = PlanetBodies[i];
        cout <<"\nPlanet name: " << body.getName();
        cout <<"\nPlanet mu: " << body.getMU() << " m^3/s^2";
        cout <<"\nPlanet radius: " << body.getRadius() << " km" <<  "\n"; 
    }
}

void listAllRockets( const vector <Rocket> &ProgramRockets)
{
    cout << "\n\tHere is a list of all of the available rockets...\n";
    for(int i = 0; i < ProgramRockets.size(); ++i)
    {
        const Rocket& rocket = ProgramRockets[i];
        cout << "\nNumber: " << (i + 1);
        cout << "\nName: " << rocket.getName();
        cout << "\nDry Mass: " << rocket.getDryMass() << " kg";
        cout << "\nFuel Mass: " << rocket.getFuelMass()<< " kg";
        cout << "\nTotal delta V: " << rocket.getDeltaV()<< " m/s" << "\n";
    }
}

void listAllMissions(const vector<Missions> &UserMissions)
{
    cout << "\n\tHere is a list of all of the missions available...\n";
    for(int i = 0; i < UserMissions.size(); ++i)
    {
        cout << (i+1) << ") Mission #" << UserMissions[i].missionNumber << "\n"
            << "Final delta v: " << UserMissions[i].finalDeltaV << " m/s" << "\n"
            << "Orbit on planet: " <<UserMissions[i].PlanetName << "\n\n";
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
    validateUserMenuInput(choice, Validation :: LISTS);
    while(choice < 1 || choice > (int)PlanetBodies.size())
    {
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            cin >> choice;
            continue;
        }

        cout << "Please enter a valid # from the list...";
        cin >> choice;

        if(choice > 1 && choice <= (int)PlanetBodies.size())
        {
            continue;
        }
    }

    Body const &body = PlanetBodies[choice - 1];

    
    cout << "You have selected the " << body.getName() << " as your planet."
        << "\nWhat would be the orbital altitude in kilometers? "
        << "\nInput: ";
    
    cin >> userAltitude;
    validateUserInput(userAltitude, Validation :: ORBITALT);
    

    cout << "\nGiven the planet is " << body.getName() << " and the orbital altitude is " << fixed << setprecision(2) << userAltitude 
        << " km, here is the relevant information (Note: all calculations are rounded to the nearest hundredth): ";
        
    orbitalRadius = body.getRadius() + userAltitude; //in km
    orbitalRadiusInMeters = orbitalRadius * 1000;
    orbitalSpeed = sqrt(body.getMU() / orbitalRadiusInMeters);
    orbitalPeriod = 2 * PI * sqrt(( orbitalRadiusInMeters * orbitalRadiusInMeters * orbitalRadiusInMeters) / body.getMU());


    //maybe format these so first digit is in line with all outputs.
    cout << fixed << setprecision(2);
    cout << "\nThe orbital radius is: " << orbitalRadius << " km";
    cout << "\nThe orbital speed is: " << orbitalSpeed << " m/s";
    cout << "\nThe orbital Period is: " << orbitalPeriod << " s\n";

}

void hohmannTransfer(const vector<Body> &PlanetBodies, vector<Missions>& UserMissions)
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
    validateUserMenuInput(choice, Validation :: LISTS);
    while(choice < 1 || choice > (int)PlanetBodies.size())
    {
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            cin >> choice;
            continue;
        }

        cout << "Please enter a valid # from the list...";
        cin >> choice;

        if(choice > 1 && choice <= (int)PlanetBodies.size())
        {
            continue;
        }
    }
    

    Body const &body = PlanetBodies[choice - 1];

    cout << "What is the initial altitude (in km) of the orbit? ";
    cin >> h1;
    validateUserInput(h1, Validation :: ORBITALT);

    cout << "What is the final altitude (in km) of the orbit? ";
    cin >> h2;
    validateUserInput(h2, Validation :: ORBITALT);

    // computing orbital radii
    r1 = (body.getRadius() + h1) * 1000;
    r2 = (body.getRadius() + h2) * 1000;

    // computing transfer orbit semi major axis & circular speeds
    a = (r1 + r2) / 2.0;
    v1 = sqrt(body.getMU() / r1);
    v2 = sqrt(body.getMU() / r2);

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

    cout << "\nBased on your selection, the total delta v necessary for the manuver is: " << fixed << setprecision(2) << dvTotal << " m/s" 
        << "\nThe transfer time is roughly: " << fixed << setprecision(2) << transferTime << " seconds (or: " << fixed << setprecision(2) << (transferTime / 60) << " minutes, or: " 
        << fixed << setprecision(2) << (transferTime / 3600) << " hours. \n"  ;

    cout << "To store this mission, please enter the mission number (integer): ";
    cin >> userMissionNumber;
    validateUserMenuInput(userMissionNumber, Validation :: LISTS);

    newMission.missionNumber = userMissionNumber;
    newMission.finalDeltaV = dvTotal;
    newMission.PlanetName = body.getName();

    UserMissions.push_back(newMission);
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
    validateUserInput(userDryMass, Validation :: ROCKETDRYM);

    cout << "What is the fuel mass in kg? ";
    cin >> userFuelMass;
    validateUserInput(userFuelMass, Validation :: ROCKETFUELM);

    cout << "What is the ISP? ";
    cin >> userISP;
    validateUserInput(userISP,Validation :: ROCKETISP);

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
    for (int i = 0; i < (int)userMission.size(); ++i) 
    {
        cout << "\n" << (i + 1) << ") Mission #: " << userMission[i].missionNumber
            << " | Delta-V: " << userMission[i].finalDeltaV
            << " | Body: " << userMission[i].PlanetName;
    }
    cout << "\nInput: ";
    cin >> userMissionChoice;

   validateUserMenuInput(userMissionChoice, Validation :: LISTS);
   while(userMissionChoice < 1 || userMissionChoice > (int)userMission.size())
    {
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            cin >> userMissionChoice;
            continue;
        }

        cout << "Please enter a valid # from the list...";
        cin >> userMissionChoice;

        if(userMissionChoice > 1 && userMissionChoice <= (int)userMission.size())
        {
            continue;
        }
    }


    cout << "\nNow select the rocket you want to use: ";
    
    for(int i = 0; i <ProgramRockets.size(); ++i)
    {
        
        const Rocket& rocket = ProgramRockets[i];
        cout << "\nNumber: " << (i + 1);
        cout << " | Name: " << rocket.getName();
        cout << " | Dry Mass: " << rocket.getDryMass();
        cout << " | Fuel Mass: " << rocket.getFuelMass();
        cout << " | Total delta V: " << rocket.getDeltaV();
        
    }
    cout << "\nInput: ";
    cin >> userRocketChoice;
    validateUserMenuInput(userRocketChoice, Validation :: LISTS);
    while(userRocketChoice < 1 || userRocketChoice > (int)ProgramRockets.size())
    {
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            cin >> userRocketChoice;
            continue;
        }

        cout << "Please enter a valid # from the list...";
        cin >> userRocketChoice;

        if(userRocketChoice > 1 && userRocketChoice <= (int)userMission.size())
        {
            continue;
        }
    }

    const Rocket& rocket = ProgramRockets[userRocketChoice - 1];

    cout << "\nThe delta v cost for the mission is: " << userMission[userMissionChoice - 1].finalDeltaV << " m/s"
        <<"\nThe available delta v for the rocket is: " << rocket.getDeltaV() << " m/s";
    if(userMission[userMissionChoice - 1].finalDeltaV > rocket.getDeltaV())
    {
        cout << "\nThe rocket cannot preform this maneuver.\n";
    }
    else
    {
        cout << "\nThe rocket can preform this maneuver.\n";
    }


}