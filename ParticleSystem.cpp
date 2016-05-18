//
//  ParticleSystem.c
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int width, int height){
//    NumParticles = width*height;
//    for(int i = 0; i < NumParticles; i++)
//        Particles[i] = new Particle();
}

void ParticleSystem::Update(float deltaTime){
    Vector3 gravity(0.0, -9.8, 0.0);
    for(int i = 0; i < NumParticles; i++){
        Vector3 force = gravity * Particles[i].getMass();
        Particles[i].ApplyForce(force);
    }
    
    for(int i = 0; i < NumParticles; i++){
        Particles[i].Update(deltaTime);
    }
}