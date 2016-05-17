//
//  ParticleSystem.h
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#ifndef ParticleSystem_h
#define ParticleSystem_h

#include <stdio.h>
#include "Particle.h"

class ParticleSystem{
public:
    void Update(float deltaTime);
    void Draw();
    
private:
    int NumParticles;
    Particle *Particles;
};
#endif /* ParticleSystem_h */
