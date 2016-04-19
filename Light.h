//
//  Light.h
//  cse169
//
//  Created by Karen Wolfe on 4/18/16.
//
//

#ifndef Light_h
#define Light_h

#include <stdio.h>

#include "vector3.h"
#include "matrix34.h"

class Light{
public:
    Light();
    ~Light();
    
    void Update(Matrix34);
    void Draw();
    void Reset();
    
    Vector3 GetPosition();
    void SetPosition(Vector3 pos);

    Vector3 GetDirection();
    void SetDirection(Vector3 dir);
    
    Vector3 GetColor();
    void SetColor(Vector3 c);
    
private:
    Vector3 Position;
    Vector3 Direction;
    Vector3 Color;
};
#endif /* Light_h */
