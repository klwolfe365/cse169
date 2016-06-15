//
//  Cloth.h
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#ifndef Cloth_h
#define Cloth_h

#include <stdio.h>
#include <vector>
#include "Particle.h"
#include "ParticleTriangle.h"
#include "SpringDamper.h"
#include "Plane.h"
#include "Intersection.h"
#include "Segment.h"

class Cloth{
public:
    static const bool DEBUG = false;
    Cloth();
    Cloth(int w, int h);
    ~Cloth();
    
    void initializeCloth();
    void initializeTriangles();
    void initializeSprings();
    void initializeStiffningSprings();
    void setFixedRow(int r);
    void setFixedColumn(int c);
    void fixCorners();
    
    void Update(Vector3 vAir);
    void Draw();
    
    int getWidth()                  { return width; }
    int getHeight()                 { return height; }
    void setWidth(int w)            { width = w; }
    void setHeight(int h)           { height = h; }
    void setColor(float r, float g, float b);
    
    void PrintParticles();
    void Drag(Vector3 dir);
    
private:
    int width, height;
    std::vector< std::vector<Particle *> > Particles;
    std::vector<SpringDamper *> springs;
    std::vector<SpringDamper *> stiffningSprings;
    std::vector<ParticleTriangle *> triangles;
    Vector3 Color;
    float ratio;
    float elasticity;
    Plane ground;
    
    
    static const long LARGE_SPRING_CONST = 500.0;
    static const long LARGE_DAMP_CONST = 1.0;
    static const long LARGE_REST_LENGTH = 1.0;
    
    
};
#endif /* Cloth_h */
