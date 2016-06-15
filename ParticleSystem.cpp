//
//  ParticleSystem.c
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#include "ParticleSystem.h"
#define EPSILON 0.000001
#define DELTA_T 0.01

const Vector3 ParticleSystem::gravity = Vector3(0, -9.8, 0);

ParticleSystem::ParticleSystem(){}

ParticleSystem::ParticleSystem(Vector3 min, Vector3 max, int n, float hVal){
    bMin = min;
    bMax = max;
    NumParticles = n;
    domain = bMax - bMin;
    boxSize = bMax - bMin;
    h = 0.5;
    supportRadius = h*2.0;
    fluid_viscosity = 3;
    particle_mass = 1.98;
    k = 1.0;
    restDensity = 1000;
    int xRange = (int)ceil(domain.x/h);
    int yRange = (int)ceil(domain.y/h);
    int zRange = (int)ceil(domain.z/h);
    grid = new Grid(xRange, yRange, zRange);
    printf("bMin: %f %f %f", bMin.x, bMin.y, bMin.z);

    float v = 0.0;
    for(Plane * w: walls){
        w->color.Set(v, 1.0, 1.0);
        v += 0.2;
    }
    printf("Walls: %lu", walls.size());
    Init();
    initKernelFunctions();
    UpdateGrid();
}

void ParticleSystem::Init(){
    //initial domain for particles
    int count = 0;
    float spacing = h/2.0;
    int pId = 0;
    float x_start = domain.x/4.0 + bMin.x;
    float y_start = domain.y/2.0 + bMin.y;
    float z_start = domain.z/4.0 + bMin.z;
    float x_end = bMax.x - domain.x/4.0;
    float y_end = bMax.y - domain.y/2.0;
    float z_end = bMax.z - domain.z/4.0;
    for(double y = y_start; y < bMax.y; y+=(spacing)){
        for(double x = x_start; x < x_end; x+=(spacing)){
                for(double z = z_start; z < z_end; z+=(spacing)) {
                    if(count < NumParticles){
                        Particle * p = new Particle();
                        pId = count;
                        p->setId(pId);
                        p->setPosition(Vector3(x,y_end,z));
                        p->setAcceleration(Vector3(0,0,0));
                        p->setPrevVelocity(Vector3(0,0,0));
                        p->setDensity(restDensity);
                        p->setPressure(0);
                        p->setForce(Vector3(0, 0, 0));
                        float randomNum = ((float) rand()) / (float) RAND_MAX;
                        p->setColor(Vector3(0.2+(0.4*randomNum), 0.1+(0.8*randomNum), 0.7+(0.2*randomNum)));
                        count++;
                        Particles.push_back(p);
                        printf("Position %d: %f %f %f\n", count, x, y_end, z);
                    }
                    
                }
            }
    }
    
    while(count < NumParticles){
        printf("!");
        Particle * p = new Particle();
        pId++;
        p->setId(pId);
        p->setPosition(Vector3(0,0,0));
        p->setAcceleration(Vector3(0,0,0));
        p->setPrevVelocity(Vector3(0,0,0));
        p->setDensity(restDensity);
        p->setPressure(0);
        p->setForce(Vector3(0, 0, 0));
        float randomNum = ((float) rand()) / (float) RAND_MAX;
        p->setColor(Vector3(0.2+(0.4*randomNum), 0.1+(0.8*randomNum), 0.7+(0.2*randomNum)));
        count++;
        Particles.push_back(p);
    }
    
    printf("Finished init!");
}

void ParticleSystem::initKernelFunctions(){
    mPolyKernel = 315/(64*M_PI*pow(h,9.0));
    mSpikyKernel = -45/(M_PI*pow(h,6));
    mViscosityKernel = 45/(M_PI*pow(h, 6));
    
    printf("Poly: %f, Spiky: %f, Visc: %f", mPolyKernel, mSpikyKernel, mViscosityKernel);
}

void ParticleSystem::Update(float deltaTime){
    
    UpdateGrid();
    clearAcceleration();
    computeDenisty();
    computePressure();
    checkWallCollisions();
    step(deltaTime);
}

void ParticleSystem::Draw(){
    for(int i = 0; i < NumParticles; i++){
        Particles[i]->Draw();
    }

    drawWireBoxColored(bMin.x, bMin.y, bMin.z, bMax.x, bMax.y, bMax.z, 1.0, 1.0, 1.0);
}

std::vector<Particle *> ParticleSystem::GetNeighbors(Particle *p){
    std::vector<Particle *> neighbors;
    Vector3 pos = p->getPosition();
    int xCell = floor((pos.x - bMin.x)/h);
    int yCell = floor((pos.y - bMin.y)/h);
    int zCell = floor((pos.z - bMin.z)/h);
    for(int x = xCell - 1; x <= xCell + 1; x++){
        if(x<0) continue;
        if(x>=grid->x) break;
        for(int y = yCell - 1; y <= yCell + 1; y++){
            if(y<0) continue;
            if(y>=grid->y) break;
            for(int z = xCell - 1; z <= zCell + 1; z++){
                if(z<0) continue;
                if(z>=grid->z) break;
                std::vector<Particle *> currneighbors = grid->getParticles(x,y,z);
                for(Particle * n : currneighbors){
                    neighbors.push_back(n);
                }
            }
        }
    }
    return neighbors;
}

void ParticleSystem::UpdateGrid(){
    EmptyGrid();
    for(Particle * particle : Particles){
        Vector3 pos = particle->getPosition();
        int newGridX = floor((pos.x - bMin.x)/h);
        int newGridY = floor((pos.y - bMin.y)/h);
        int newGridZ = floor((pos.z - bMin.z)/h);
        
        if(newGridX < 0)
            newGridX = 0;
        else if(newGridX >= grid->x)
            newGridX = grid->x - 1;
        
        if(newGridY < 0)
            newGridY = 0;
        else if(newGridY >= grid->y)
            newGridY = grid->y - 1;
        
        if(newGridZ < 0)
            newGridZ = 0;
        else if(newGridZ >= grid->z)
            newGridZ = grid->z - 1;
        grid->addParticle(particle, newGridX, newGridY, newGridZ);
    }
}

void ParticleSystem::EmptyGrid(){
    grid->empty();
}

float ParticleSystem::W(float q){
    return (1/pow(h, 3))*f(q);
}

float ParticleSystem::f(float q){
    if(q >= 2)
        return 0.0f;
    
    float res = 0.0f;
    if(q < 1)
        res = 2/3 - q*q + 0.5*pow(q,3);
    else if(q < 2)
        res = 1/6*pow((2-q),3);
    return 3/(2*M_PI)*res;
}

float ParticleSystem::CalculatePressure(float d){
    float densityRatio = d/restDensity;
    return k*(pow(densityRatio, 7) - 1);
}

void ParticleSystem::clearAcceleration(){
    for(int i = 0; i < NumParticles; i++){
        Particles[i]->setAcceleration(Vector3(0,0,0));
        Particles[i]->setForce(Vector3(0, 0, 0));
        
    }
}

void ParticleSystem::computeDenisty(){
    float h2 = h*h;
    
    for(int i = 0; i < NumParticles; i++){
        std::vector<Particle *> neighbors = GetNeighbors(Particles[i]);
        
        Vector3 pi = Particles[i]->getPosition();
        float sum = 0;
        Particles[i]->setDensity(0);
        Particles[i]->setPressure(0);
        float density = 0;
        float pressure = 0;
        
        for(int j = 0; j < neighbors.size(); j++){
            Vector3 pj = neighbors[j]->getPosition();
            float rad = (pj-pi).Mag();
            float rad2 = rad * rad;
            if(h2 > rad2 && EPSILON <= rad2){
                float cubic = h2 - rad2;
                float d = cubic * cubic * cubic;
                sum += d;
            }
        }
        density += (sum * mPolyKernel * particle_mass); 
        pressure += k * (density-restDensity);
        Particles[i]->setDensity(density);
        Particles[i]->setPressure(pressure);
    }
}

void ParticleSystem::computePressure(){
    float h2 = h*h;
    
    for(int i = 0; i < NumParticles; i++){
        std::vector<Particle *> neighbors = GetNeighbors(Particles[i]);
        
        Vector3 pi = Particles[i]->getPosition();
        Vector3 vi = Particles[i]->getVelocity();
        float pressure_i = Particles[i]->getPressure();
        
        Vector3 sumPressure = Vector3(0, 0, 0);
        Vector3 sumViscosity = Vector3(0, 0, 0);
        for(int j = 0; j < neighbors.size(); j++){
            Vector3 pj = neighbors[j]->getPosition();
            Vector3 vj = neighbors[j]->getVelocity();
            float pressure_j = neighbors[j]->getPressure();
            float density_j = neighbors[j]->getDensity();
            
            Vector3 diff = pi - pj;
            float rad = diff.Mag();
            float rad2 = rad * rad;
            
            if(h2 > rad2 && EPSILON <= rad2){
                float sqr = h - rad;
                sumPressure += diff/rad * ((pressure_i+pressure_j)/(2*density_j)) * sqr * sqr;
                sumViscosity += (vj - vi)/density_j * sqr;
            }
        }
        
        Particles[i]->addForce(sumPressure * (float(particle_mass) * mSpikyKernel * -1.0f));
        Particles[i]->addForce(sumViscosity * float(fluid_viscosity*particle_mass)*mViscosityKernel);
        
    }
}

void ParticleSystem::checkWallCollisions(){
    float wallStiffness = 500.0;
    float wallDamper = 0.5;
    float radius = h*0.2;
    float diff;
    float adj;
    Vector3 normal;
    float padding = h * 0.7;
    
    for(int i = 0; i < NumParticles; i++){
        Particle * p = Particles[i];
        
        //X Walls - Left and Right
        normal = Vector3(1,0,0);
        diff = 2*radius - (p->getPosition().x - (bMin.x+padding));
        if(diff > EPSILON){
            adj = wallStiffness * diff - wallDamper*(normal.Dot(p->getPrevVelocity()));
            p->setAcceleration(p->getAcceleration() + float(adj)*normal);
        }
        
        normal = Vector3(-1,0,0);
        diff = 2*radius - ((bMax.x-padding) - p->getPosition().x);
        if(diff > EPSILON){
            adj = wallStiffness * diff - wallDamper*(normal.Dot(p->getPrevVelocity()));
            p->setAcceleration(p->getAcceleration() + float(adj)*normal);
        }
        
        //Y wall bottom
        normal = Vector3(0,1,0);
        diff = 2*radius - (p->getPosition().y - (bMin.y+padding));
        if(diff > EPSILON){
            printf("HIT\n");
            adj = wallStiffness * diff - wallDamper*(normal.Dot(p->getPrevVelocity()));
            p->setAcceleration(p->getAcceleration() + (float(adj)*normal));
        }
        
        //Z walls - Front and Back
        normal = Vector3(0,0,1);
        diff = 2*radius - (p->getPosition().z - (bMin.z+padding));
        if(diff > EPSILON){
            adj = wallStiffness * diff - wallDamper*(normal.Dot(p->getPrevVelocity()));
            p->setAcceleration(p->getAcceleration() + float(adj)*normal);
        }
        
        normal = Vector3(0,0,-1);
        diff = 2*radius - ((bMax.z-padding) - p->getPosition().z);
        if(diff > EPSILON){
            adj = wallStiffness * diff - wallDamper*(normal.Dot(p->getPrevVelocity()));
            p->setAcceleration(p->getAcceleration() + float(adj)*normal);
        }
    }
}

void ParticleSystem::step(float dt){
    for(int i = 0; i < NumParticles; i++){
        Particle * p = Particles[i];
        Vector3 a = p->getAcceleration();
        Vector3 f = p->getForce();
        a += p->getForce()/p->getDensity();
        a += gravity;
        p->setAcceleration(a);
        
        Vector3 v = p->getVelocity();
        v += a * dt;
        p->setVelocity(v);

        Vector3 pos = p->getPosition();
        pos += v * dt;
        p->setPosition(pos);
    }
}

/* Following Gradients/Laplacians based off different Kernel functions
 * https://www8.cs.umu.se/kurser/TDBD24/VT06/lectures/sphsurvivalkit.pdf
 */
float ParticleSystem::WPoly6(float radiusSqr){
    static float coeff = 315.0/(64.0*M_PI*pow(h,9));
    static float hSqr = h*h;
    
    return coeff * pow(hSqr - radiusSqr, 3);
}

Vector3 ParticleSystem::WPoly6Gradient(Vector3 positionDiff, double radiusSqr, Vector3& gradient){
    static float coeff = -945.0/(32.0*M_PI*pow(h,9));
    static float hSqr = h*h;
    
    return coeff * pow(hSqr - radiusSqr, 2) * positionDiff;
}

Vector3 ParticleSystem::WSpikyGradient(Vector3 positionDiff, double radiusSqr, Vector3& gradient){
    static float coeff = -45.0/(M_PI*pow(h,6));
    float rad = sqrt(radiusSqr);
    
    return coeff * pow(h-rad, 2) * positionDiff / rad;
}

float ParticleSystem::WViscosityLaplacian(float radiusSqr){
    static float coeff = 45.0/(M_PI*pow(h,6));
    double rad = sqrt(radiusSqr);
    
    return coeff * (h - rad);
}

float ParticleSystem::WPoly6Laplacian(float radiusSqr){
    static float coeff = -945.0/(32.0*M_PI*pow(h,9));
    static float hSqr = h * h;
    
    return coeff * (hSqr - radiusSqr) * (3.0*hSqr - 7.0*radiusSqr);
}

void ParticleSystem::calculateWallCollisions(Particle *particle, Vector3 collisionVector){
    for(Plane * wall : walls){
        float dist = (wall->GetPoint()-particle->getPosition()).Dot(wall->GetNormal());
        //creates repulsion force against a wall
        if(dist > 0.0){
            //            printf("!");
            Vector3 a = particle->getAcceleration();
            a += wall->k()*wall->GetNormal()*dist;
            a += wall->damping() * particle->getVelocity().Dot(wall->GetNormal()) * wall->GetNormal();
            
            particle->setAcceleration(a);
        }
    }
}