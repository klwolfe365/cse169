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
#include <vector>
#include "matrix34.h"
#include "Joint.h"
class Skeleton {
public:
    static const bool DEBUG = false;

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
    const char* GetFileName() {return filename;}
    
    std::vector<Joint *> GetJoints();
    
private:
    Joint* Root;
    const char *filename;
    
    
    Joint* currentJoint = NULL;
    int currentJointNum;
    int totalJointNum;
    
    std::vector<Joint *> joints;
};

#endif /* Skeleton_h */
