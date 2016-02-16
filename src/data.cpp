//
//  data.cpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 13/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#include "data.hpp"
#include <boost/numeric/ublas/io.hpp>

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
    
    tableau.a(1, 0) = 0.5;
    tableau.a(2, 0) = -1.0;
    tableau.a(2, 1) = 2.0;
    
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
    
    tableau.a(1, 0) = 0.5;
    tableau.a(2, 1) = 0.5;
    tableau.a(3, 2) = 1.0;
    
    return tableau;
}

ButcherTableau RK4_ThreeEighths()
{
    ButcherTableau tableau {{}, {0.125, 0.375, 0.375, 0.125}, {0., 1./3., 2./3., 1.}};
    tableau.a.resize(4, 4);
    
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            tableau.a(row, col) = 0.;
    
    tableau.a(1, 0) = 1./3.;
    tableau.a(2, 0) = -1./3.;
    tableau.a(3, 0) = 1.;
    tableau.a(2, 1) = 1.;
    tableau.a(3, 1) = -1.;
    tableau.a(3, 2) = 1.;
    return tableau;
}

// Embedded methods
ButcherTableau HeunEuler()
{
    /**
     0 |  0   0
     1 |  1   0
     ------------
       | 1/2 1/2
       |  1   0
     **/
    ButcherTableau tableau {{}, {0.5, 0.5, 1.0, 0.0}, {0., 1.0}};
    tableau.a.resize(2, 2);
    
    for (int row = 0; row < 2; row++)
        for (int col = 0; col < 2; col++)
            if (row <= col)
                tableau.a(row, col) = 0.;
            else
                tableau.a(row, col) = 1.0;
    return tableau;
}

ButcherTableau BogackiShampine()
{
    ButcherTableau tableau {{},
        {2./9., 1./3., 4./9., 0.,
         7./24., 1./4., 1./3., 1./8.},
        {0., 1./2., 3./4., 1.}};
    tableau.a.resize(4, 4);
    
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            tableau.a(row, col) = 0.;
    
    tableau.a(1, 0) = 1./2.;
    tableau.a(3, 0) = 2./9.;
    tableau.a(2, 1) = 3./4.;
    tableau.a(3, 1) = 1./3.;
    tableau.a(3, 2) = 4./9.;
    return tableau;
}

ButcherTableau RungeKuttaFehlberg()
{
    ButcherTableau tableau {{},
        {16./135., 0., 6656./12825., 28561/56430., -9./50., 2./55.,
            25./216., 0., 1408./2565., 2197./4104., -1./5, 0.},
        {0., 1./4., 3./8., 12./13., 1., 1./2}};
    tableau.a.resize(6, 6);
    
    for (int row = 0; row < 6; row++)
        for (int col = 0; col < 6; col++)
            tableau.a(row, col) = 0.;
    
    tableau.a(1, 0) = 1./4.;
    tableau.a(2, 0) = 3./32.;
    tableau.a(3, 0) = 1932./2197.;
    tableau.a(4, 0) = 439./216.;
    tableau.a(5, 0) = -8./27.;
    
    tableau.a(2, 1) = 9./32.;
    tableau.a(3, 1) = -7200./2197.;
    tableau.a(4, 1) = -8.;
    tableau.a(5, 1) = 2.;
    
    tableau.a(3, 2) = 7296./2197.;
    tableau.a(4, 2) = 3680./513.;
    tableau.a(5, 2) = -3544./2565.;
    
    tableau.a(4, 3) = -845./4104.;
    tableau.a(5, 3) = 1859./4104.;
    
    tableau.a(5, 4) = -11./40.;
    return tableau;
}

ButcherTableau CashKarp()
{
    ButcherTableau tableau {{},
        {37./378., 0., 250./621., 125/594., 0., 512./1771.,
            2825./27648., 0., 18575./48384., 13525./55296., 277./14336., 0.25},
        {0., 1./5., 3./10., 3./5., 1., 7./8.}};
    tableau.a.resize(6, 6);
    
    for (int row = 0; row < 6; row++)
        for (int col = 0; col < 6; col++)
            tableau.a(row, col) = 0.;
    
    tableau.a(1, 0) = 1./5.;
    tableau.a(2, 0) = 3./40.;
    tableau.a(3, 0) = 3./10.;
    tableau.a(4, 0) = -11./54.;
    tableau.a(5, 0) = 1631./55296.;
    
    tableau.a(2, 1) = 9./40.;
    tableau.a(3, 1) = -9./10.;
    tableau.a(4, 1) = 5./2.;
    tableau.a(5, 1) = 175./512;
    
    tableau.a(3, 2) = 6./5.;
    tableau.a(4, 2) = -70./27.;
    tableau.a(5, 2) = 575./13824.;
    
    tableau.a(4, 3) = 35./27.;
    tableau.a(5, 3) = 44275./110592.;
    
    tableau.a(5, 4) = -253./4096.;
    return tableau;
}