//
//  main.cpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 13/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#include <iostream>
#include "integrate.hpp"
#include "data.hpp"
#include <cmath>
#include <math.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
using namespace boost::numeric::ublas;

// (const ParticleState&, double, double, const vector<DeltaState>&, const ButcherTableau&)
DeltaState deltaYEqualsY(const ParticleState &state, double time, double deltaTime,
                         const std::vector<DeltaState> &ks, const ButcherTableau &tableau, int i)
{
    ParticleState newState;
    //newState.pos = state.pos + deltaTime * deltaState.vel;
    double deltaPos = 0., deltaVel = 0.;
    for (int j = 0; j < tableau.a.size1(); j++)
    {
        if (i > j)
        {
            deltaPos += tableau.a(i,j) * ks[j].vel;
            deltaVel += tableau.a(i,j) * ks[j].accel;
        }
    }
    newState.pos = state.pos + deltaTime * deltaPos;
    newState.vel = state.vel + deltaTime * deltaVel;
    
    DeltaState output;
    output.vel = newState.pos;
    return output;
}

DeltaState deltaYEqualsTanYPlus1(const ParticleState &state, const ParticleState &changeState, double time, double deltaTime)
{
    ParticleState newState;
    
    newState.pos = state.pos + deltaTime * changeState.pos;
    newState.vel = state.vel + deltaTime * changeState.vel;
    
    DeltaState output;
    output.vel = newState.pos; //tan(newState.pos) + 1;
    return output;
}

int IntegratorTest()
{
    cout << "Testing different integrators\n";
    cout << "Given dy/dt = y + t, and y(0) = 1, find y(4).\n";
     
    double time = 0.0;
    ParticleState initialEuler {1.0};
    ParticleState initialRalston {1.0};
    ParticleState initialRK4 {1.0};
    ParticleState initialMidPoint {1.0};
    ButcherTableau euler = Euler();
    ButcherTableau ralston = Ralston();
    ButcherTableau midpoint = MidPoint();
    ButcherTableau adaptive = HeunEuler();
    ButcherTableau huen = Heun();
    double timeStep = 1.;
    double targetTime = 4;
        //ExplicitRungeKutta(initialEuler, time + i*timeStep, timeStep, euler, deltaYEqualsY);
    AdaptiveRungeKutta(initialEuler, time, targetTime, 0.001, adaptive, deltaYEqualsTanYPlus1);
    cout << "Euler: y(t=" << targetTime << ") = " << initialEuler.pos << "\n";
    ExplicitRungeKutta(initialMidPoint, time, targetTime, 1, huen, deltaYEqualsTanYPlus1);
    cout << "Euler: y(t=" << targetTime << ") = " << initialMidPoint.pos << "\n";
//        Euler(initialEuler, time + i * timeStep, timeStep, deltaYEqualsY);
//        Ralston(initialRalston, time + i * timeStep, timeStep, deltaYEqualsY);
//        RK4(initialRK4, time + i * timeStep, timeStep, deltaYEqualsY);
//        MidPoint(initialMidPoint, time + i * timeStep, timeStep, deltaYEqualsY);

    //cout << "Euler:   y(4) = " << initialEuler.pos << "\n";
    //cout << "MidPoint:y(4) = " << initialMidPoint.pos << "\n";
    //cout << "Ralston: y(4) = " << initialRalston.pos << "\n";
    //cout << "RK4:     y(4) = " << initialRK4.pos << "\n";
    //cout << "Exact:   y(4) = " << exp(4) << "\n";
    //cout << 10 % 1 << "\n";
    return 0;
}

int main()
{
    IntegratorTest();
    return 0;
}

