//
//  solver.cpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 21/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#include "solver.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

/*
 * Use Newton-Raphson to solve a given function.
 */
using namespace std;

double NewtonsRaphson(double (*func)(double x), double xInitial, int maxIter, double tolerance, double epsilon)
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


