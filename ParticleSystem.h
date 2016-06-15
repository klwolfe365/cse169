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
#include <vector>
#include <list>
#include "Particle.h"
#include "Grid.h"
#include "Plane.h"

class ParticleSystem{
public:
    static const Vector3 gravity;    
    
    ParticleSystem();
    ParticleSystem(Vector3 min, Vector3 max, int n, float sR);
    void Init();
    void initKernelFunctions();
    void Update(float deltaTime);
    void Draw();
    
    //Helper functions for update
    void CalculateParticleChanges();
    std::vector<Particle *> GetNeighbors(Particle * p);
    void PlaceParticles();
    void UpdateGrid();
    void EmptyGrid();
    
    //Kernel Functions/Helper Kernel Functions
    float W(float q);
    float f(float q);
    
    float CalculatePressure(float d);
    
    float WPoly6(float radiusSqr);
    Vector3 WPoly6Gradient(Vector3 positionDiff, double radiusSqr, Vector3& gradient);
    Vector3 WSpikyGradient(Vector3 positionDiff, double radiusSqr, Vector3& gradient);
    float WViscosityLaplacian(float radiusSqr);
    float WPoly6Laplacian(float radiusSqr);
    void calculateWallCollisions(Particle * particle, Vector3 collisionVector);
    
    
    void clearAcceleration();
    void computeDenisty();
    void computePressure();
    void checkWallCollisions();
    void step(float dt);
    
    //Getters/Setters
    void setK(float kVal)           { k = kVal; }
    void setRestDensity(float d)    { restDensity = d; }
    
    
private:
    static const long KERNEL_SIZE = 0.5;
    Vector3 bMin;
    Vector3 bMax;
    Vector3 boxSize;
    Vector3 domain;
    float supportRadius;
    float h;                                //smoothing radius
    float k;                                //stiffness of fluid system
    float restDensity;
    int NumParticles;
    std::vector<Particle *> Particles;
    Grid* grid;
    std::vector<Plane *> walls;
    
    float fluid_viscosity;
    float particle_mass;
    
    float mPolyKernel;
    float mSpikyKernel;
    float mViscosityKernel;
};
#endif /* ParticleSystem_h */
