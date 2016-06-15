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
    float Kernel(float q);
    
    void addForce(Vector3 f)        { Force += f; }
    
    float getMass()                 { return mass; }
    float getDensity()              { return density; }
    float getPressure()             { return pressure; }
    Vector3 getPosition()           { return Position; }
    Vector3 getVelocity()           { return Velocity; }
    Vector3 getAcceleration()       { return Acceleration; }
    Vector3 getNormal()             { return Normal;}
    Vector3 getForce()              { return Force; }
    bool isFixed()                  { return fixed; }
    Vector3 getColor()              { return Color; }
    Vector3 getPrevPosition()       { return prevPosition; }
    Vector3 getPrevVelocity()       { return prevVelocity; }
    int id()                        { return particleId; }
    
    void setMass(float m)           { mass = m; }
    void setDensity(float d)        { density = d; }
    void setPressure(float p)       { pressure = p; }
    void setPosition(Vector3 p)     { Position.Set(p.x, p.y, p.z); }
    void setVelocity(Vector3 v)     { Velocity.Set(v.x,v.y,v.z); }
    void setAcceleration(Vector3 a) { Acceleration.Set(a.x, a.y, a.z); }
    void setForce(Vector3 f)        { Force.Set(f.x, f.y, f.z); }
    void setNormal(Vector3 v)       { Normal.Set(v.x,v.y,v.z); }
    void setFixed(bool f)           { fixed = f; }
    void setColor(Vector3 c)        { Color.Set(c.x, c.y, c.z); }
    void setPrevPosition(Vector3 p) { prevPosition.Set(p.x, p.y, p.z); }
    void setPrevVelocity(Vector3 p) { prevVelocity.Set(p.x, p.y, p.z); }
    void setId(int i)               { particleId = i; }
    
    void Print();
    
private:
    float mass;
    float density;
    float pressure;
    Vector3 Position;
    Vector3 Velocity;
    Vector3 Acceleration;
    Vector3 Force;
    Vector3 Normal;
    bool fixed;
    Vector3 Color;
    Vector3 prevPosition;
    Vector3 prevVelocity;
    
    
    int particleId;
    
};
#endif /* Particle_h */
