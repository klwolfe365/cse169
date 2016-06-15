//
//  Plane.h
//  cse169
//
//  Created by Karen Wolfe on 5/18/16.
//
//

#ifndef Plane_h
#define Plane_h

#include <stdio.h>
#include "vector3.h"
#include "Intersection.h"
#include "Segment.h"

class Plane{
public:
    Plane();
    Plane(Vector3 p);
    Plane(Vector3 p, Vector3 n);
    ~Plane();
    
    bool TestSegment(const Segment &s, Intersection &i);
    
    void SetPoint(Vector3 p);
    void SetNormal(Vector3 n);
    void setK(float k)                  { kVal = k; }
    void setDamping(float d)            { dampingVal = d; }
    
    Vector3 GetNormal()                 { return normal; }
    Vector3 GetPoint()                  { return point; }
    float k()                           { return kVal; }
    float damping()                     { return dampingVal; }
    void Draw();
    
    Vector3 color;
    
private:
    Vector3 point;
    Vector3 normal;
    float dist;
    float kVal;
    float dampingVal;
    
    float length = 0.5;
};
#endif /* Plane_h */
