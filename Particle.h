//
//  Particle.h
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#ifndef Particle_h
#define Particle_h

#include <stdio.h>
#include "vector3.h"

class Particle{
public:
    void Update(float deltaTime);
    void Draw();
    void ApplyForce(Vector3 &f)     { Force+=f; }
    
    Vector3 getForce()              { return Force; }
    Vector3 getPosition()           { return Position; }
    Vector3 getVelocity()           { return Velocity; }
    float getMass()                 { return mass; }
    bool isFixed()                  { return fixed; }
    
    void setForce(Vector3 f)        { Force = f; }
    void setPosition(Vector3 p)     { Position = p; }
    void setVelocity(Vector3 v)     { Velocity = v; }
    void setMass(float m)           { mass = m; }
    void setFixed(bool f)           { fixed = f; }
    
private:
    float mass;
    Vector3 Position;
    Vector3 Velocity;
    Vector3 Force;
    bool fixed;
    
};
#endif /* Particle_h */
