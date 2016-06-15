//
//  Plane.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/18/16.
//
//

#include "Plane.h"
Plane::Plane(){
    point = Vector3::ORIGIN;
    normal = Vector3::YAXIS;
}

Plane::Plane(Vector3 p){
    point = p;
    normal = Vector3::YAXIS;
    dist = normal.Dot(point);
}

Plane::Plane(Vector3 p, Vector3 n){
    point = p;
    normal = n;
    dist = normal.Dot(point);
}

Plane::~Plane(){}

bool Plane::TestSegment(const Segment &s, Intersection &i) {    
    Vector3 v = s.B - point;
    
    float l = v.Dot(normal);
    
    //behind the plane
    if (l < 0) {
        Vector3 dir = s.B - s.A;
        dir.Normalize();
        float dn = dir.Dot(normal);
        float t = (dist - s.A.Dot(normal)) / dn;
        Vector3 x = s.A + (t * dir);
        
        i.Position.Set(x.x, x.y, x.z);
        i.Normal = v;
        return true;
    }
    
    return false;
}

void Plane::Draw(){
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(point.x, point.y, point.z);
    double angle1 = asin(normal.x) / (2*M_PI) * 360.0;
    double angle2 = asin(normal.y) / (2*M_PI) * 360.0;
    glRotatef(-angle1, 0, 1, 0);
    glRotatef(-angle2, 1, 0, 0);
    glTranslated(0, 0, length/2.0);
    glScalef(20, 20, 1);
    glutSolidCube(length);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}