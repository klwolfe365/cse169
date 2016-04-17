//
//  Skin.h
//  cse169
//
//  Created by Karen Wolfe on 4/16/16.
//
//

#ifndef Skin_h
#define Skin_h

#include <stdio.h>

#include "Vertex.h"
#include "Triangle.h"
#include "matrix34.h"
#include "token.h"

class Skin{
public:
    static const bool DEBUG = true;
    Skin();
    ~Skin();
    
    bool Load(const char* file);
    void PrintSkin();
private:
    int numVerts;
    int numTriangles;
    int numJoints;
    const char* filename;
    Vertex* vertices;
    Triangle* triangles;
    Matrix34* bindings;
    
};
#endif /* Skin_h */
