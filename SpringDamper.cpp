//
//  SpringDamper.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#include "SpringDamper.h"
SpringDamper::SpringDamper(){
    P1 = NULL;
    P2 = NULL;
    SpringConstant = SPRING_CONST;
    DampingFactor = DAMP_CONST;
    RestLength = REST_LENGTH;
    color.Set(1.0, 1.0, 1.0);
}

SpringDamper::SpringDamper(Particle * p1, Particle * p2){
    P1 = p1;
    P2 = p2;
    SpringConstant = SPRING_CONST;
    DampingFactor = DAMP_CONST;
    RestLength = REST_LENGTH;
    color.Set(1.0, 1.0, 1.0);
}

SpringDamper::SpringDamper(Particle * p1, Particle * p2, float rl){
    P1 = p1;
    P2 = p2;
    SpringConstant = SPRING_CONST;
    DampingFactor = DAMP_CONST;
    RestLength = rl;
    color.Set(1.0, 1.0, 1.0);
}

SpringDamper::SpringDamper(Particle * p1, Particle * p2, float sc, float df, float rl){
    P1 = p1;
    P2 = p2;
    SpringConstant = sc;
    DampingFactor = df;
    RestLength = rl;
    color.Set(1.0, 1.0, 1.0);
}

SpringDamper::~SpringDamper(){}

void SpringDamper::ComputeForce(){
    Vector3 e = P2->getPosition() - P1->getPosition();
    float l = e.Mag();
    if(l != 0.0)
        e.Normalize();
    
    float v1 = e.Dot(P1->getVelocity());
    float v2 = e.Dot(P2->getVelocity());
    float fsd = -SpringConstant*(RestLength - l) - DampingFactor*(v1 - v2);

    Vector3 f1 = fsd*e;
    Vector3 f2 = -f1;
    
    P1->ApplyForce(f1);
    P2->ApplyForce(f2);
    
}

void SpringDamper::Draw(){
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    
    glColor3f(color.x, color.y, color.z);
    Vector3 pos1 = P1->getPosition();
    Vector3 pos2 = P2->getPosition();
    glVertex3f(pos1.x, pos1.y, pos1.z);
    glVertex3f(pos2.x, pos2.y, pos2.z);
    glColor3f(1.0f, 1.0f, 1.0f); //clear color
    glEnd();
    glEnable(GL_LIGHTING);

}
