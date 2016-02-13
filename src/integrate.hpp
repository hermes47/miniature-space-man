//
//  integrate.hpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 13/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#ifndef integrate_h
#define integrate_h

#include "data.hpp"
#include <vector>

void Euler(ParticleState &state, double time, double deltaTime, 
           DeltaState (*evaluateFunc)(const ParticleState&, double, double, const DeltaState&));

void MidPoint(ParticleState &state,double time, double deltaTime,
             DeltaState (*evaluateFunc)(const ParticleState&, double, double, const DeltaState&));

void Ralston(ParticleState &state,double time, double deltaTime,
             DeltaState (*evaluateFunc)(const ParticleState&, double, double, const DeltaState&));

void RK4(ParticleState &state, double time, double deltaTime, 
         DeltaState (*evaluateFunc)(const ParticleState&, double, double, const DeltaState&));

void ExplicitRungeKutta(ParticleState &state, double time, double deltaTime, const ButcherTableau &tableau,
                        DeltaState (*evaluateFunc)(const ParticleState&, double, double, const std::vector<DeltaState>&,
                                                   const ButcherTableau&, int));

#endif /* integrate_h */
