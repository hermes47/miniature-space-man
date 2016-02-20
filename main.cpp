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
#include "matrix.hpp"
#include "solver.hpp"
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
    ButcherTableau adaptive = CashKarp();
    ButcherTableau huen = Heun();
    double timeStep = 4/32.;
    double targetTime = 4;
        //ExplicitRungeKutta(initialEuler, time + i*timeStep, timeStep, euler, deltaYEqualsY);
    AdaptiveRungeKutta(initialEuler, time, targetTime, 0.0001, adaptive, deltaYEqualsTanYPlus1);
    cout << "Euler: y(t=" << targetTime << ") = " << initialEuler.pos << "\n";
    cout << "Difference from exact: " << exp(4.) - initialEuler.pos << "\n";
    ExplicitRungeKutta(initialMidPoint, time, targetTime, 1, adaptive, deltaYEqualsTanYPlus1);
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

int RowReductionTest()
{
    std::vector<std::vector<double>> matrixA(3);
    std::vector<std::vector<double>> matrixB(3);
    std::vector<double> vectorB(3);
    for (int row = 0; row < 3; row++)
    {
        matrixA[row].resize(6);
        matrixB[row].resize(3);
    }
    
    matrixA[0][0] = 2;
    matrixA[0][1] = -1;
    matrixA[0][2] = 0;
    matrixA[1][0] = -1;
    matrixA[1][1] = 2;
    matrixA[1][2] = -1;
    matrixA[2][0] = 0;
    matrixA[2][1] = -1;
    matrixA[2][2] = 2;
    matrixA[0][3] = 1;
    matrixA[0][4] = 0;
    matrixA[0][5] = 0;
    matrixA[1][3] = 0;
    matrixA[1][4] = 1;
    matrixA[1][5] = 0;
    matrixA[2][3] = 0;
    matrixA[2][4] = 0;
    matrixA[2][5] = 1;
    
    matrixB[0][0] = 2;
    matrixB[0][1] = 1;
    matrixB[0][2] = -1;
    matrixB[1][0] = -3;
    matrixB[1][1] = -1;
    matrixB[1][2] = 2;
    matrixB[2][0] = -2;
    matrixB[2][1] = 1;
    matrixB[2][2] = 2;
    vectorB[0] = 8;
    vectorB[1] = -11;
    vectorB[2] = -3;
   
    
    std::vector<double> vectorX = Solve(matrixB, vectorB);
    
    for (int row = 0; row < matrixB.size(); row++)
    {
        for (int col = 0; col < matrixB[row].size(); col++)
            cout << matrixB[row][col]  << ", ";
        cout << "\n";
    }

    for (int row = 0; row < vectorX.size(); row++)
        cout << vectorX[row] << ", ";
    
    cout << "\n";
    return 0;
}


double func(double x)
{
    return x * x * x - cos(x);
}

void NewtonTesting()
{
    double solved =  NewtonsRaphson(func, 0.5);
    cout << 10 << ", " << solved << "\n";
}

int main()
{
    NewtonTesting();
    return 0;
}

