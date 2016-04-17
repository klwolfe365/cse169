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
#include "Skin.h"
class Skeleton {
public:
    static const bool DEBUG = false;

    Skeleton();
    ~Skeleton();
    
    bool Load(const char *file);
    void Update(Matrix34 &parent);
    void Draw();
    void Reset();
    
private:
    Joint* Root;
    Skin* skin;
    const char *filename;
};

#endif /* Skeleton_h */
