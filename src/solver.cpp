//
//  solver.cpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 21/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#include "solver.hpp"
#include "matrix.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

/*
 * Use Newton-Raphson to solve a given function.
 */
using namespace std;

double NewtonRaphson(double (*func)(double x), double xInitial, int maxIter, double tolerance, double epsilon)
{
    double x0 = xInitial, x1 = 0;
    for (int iter = 0; iter < maxIter; iter++)
    {
        double fx0 = func(x0);
        double fprimex0 = Derivative(x0, func, 1e-6);
        if (fprimex0 < epsilon)
        {
            cout << "Derivative close to 0. Unable to continue.\n";
            return x1;
        }
        
        x1 = x0 - fx0 / fprimex0;
        cout << setprecision(12) << x1 << "\n";
        if (abs(x0 - x1) < tolerance)
        {
            return x1;
        }
        x0 = x1;
    }
    cout << "Unconverged after " << maxIter << "iterations";
    return x1;
}


/*
 * Use Newton Raphson to solve an N length system of simultaneous equations.
 * A system of equations g(f) = [f1(x1,x2,...,xn), f2(x1,x2,...,xn), ..., fn(x1,x2,...,xn)]
 * Given an initial guess x0 = [x1(0), x2(0), ..., xn(0)]
 * Can be solved by: x(m+1) = x(m) - [Jg(x(m))]^-1 * g(x(m)) where Jg(x(m)) is the Jacobian.
 * Is can computatinally be simplified to x(m+1) = x(m) + s(m) where Jg(x(m))s(m) = -g(x(m))
 */
vector<double> NewtonRaphson(vector<double> (*func)(vector<double> x), vector<double> xInitial, int maxIter,
                             double tolerance)
{
    vector<double> x0 = xInitial, x1(xInitial.size());
    for (int iter = 0; iter < maxIter; iter++)
    {
        vector<double> fx0 = func(x0);
        cout << "f(x0) = : ";
        for (auto x : fx0)
            cout << x << ", ";
        cout << "\n";
        vector<double> deltas(xInitial.size(),1e-6);
        vector<vector<double>> jacobian = Jacobian(func, x0, deltas);
        
        vector<double> minusfx0;
        for (auto x: fx0)
            minusfx0.push_back(-1*x);
        
        vector<double> s0 = Solve(jacobian, minusfx0);
        cout << "s(0) = : ";
        for (auto x : s0)
            cout << x << ", ";
        cout << "\n";
        
        bool allWithinTolerance = true;
        for (int i = 0; i < xInitial.size(); i++)
        {
            x1[i] = x0[i] + s0[i];
            if (abs(x1[i] - x0[i]) > tolerance)
                allWithinTolerance = false;
        }
        cout << "f(x1) = : ";
        for (auto x : x1)
            cout << x << ", ";
        cout << "\n";
        
        if (allWithinTolerance)
            return x1;
        x0 = x1;
    }
    
    cout << "Unconverged after " << maxIter << "iterations";
    return x1;
}

/*
 * Determine the derivative of a function at x
 */
double Derivative(double x, double (*func)(double x), double delta)
{
    // Using a second order central finite difference method, because fast and easyish
    double fMinus1 = func(x - delta);
    double fPlus1 = func(x + delta);
    double derivative = (-0.5*fMinus1 + 0.5*fPlus1) / (delta );
    return derivative;
}

vector<double> Derivative(vector<double> vals, vector<double> (*func)(vector<double> vals), vector<double> deltas)
{
    vector<double> derivative(vals.size());
    // Using a second order central finite difference
    vector<double> fMinusOne(vals.size());
    vector<double> fPlusOne(vals.size());
    for (int i = 0; i < vals.size(); i++)
    {
        fMinusOne[i] = vals[i] - deltas[i];
        fPlusOne[i] = vals[i] + deltas[i];
    }
    
    fMinusOne = func(fMinusOne);
    fPlusOne = func(fPlusOne);
    
    double h;
    for (auto hi: deltas)
        h += hi;
    
    for (int i = 0; i < vals.size(); i++)
        derivative[i] = (-0.5*fMinusOne[i] + 0.5*fPlusOne[i]) / h;//deltas[i];
    
    return derivative;
}

/**
 * Determine the Jacobian of a function at the initial position vector
 **/
vector<vector<double>> Jacobian(vector<double> (*func)(vector<double> f), vector<double> vals, vector<double> deltas)
{
    // Unfortunately going by column in a row setup matrix. Bad memory managment. Possible to improve?
    // make sure the matrix is the correct size
    vector<vector<double>> jacobian(vals.size());
    for (int val = 0; val < vals.size(); val ++)
        jacobian[val].resize(vals.size());
    
    for (int fi = 0; fi < vals.size(); fi++)
    {
        vector<double> deltaFi(vals.size());
        deltaFi[fi] = deltas[fi];
        vector<double> derivatives = Derivative(vals, func, deltaFi);
        for (int row = 0; row < vals.size(); row++)
            jacobian[row][fi] = derivatives[row];
    }
    cout << "J(x0): \n";
    for (int row = 0; row < jacobian.size(); row++)
    {
        for (int col = 0; col < jacobian.size(); col++)
        {
            cout << jacobian[row][col] << ", ";
        }
        cout << "\n";
    }
    cout << "---------\n";
    
    return jacobian;
}


