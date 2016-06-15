//
//  Grid.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/30/16.
//
//

#include "Grid.h"


Grid::Grid(){}

Grid::Grid(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
    
    for(int z1 = 0; z1 < z; z1++){
        for(int y1 = 0; y1 < y; y1++){
            for(int x1 = 0; x1 < x; x1++){
                data.push_back(std::vector<Particle *>());
            }
        }
    }
}

void Grid::empty(){
    for(int z_pos = 0; z_pos < z; z_pos++){
        for(int y_pos = 0; y_pos < y; y_pos++){
            for(int x_pos = 0; x_pos < x; x_pos++){
                data[x_pos + x*y_pos + x*y*z_pos].clear();
            }
        }
    }
}

void Grid::addParticle(Particle *p, int xCell, int yCell, int zCell){
    int cell = xCell + x*yCell + x*y*zCell;
    data[cell].push_back(p);
}

std::vector<Particle *> Grid::getParticles(int xCell, int yCell, int zCell){
    int cell = xCell + x*yCell + x*y*zCell;
    return data[cell];
}