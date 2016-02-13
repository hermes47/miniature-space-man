//
//  data.cpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 13/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#include "data.hpp"

// First order methods
ButcherTableau Euler()
{
    /**
     0 | 0
     ------
       | 1
     **/
    ButcherTableau tableau {{}, {1.}, {0.}};
    tableau.a.resize(1,1);
    tableau.a(0, 0) = 0.;
    
    return tableau;
}

// Second order methods
ButcherTableau MidPoint()
{
    /**
      0  |  0  0
     1/2 | 1/2 0
     ------------
         |  0  1
     **/
    ButcherTableau tableau {{}, {0., 1.0}, {0., 0.5}};
    tableau.a.resize(2, 2);
    
    for (int row = 0; row < 2; row++)
        for (int col = 0; col < 2; col++)
            if (row <= col)
                tableau.a(row, col) = 0.;
            else
                tableau.a(row, col) = 0.5;
    return tableau;
}

ButcherTableau Heun()
{
    /**
     0 |  0   0
     1 |  1   0
     ------------
       | 1/2 1/2
     **/
    ButcherTableau tableau {{}, {0.5, 0.5}, {0., 1.0}};
    tableau.a.resize(2, 2);
    
    for (int row = 0; row < 2; row++)
        for (int col = 0; col < 2; col++)
            if (row <= col)
                tableau.a(row, col) = 0.;
            else
                tableau.a(row, col) = 1.0;
    return tableau;
}

ButcherTableau Ralston()
{
    /**
     0   |  0   0
     2/3 | 2/3  0
     --------------
         | 1/4 3/4
     **/
    ButcherTableau tableau {{}, {0.25, 0.75}, {0., 2.0/3.0}};
    
    tableau.a.resize(2, 2);
    
    for (int row = 0; row < 2; row++)
        for (int col = 0; col < 2; col++)
            if (row <= col)
                tableau.a(row, col) = 0.;
            else
                tableau.a(row, col) = 2.0/3.0;
    
    return tableau;
}

ButcherTableau GenericSecondOrder(double x)
{
    ButcherTableau tableau {{}, {1.0 - 1.0/(2*x), 1.0/(2*x)}, {0., x}};
    tableau.a.resize(2, 2);
    
    for (int row = 0; row < 2; row++)
        for (int col = 0; col < 2; col++)
            if (row <= col)
                tableau.a(row, col) = 0.;
            else
                tableau.a(row, col) = x;
    
    return tableau;
}

// Third order methods
ButcherTableau RK3()
{
    ButcherTableau tableau {{}, {1./6., 2./3., 1./6.}, {0., 0.5, 1.}};
    tableau.a.resize(3, 3);
    
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            tableau.a(row, col) = 0.;
    
    tableau.a(2, 1) = 0.5;
    tableau.a(3, 1) = -1.0;
    tableau.a(3, 2) = 2.0;
    
    return tableau;
}

// Fourth order methods
ButcherTableau RK4()
{
    ButcherTableau tableau {{}, {1./6., 1./3., 1./3., 1./6.}, {0., 0.5, 0.5, 1.}};
    tableau.a.resize(4, 4);
    
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            tableau.a(row, col) = 0.;
    
    tableau.a(2, 1) = 0.5;
    tableau.a(3, 2) = 0.5;
    tableau.a(4, 3) = 1.0;
    
    return tableau;
}

ButcherTableau RK4_ThreeEighths()
{
    ButcherTableau tableau {{}, {0.125, 0.375, 0.375, 0.125}, {0., 1./3., 2./3., 1.}};
    tableau.a.resize(4, 4);
    
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            tableau.a(row, col) = 0.;
    
    tableau.a(2, 1) = 1./3.;
    tableau.a(3, 1) = -1./3.;
    tableau.a(4, 1) = 1.;
    tableau.a(3, 2) = 1.;
    tableau.a(4, 2) = -1.;
    tableau.a(4, 3) = 1.;
    return tableau;
}