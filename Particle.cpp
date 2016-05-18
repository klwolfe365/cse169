//
//  Particle.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#include "Particle.h"
Particle::Particle(){
    mass = 1.0f;
    Position.Zero();
    Velocity.Zero();
    Force.Zero();
    fixed = false;
    Color = Vector3(1.0, 1.0, 1.0);
}

Particle::~Particle(){}

void Particle::Update(float deltaTime){
    if(fixed)
        return;
    Vector3 accel = (1.0/mass) * Force;
    
    Velocity += accel*deltaTime;
    Position += Velocity*deltaTime;
    
    Force.Zero();
}

void Particle::Draw(){
    glPointSize(1.5);
    glBegin(GL_POINTS);
    glColor3f(Color.x, Color.y, Color.z);
    glVertex3f(Position.x, Position.y, Position.z);
    glColor3f(1.0f, 1.0f, 1.0f); //clear color
    glEnd();
}

void Particle::Reset(){
    Force.Zero();
    Velocity.Zero();
}

void Particle::UpdatePosition(Vector3 pos){
    Position.x += pos.x;
    Position.y += pos.y;
    Position.z += pos.z;
}

void Particle::Print(){
    printf("Position %f %f %f\n", Position.x, Position.y, Position.z);
    printf("\t\tVelocity %f %f %f\n", Velocity.x, Velocity.y, Velocity.z);
    printf("\t\tForce %f %f %f\n", Force.x, Force.y, Force.z);
    printf("\t\tMass: %f\tFixed: %s\n", mass, fixed ? "true":"false");
}