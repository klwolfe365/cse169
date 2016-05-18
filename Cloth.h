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
class Cloth{
public:
    Cloth();
    Cloth(int w, int h);
    ~Cloth();
    
    void initializeCloth();
    void initializeTriangles();
    void initializeSprings();
    void setFixedRow(int r);
    void setFixedColumn(int c);
    
    void Update(Vector3 vAir);
    void Draw();
    
    int getWidth()                  { return width; }
    int getHeight()                 { return height; }
    void setWidth(int w)            { width = w; }
    void setHeight(int h)           { height = h; }
    void setColor(float r, float g, float b);
    
private:
    int width, height;
    std::vector< std::vector<Particle *> > Particles;
    std::vector<SpringDamper *> springs;
    std::vector<ParticleTriangle *> triangles;
    Vector3 Color;
    
};
#endif /* Cloth_h */
