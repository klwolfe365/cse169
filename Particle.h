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
    Particle();
    ~Particle();
    void Update(float deltaTime);
    void Draw();
    void ApplyForce(Vector3 &f)     { Force+=f; }
    void Reset();
    void UpdatePosition(Vector3 pos);
    
    Vector3 getForce()              { return Force; }
    Vector3 getPosition()           { return Position; }
    Vector3 getVelocity()           { return Velocity; }
    float getMass()                 { return mass; }
    bool isFixed()                  { return fixed; }
    Vector3 getColor()              { return Color; }
    
    void setForce(Vector3 f)        { Force.Set(f.x, f.y, f.z); }
    void setPosition(Vector3 p)     { Position.Set(p.x, p.y, p.z); }
    void setVelocity(Vector3 v)     { Velocity.Set(v.x,v.y,v.z); }
    void setMass(float m)           { mass = m; }
    void setFixed(bool f)           { fixed = f; }
    void setColor(Vector3 c)        { Color.Set(c.x, c.y, c.z); }
    
    void Print();
    
private:
    float mass;
    Vector3 Position;
    Vector3 Velocity;
    Vector3 Force;
    bool fixed;
    Vector3 Color;
    
};
#endif /* Particle_h */
