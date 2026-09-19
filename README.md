# Orbital Planner

A simple C++ command-line program for performing basic orbital mechanics and spacecraft mission-planning calculations.

This was developed as a personal project to practice C++ programming, object-oriented design, and the application of fundamental orbital mechanics equations.

## Features

The program allows the user to:

* View available planetary bodies
* Add custom planetary bodies
* Calculate circular-orbit velocity and orbital period at a specified altitude
* Plan a Hohmann transfer between two circular orbits
* Calculate the required Δv for each Hohmann transfer
* Calculate approximate Hohmann transfer time
* Create custom rockets using dry mass, fuel mass, and specific impulse
* Calculate available rocket Δv using the Tsiolkovsky rocket equation
* Compare a rocket's available Δv against the requirements of a planned maneuver

## Orbital Calculations

### Circular Orbits

For a selected planetary body and orbital altitude, the program calculates the circular orbital velocity

$$
v = \sqrt{\frac{\mu}{r}}
$$

and orbital period

$$
T = 2\pi\sqrt{\frac{r^3}{\mu}}
$$

where:

* $(\mu\)$ is the gravitational parameter of the planetary body
* \(r\) is the orbital radius measured from the center of the body

### Hohmann Transfers

The program can calculate a two-burn Hohmann transfer between two circular orbits around the same planetary body.

It determines:

* Initial circular-orbit velocity
* Final circular-orbit velocity
* Transfer-orbit velocity at each burn
* Δv required for both burns
* Total maneuver Δv
* Approximate transfer time

### Rocket Δv

Rocket performance is calculated using the Tsiolkovsky rocket equation:

$$
\Delta v = I_{sp} g_0 \ln\left(\frac{m_0}{m_f}\right)
$$

where:

* \(I_{sp}\) is the engine specific impulse
* \(g_0\) is standard gravitational acceleration
* \(m_0\) is the initial rocket mass
* \(m_f\) is the final dry mass

The calculated rocket Δv can then be compared against a stored Hohmann-transfer mission to determine whether the rocket has sufficient Δv to perform the maneuver.

## Building

The project requires a C++17-compatible compiler.

Using `g++`:

```bash
g++ -std=c++17 -O2 CalculatorMain.cpp Body.cpp Rocket.cpp -o orbital_planner
```

Run the executable on Linux/macOS with:

```bash
./orbital_planner
```

or on Windows with:

```bash
orbital_planner.exe
```

## Project Structure

```text
Orbiter_Calculator/
├── CalculatorMain.cpp
├── Body.cpp
├── Body.h
├── Rocket.cpp
├── Rocket.h
└── Makefile
```

`Body` stores information associated with a planetary body, while `Rocket` stores vehicle properties and handles rocket Δv calculations. `CalculatorMain.cpp` contains the user interface and orbital-mechanics calculations.

## Limitations

This project is intended as a basic orbital-mechanics calculator rather than a full orbital simulation.

The current implementation assumes idealized orbital maneuvers and does not include:

* Numerical orbit propagation
* N-body gravitational effects
* Orbital inclination changes
* Atmospheric drag
* Finite-duration burns
* Trajectory visualization

Hohmann transfers are modeled as ideal two-impulse transfers between circular orbits around a single planetary body.

## Purpose

The primary goal of this project was to apply C++ programming concepts to a physics-based problem while gaining experience with basic orbital mechanics, object-oriented programming, user input validation, and numerical calculations.
