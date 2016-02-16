//
//  data.hpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 13/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#ifndef data_hpp
#define data_hpp

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

struct ParticleState
{
    double pos;
    double vel;
};

struct DeltaState
{
    double vel;
    double accel;
};

struct ButcherTableau
{
    boost::numeric::ublas::matrix<double> a;
    std::vector<double> b;
    std::vector<double> c;
};

ButcherTableau Euler();
ButcherTableau MidPoint();
ButcherTableau Heun();
ButcherTableau Ralston();
ButcherTableau GenericSecondOrder(double x);
ButcherTableau RK3();
ButcherTableau RK4();
ButcherTableau RK4_ThreeEighths();

ButcherTableau HeunEuler();
ButcherTableau BogackiShampine();
ButcherTableau RungeKuttaFehlberg();
ButcherTableau CashKarp();


#endif /* data_hpp */
