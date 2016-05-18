//
//  ParticleTriangle.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/17/16.
//
//

#include "ParticleTriangle.h"

ParticleTriangle::ParticleTriangle(){
    rho = 1.225; //Default density - air
    cd = 1.0;
}

ParticleTriangle::~ParticleTriangle(){}//TODO

void ParticleTriangle::SetParticles(Particle* p1, Particle* p2, Particle* p3){
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Particle* ParticleTriangle::GetParticle(int index){
    if(index == 0)
        return p1;
    if(index == 1)
        return p2;
    return p3;
}

void ParticleTriangle::calculateNormal(){
    Vector3 a = (p2->getPosition() - p1->getPosition());
    Vector3 b = (p3->getPosition() - p1->getPosition());
    
    normal.Cross(a, b);
    normal.Normalize();
}

void ParticleTriangle::ComputeForce(Vector3 force){
    //TODO
    velocity = (p1->getVelocity() + p2->getVelocity() + p3->getVelocity())/3.0;
    Vector3 v = velocity - force;
    Vector3 a = p2->getPosition() - p1->getPosition();
    Vector3 b = p3->getPosition() - p1->getPosition();
    Vector3 n;
    n.Cross(a, b);
    
    //Simplified aero vector calculations
    Vector3 vMagAN = ((v.Mag()*v.Dot(n))/(2.0f*n.Mag())) * n;
    Vector3 aeroForce = (-0.5f) * rho * cd * vMagAN;
    aeroForce = aeroForce / 3.0;
    p1->ApplyForce(aeroForce);
    p2->ApplyForce(aeroForce);
    p3->ApplyForce(aeroForce);
    
    normal = n.Normalize();
}