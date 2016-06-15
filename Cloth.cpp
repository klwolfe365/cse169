//
//  Cloth.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/16/16.
//
//

#include "Cloth.h"

Cloth::Cloth(){
    ratio = 0.25;
    elasticity = 0.2;
}
Cloth::Cloth(int w, int h){
    ground = Plane(Vector3(0.0f, -1.7f, 0.0f));
    ratio = 0.25;
    elasticity = 0.2;
    width = w;
    height = h;
    Particles.resize(height);
    for(int i = 0; i < height; i++)
        Particles[i].resize(width);
    initializeCloth();
    initializeTriangles();
    initializeSprings();
    initializeStiffningSprings();
    setFixedRow(0);
    Color = Vector3(1.0, 1.0, 1.0);
    
}
Cloth::~Cloth(){}

void Cloth::initializeCloth(){
    for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            Particle * p = new Particle();
            float x = (c-(width/2.0))*ratio;
            float y = ((height/2.0)-r)*ratio;
//            if(y < ground.GetPoint().y)
//                y = ground.GetPoint().y;
            printf("(%d, %d): %f %f\n", r, c, x, y);
            p->setPosition(Vector3(x, y, 0.0));
            p->setMass(0.5);
            p->setPrevPosition(Vector3(x, y, 0.0f));
            Particles[r][c] = p;
        }
    }
    printf("width/2*ratio %f\n", Particles[0][1]->getPosition().x-Particles[0][0]->getPosition().x);

    if(DEBUG){
        PrintParticles();
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
            ParticleTriangle *t3 = new ParticleTriangle();
            ParticleTriangle *t4 = new ParticleTriangle();
            t1->SetParticles(p0, p1, p2);
            t2->SetParticles(p3, p2, p1);
            t3->SetParticles(p0, p1, p3);
            t4->SetParticles(p0, p3, p2);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        }
    }
    
//    if(DEBUG){
//        for(int i = 0; i < triangles.size(); i++){
//            printf("Triangle %d: ", i);
//            triangles[i]->GetParticle1()->Print();
//            printf("\t");
//            triangles[i]->GetParticle2()->Print();
//            printf("\t");
//            triangles[i]->GetParticle3()->Print();
//        }
//    }
}

void Cloth::initializeSprings(){
    float w = ratio;
    float h = ratio;
    float d = sqrt(w*w + w*w);
    
    printf("%f %f %f\n", w, h, d);
    for(int r = 0; r < height-1; r++){
        for(int c = 0; c < width-1; c++){
            Particle * p0 = Particles[r][c];        //Current
            Particle * p1 = Particles[r][c+1];      //Next
            Particle * p2 = Particles[r+1][c];      //Below
            Particle * p3 = Particles[r+1][c+1];    //Diagonal next
            
            SpringDamper * s0 = new SpringDamper(p0, p1);
            SpringDamper * s1 = new SpringDamper(p0, p2);
            SpringDamper * s2 = new SpringDamper(p0, p3);
            
            s0->setRestLength(w);
            s1->setRestLength(h);
            s2->setRestLength(d);
            
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
            s0->setRestLength(d);
            springs.push_back(s0);
        }
    }
    
    //Last column
    for(int r = 0; r < height-1; r++){
        Particle * p0 = Particles[r][width-1];
        Particle * p1 = Particles[r+1][width-1];    //Border - up/down
        SpringDamper * s0 = new SpringDamper(p0, p1);
        s0->setRestLength(h);
        springs.push_back(s0);
    }
    
    //Last Row
    for(int c = 1; c < width; c++){
        Particle * p0 = Particles[height-1][c];
        Particle * p1 = Particles[height-1][c-1];   //Border - right/left
        SpringDamper * s0 = new SpringDamper(p0, p1);
        s0->setRestLength(w);
        springs.push_back(s0);
    }
}

void Cloth::initializeStiffningSprings(){
    float w = 1.1*2*ratio;
    float h = 1.1*2*ratio;
    float d = 1.1*sqrt(w*w + w*w);
    
    for(int r = 0; r < height - 2; r+=2){
        for(int c = 0; c < width - 2; c+=2){
            Particle * p0 = Particles[r][c];        //Current
            Particle * p1 = Particles[r][c+2];      //Next
            Particle * p2 = Particles[r+2][c];      //Below
            Particle * p3 = Particles[r+2][c+2];    //Diagonal next
            SpringDamper * s0 = new SpringDamper(p0, p1, LARGE_SPRING_CONST, LARGE_DAMP_CONST, w);
            s0->color.Set(1.0, 0.0, 0.0);
            SpringDamper * s1 = new SpringDamper(p0, p2,LARGE_SPRING_CONST, LARGE_DAMP_CONST, h);
            s1->color.Set(1.0, 0.0, 0.0);
            SpringDamper * s2 = new SpringDamper(p0, p3,LARGE_SPRING_CONST, LARGE_DAMP_CONST, d);
            s2->color.Set(1.0, 0.0, 0.0);
            stiffningSprings.push_back(s0);
            stiffningSprings.push_back(s1);
            stiffningSprings.push_back(s2);
        }
    }
    for(int r = 0; r < height-2; r+=2){
        for(int c = 2; c < width; c+=2){
            Particle * p0 = Particles[r][c];
            Particle * p1 = Particles[r+2][c-2];    //Diagonal prev
            SpringDamper * s0 = new SpringDamper(p0, p1,LARGE_SPRING_CONST, LARGE_DAMP_CONST, d);
            s0->color.Set(1.0, 0.0, 0.0);
            stiffningSprings.push_back(s0);
        }
    }
    
    //Last Column
    for(int r = 0; r < height-2; r+=2){
        Particle * p0 = Particles[r][width-2];
        Particle * p1 = Particles[r+2][width-2];    //Border - up/down
        SpringDamper * s0 = new SpringDamper(p0, p1,LARGE_SPRING_CONST, LARGE_DAMP_CONST, h);
        s0->color.Set(1.0, 0.0, 0.0);
        stiffningSprings.push_back(s0);
    }
    
    //Last Row
    for(int c = 2; c < width; c+=2){
        Particle * p0 = Particles[height-2][c];
        Particle * p1 = Particles[height-2][c-2];   //Border - right/left
        SpringDamper * s0 = new SpringDamper(p0, p1,LARGE_SPRING_CONST, LARGE_DAMP_CONST, w);
        s0->color.Set(1.0, 0.0, 0.0);
        stiffningSprings.push_back(s0);
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

void Cloth::fixCorners(){
    Particles[0][0]->setFixed(true);
    Particles[0][width-1]->setFixed(true);
    Particles[height-1][0]->setFixed(true);
    Particles[height-1][width-1]->setFixed(true);
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
    
    //Springs
    for(int i = 0; i < springs.size(); i++){
        springs[i]->ComputeForce();
    }

    
    //AeroDynamic Force
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i]->ComputeForce(vAir);
    }
    
    //Integrate over particles
    for(int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Particles[r][c]->Update(0.005);
        }
    }
    
    for(int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Segment s;
            Intersection inter;
            s.A = Particles[r][c]->getPrevPosition();
            s.B = Particles[r][c]->getPosition();

            //check for collision with ground
            if (ground.TestSegment(s, inter)) {
                Vector3 v = Particles[r][c]->getVelocity();
                Vector3 p = Particles[r][c]->getPosition();
                p.y = 2.0*ground.GetPoint().y - p.y;
                Particles[r][c]->setVelocity(-v);
                Particles[r][c]->setPosition(p);
            }
            
            Particles[r][c]->setPrevPosition(Particles[r][c]->getPosition());
        }
    }
    
    
    //Set up normals
    for(int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Particles[r][c]->setNormal(Vector3(0.0f, 0.0f, 0.0f));
        }
    }
    
    for(int i = 0; i < triangles.size(); i++){
        triangles[i]->calculateNormal();
        Vector3 n = triangles[i]->getNormal();
        Particle* p0 = triangles[i]->GetParticle(0);
        Particle* p1 = triangles[i]->GetParticle(1);
        Particle* p2 = triangles[i]->GetParticle(2);
        p0->setNormal(p0->getNormal()+ n);
        p1->setNormal(p1->getNormal()+ n);
        p2->setNormal(p2->getNormal()+ n);
    }
    
    for(int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Vector3 n = Particles[r][c]->getNormal();
            Particles[r][c]->setNormal(n.Normalize());
        }
    }
    
    
}

void Cloth::Draw(){    
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor3f(Color.x, Color.y, Color.z);
    for(int i = 0; i < triangles.size(); i++){
        Vector3 p0 = triangles[i]->GetParticle(0)->getPosition();
        Vector3 p1 = triangles[i]->GetParticle(1)->getPosition();
        Vector3 p2 = triangles[i]->GetParticle(2)->getPosition();
        Vector3 n0 = triangles[i]->GetParticle(0)->getNormal();
        Vector3 n1 = triangles[i]->GetParticle(1)->getNormal();
        Vector3 n2 = triangles[i]->GetParticle(2)->getNormal();
        Vector3 n = (n0+n1+n2)/3.0;
        
        glNormal3f(n.x, n.y, n.z);
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    }
    glEnd();
    glPopMatrix();
    
    if(DEBUG){
        for(int i = 0; i < springs.size(); i++)
            springs[i]->Draw();
    }

    ground.Draw();
}

void Cloth::setColor(float r, float g, float b){
    Color.x = r;
    Color.y = g;
    Color.z = b;
}

void Cloth::Drag(Vector3 d){
    for(int r = 0; r < height; r ++){
        for(int c = 0; c < width; c++){
            if(Particles[r][c]->isFixed()){
                Vector3 prev = Particles[r][c]->getPosition();
                Particles[r][c]->setPrevPosition(prev);
                Particles[r][c]->setPosition(prev+d);
            }
        }
    }
}

void Cloth::PrintParticles(){
    for(int r = 0; r < height; r ++){
        for(int c = 0; c < width; c++){
            printf("(%d, %d): ", r, c);
            Particles[r][c]->Print();
        }
    }
}