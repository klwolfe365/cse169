//
//  ParticleTriangle.h
//  cse169
//
//  Created by Karen Wolfe on 5/17/16.
//
//

#ifndef ParticleTriangle_h
#define ParticleTriangle_h

#include <stdio.h>
#include "Particle.h"
#include "vector3.h"

class ParticleTriangle{
public:
    
    ParticleTriangle();
    ~ParticleTriangle();
    
    void SetParticles(Particle* p1, Particle* p2, Particle* p3);
    void SetParticle1(Particle* p1)     { this->p1 = p1; }
    void SetParticle2(Particle* p2)     { this->p2 = p2; }
    void SetParticle3(Particle* p3)     { this->p3 = p3; }
    Particle* GetParticle(int index);
    Particle* GetParticle1()            { return p1; }
    Particle* GetParticle2()            { return p2; }
    Particle* GetParticle3()            { return p3; }
    
    void setVelocity(Vector3 v)         { velocity = v; }
    void setNormal(Vector3 n)           { normal = n; }
    Vector3 getVelocity()               { return velocity; }
    Vector3 getNormal()                 { return normal; }
    
    void calculateNormal();
    void ComputeForce(Vector3 force);
    
private:
    Particle * p1;
    Particle * p2;
    Particle * p3;
    Vector3 normal;
    Vector3 velocity;
    
    float rho;
    float cd;
    
};
#endif /* ParticleTriangle_h */
