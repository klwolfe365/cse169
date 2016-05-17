//
//  Particle.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#include "Particle.h"

void Particle::Update(float deltaTime){
    Vector3 accel = (1.0/mass) * Force;
    
    Velocity += accel*deltaTime;
    Position += Velocity*deltaTime;
    
    Force.Zero();
}