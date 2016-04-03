//
//  Skeleton.h
//  cse169
//
//  Created by Karen Wolfe on 4/3/16.
//
//

#ifndef Skeleton_h
#define Skeleton_h

#include <stdio.h>
#include "matrix34.h"
#include "Joint.h"
class Skeleton {
public:
    Skeleton();
    ~Skeleton();
    
    bool Load(const char *file);
    void Update(Matrix34 &parent);
    void Draw();
    
private:
    Joint* Root;
};

#endif /* Skeleton_h */
