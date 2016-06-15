//
//  Vertex.h
//  cse169
//
//  Created by Karen Wolfe on 4/16/16.
//
//

#ifndef Vertex_h
#define Vertex_h

#include <stdio.h>
#include <vector>


#include "vector3.h"

class Vertex{
public:
    static const bool DEBUG = false;
    Vertex();
    ~Vertex();
    
    Vector3 GetPosition();
    void SetPosition(Vector3 position);
    void SetPosition(float x, float y, float z);
    
    Vector3 GetNormal();
    void SetNormal(Vector3 normal);
    void SetNormal(float x, float y, float z);
    
    int numAttachments;
    float skinweights[4];
    int joints[4];
    
private:
    Vector3 Position;
    Vector3 Normal;
};

#endif /* Vertex_h */
