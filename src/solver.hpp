//
//  solver.hpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 21/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#ifndef solver_hpp
#define solver_hpp

#include <stdio.h>
#include <vector>

double NewtonRaphson(double (*func)(double x), double xInitial, int maxIter = 50,
                      double tolerance = 1e-8, double epsilon = 1e-14);

std::vector<double> NewtonRaphson(std::vector<double> (*func)(std::vector<double> x), std::vector<double> xInitial,
                                  int maxIter = 50, double tolerance = 1e-8);

double Derivative(double x, double (*func)(double x), double delta);

std::vector<double> Derivative(std::vector<double> vals, std::vector<double> (*func)(std::vector<double> vals),
                               std::vector<double> deltas);

std::vector<std::vector<double>> Jacobian(std::vector<double> (*func)(std::vector<double> f), std::vector<double> vals,
                                          std::vector<double> deltas);
#endif /* solver_hpp */
