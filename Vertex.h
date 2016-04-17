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

#include "vector3.h"

class Vertex{
public:
    static const bool DEBUG = false;
    Vertex();
    ~Vertex();
    
    Vector3 GetPosition();
    void SetPosition(Vector3 position);
    Vector3 GetNormal();
    void SetNormal(Vector3 normal);
private:
    Vector3 Position;
    Vector3 Normal;
};

#endif /* Vertex_h */
