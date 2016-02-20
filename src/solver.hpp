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

double NewtonsRaphson(double (*func)(double x), double xInitial, int maxIter = 50,
                      double tolerance = 1e-8, double epsilon = 1e-14);

double Derivative(double x, double (*func)(double x), double delta);

#endif /* solver_hpp */
