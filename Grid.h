//
//  Grid.h
//  cse169
//
//  Created by Karen Wolfe on 5/30/16.
//
//

#ifndef Grid_h
#define Grid_h

#include <stdio.h>
#include <vector>
#include "Particle.h"
class Grid{
public:
    Grid();
    Grid(int x, int y, int z);
    ~Grid();
    
    void empty();
    void addParticle(Particle *p, int xCell, int yCell, int zCell);
    std::vector<Particle *> getParticles(int x_pos, int y_pos, int z_pos);
    int index(Particle *p, Vector3 bMin, float supportRadius);
    
    float x;
    float y;
    float z;
    
    std::vector<std::vector<Particle *> > data;
};
#endif /* Grid_h */
