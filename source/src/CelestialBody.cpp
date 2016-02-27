//
//  CelestialBody.cpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 27/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#include "CelestialBody.hpp"
#include <eigen3/Eigen/Dense>
#include <string>

double CelestialBody::GetMass(){
    return mass_d;
}