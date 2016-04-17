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
#include <vector>

#include "Vertex.h"
#include "Triangle.h"
#include "matrix34.h"
#include "token.h"

class Skin{
public:
    static const bool DEBUG = false;
    Skin();
    ~Skin();
    
    bool Load(const char* file);
    void PrintSkin();
private:
    int numVerts;
    int numTriangles;
    int numJoints;
    const char* filename;
    std::vector<Vertex *> vertices;
    std::vector<Triangle *> triangles;
    std::vector<Matrix34 *> bindings;
    
};
#endif /* Skin_h */
