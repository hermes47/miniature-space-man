//
//  CelestialBody.hpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 27/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#ifndef CELESTIAL_BODY
#define CELESTIAL_BODY

#include <eigen3/Eigen/Dense>
#include <string>

class CelestialBody {
private:
    double mass_d;
    double radius_d;
    Eigen::Vector3d position_v3d;
    Eigen::Vector3d velocity_v3d;
    std::string name_s;
    int id_i;
    
public:
    double GetMass();
    Eigen::Vector3d GetPosition();
    double GetRadius();
    Eigen::Vector3d GetVelocity();
    
    void SetMass(double mass_d);
    void SetPosition(Eigen::Vector3d position_v3d);
    void SetPosition(double x_d, double y_d, double z_d);
    void SetRadius(double radius_d);
    void SetVelocity(Eigen::Vector3d velocity_v3d);
    
};

#endif /* CELESTIAL_BODY */
