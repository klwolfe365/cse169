//
//  SpringDamper.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#include "SpringDamper.h"
SpringDamper::SpringDamper(){}
SpringDamper::SpringDamper(Particle * p1, Particle * p2){
    P1 = p1;
    P2 = p2;
}

SpringDamper::SpringDamper(Particle * p1, Particle * p2, float sc, float df, float rl){
    P1 = p1;
    P2 = p2;
    SpringConstant = sc;
    DampingFactor = df;
    RestLength = rl;
}

SpringDamper::~SpringDamper(){}

void SpringDamper::ComputeForce(){}
