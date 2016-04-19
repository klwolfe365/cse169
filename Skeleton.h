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
    static const bool DEBUG = true;

    Skeleton();
    ~Skeleton();
    
    bool Load(const char *file);
    void Update(Matrix34 &parent);
    void Draw();
    void Reset();
    
    void NumberJoints();
    void PrintJoints();
    Joint* GetJoint(int jointNum);
    Joint* GetCurrentJoint();
    Joint* GetNextJoint();
    Joint* GetPrevJoint();
    
private:
    Joint* Root;
    Skin* skin;
    const char *filename;
    
    
    Joint* currentJoint = NULL;
    int currentJointNum;
    int totalJointNum;
};

#endif /* Skeleton_h */
