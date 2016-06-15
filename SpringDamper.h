//
//  SpringDamper.h
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#ifndef SpringDamper_h
#define SpringDamper_h

#include <stdio.h>
#include "Particle.h"
class SpringDamper{
public:
    static const long SPRING_CONST = 200.0;
    static const long DAMP_CONST = 10.0;
    static const long REST_LENGTH = 0.5;
    
    SpringDamper();
    SpringDamper(Particle * p1, Particle * p2);
    SpringDamper(Particle * p1, Particle * p2, float rl);
    SpringDamper(Particle * p1, Particle * p2, float sc, float df, float rl);
    ~SpringDamper();
    void ComputeForce();
    
    void setSpringConstant(float s)     { SpringConstant = s; }
    void setDampingFactor(float f)      { DampingFactor = f; }
    void setRestLength(float r)         { RestLength = r; }
    void setP1(Particle *p)             { P1 = p; }
    void setP2(Particle *p)             { P2 = p; }
    
    float getSpringConstant()           { return SpringConstant; }
    float getDampingFactor()            { return DampingFactor; }
    float getRestLength()               { return RestLength; }
    Particle* getP1()                   { return P1; }
    Particle* getP2()                   { return P2; }
    
    void Draw();
    
    Vector3 color;
    
private:
    float SpringConstant;
    float DampingFactor;
    float RestLength;
    Particle *P1;
    Particle *P2;

};
#endif /* SpringDamper_h */
