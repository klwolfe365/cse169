//
//  Triangle.h
//  cse169
//
//  Created by Karen Wolfe on 4/16/16.
//
//

#ifndef Triangle_h
#define Triangle_h

#include <stdio.h>

#include "Vertex.h"

class Triangle{
public:
    static const bool DEBUG = false;
    Triangle();
    ~Triangle();
    
    void SetVertices(int v1, int v2, int v3);
    void SetVertex1(int v);
    void SetVertex2(int v);
    void SetVertex3(int v);
    int GetVertex1();
    int GetVertex2();
    int GetVertex3();
private:
    //Vertex v1, v2, v3;
    int v1, v2, v3;
};
#endif /* Triangle_h */
