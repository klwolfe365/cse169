//
//  Cloth.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#include "Cloth.h"

Cloth::Cloth(){}
Cloth::Cloth(int w, int h){
    width = w;
    height = h;
    Particles.resize(height);
    for(int i = 0; i < height; i++)
        Particles[i].resize(width);
    initializeCloth();
    initializeTriangles();
    initializeSprings();
    setFixedRow(0);
    Color = Vector3(0.0, 1.0, 1.0);

    
    //TODO init cloth/spring/triangle arrays
}
Cloth::~Cloth(){}

void Cloth::initializeCloth(){
    for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            Particle * p = new Particle();
            p->setPosition(Vector3(c, 0-r, 0.0));
            Particles[r][c] = new Particle();
        }
    }
}

void Cloth::initializeTriangles(){
    for(int r = 0; r < height-1; r++){
        for(int c = 0; c < width-1; c++){
            Particle * p0 = Particles[r][c];        //Current
            Particle * p1 = Particles[r][c+1];      //Next
            Particle * p2 = Particles[r+1][c];      //Below
            Particle * p3 = Particles[r+1][c+1];    //Diagonal
            ParticleTriangle *t1 = new ParticleTriangle();
            ParticleTriangle *t2 = new ParticleTriangle();
            t1->SetParticles(p0, p1, p2);
            t2->SetParticles(p1, p2, p3);
            triangles.push_back(t1);
            triangles.push_back(t2);
        }
    }
}

void Cloth::initializeSprings(){
    
    for(int r = 0; r < height-1; r++){
        for(int c = 0; c < width-1; c++){
            Particle * p0 = Particles[r][c];        //Current
            Particle * p1 = Particles[r][c+1];      //Next
            Particle * p2 = Particles[r+1][c];      //Below
            Particle * p3 = Particles[r+1][c+1];    //Diagonal next
            SpringDamper * s0 = new SpringDamper(p0, p1);
            SpringDamper * s1 = new SpringDamper(p0, p2);
            SpringDamper * s2 = new SpringDamper(p0, p3);
            springs.push_back(s0);
            springs.push_back(s1);
            springs.push_back(s2);
            
        }
    }
    
    for(int r = 0; r < height-1; r++){
        for(int c = 1; c < width; c++){
            Particle * p0 = Particles[r][c];
            Particle * p1 = Particles[r+1][c-1];    //Diagonal prev
            SpringDamper * s0 = new SpringDamper(p0, p1);
            springs.push_back(s0);
        }
    }
    
    //Last column
    for(int r = 0; r < height-1; r++){
        Particle * p0 = Particles[r][width-1];
        Particle * p1 = Particles[r+1][width-1];    //Border - up/down
        SpringDamper * s0 = new SpringDamper(p0, p1);
        springs.push_back(s0);
    }
    
    //Last Row
    for(int c = 1; c < width; c++){
        Particle * p0 = Particles[height-1][c];
        Particle * p1 = Particles[height-1][c-1];   //Border - right/left
        SpringDamper * s0 = new SpringDamper(p0, p1);
        springs.push_back(s0);
    }
}

void Cloth::setFixedRow(int r){
    for(int c = 0; c < width; c++){
        Particles[r][c]->setFixed(true);
    }
}

void Cloth::setFixedColumn(int c){
    for(int r = 0; r < height; r++){
        Particles[r][c]->setFixed(true);
    }
}

void Cloth::Update(Vector3 vAir){
    Vector3 g(0, -9.8, 0);
    
    //Gravity
    for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            Vector3 f = g * Particles[r][c]->getMass();
            Particles[r][c]->ApplyForce(f);
        }
    }
}

void Cloth::Draw(){
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    GLfloat c[] = {Color.x, Color.y, Color.z, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
    for(int i = 0; i < triangles.size(); i++){
        Vector3 p0 = triangles[i]->GetParticle(0)->getPosition();
        Vector3 p1 = triangles[i]->GetParticle(1)->getPosition();
        Vector3 p2 = triangles[i]->GetParticle(2)->getPosition();
        Vector3 n = triangles[i]->getNormal();
        
        glNormal3f(n.x, n.y, n.z);
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    }
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glEnd();
    
}

void Cloth::setColor(float r, float g, float b){
    Color.x = r;
    Color.y = g;
    Color.z = b;
}