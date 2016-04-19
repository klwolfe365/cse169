//
//  Joint.h
//  cse169
//
//  Created by Karen Wolfe on 4/3/16.
//
//

#ifndef Joint_h
#define Joint_h

#include <stdio.h>
#include <list>
#include "matrix34.h"
#include "vector3.h"
#include "token.h"
#include "DOF.h"

class Joint{
public:
    static const bool DEBUG = false;
    Joint();
    ~Joint();
    
    bool Load(Tokenizer &t);
    void Initialize();
    void Update();
    void Draw();
    void AddChild(Joint *j);
    Matrix34* MakeLocalMatrix();
    
    int NumberJoints(int n);
    Joint* GetJoint(int jointNum);
    void Print();
    
    DOF* GetNextDof();
    DOF* GetPrevDof();
    DOF* GetCurrentDof();
    const char* GetName();
    int GetJointNumber();
    int GetCurrentDofNum();
    
private:
    Vector3 Offset;
    Vector3 Boxmin;
    Vector3 Boxmax;
    Vector3 Pose;
    DOF RotXLimit;
    DOF RotYLimit;
    DOF RotZLimit;
    
    Matrix34 W;
    Matrix34 L;
    std::list<DOF *> dofs;
    Joint *parent;
    std::list<Joint *> children;
    
    const char *name;
    int num;
    DOF* currentDof = NULL;
    int dofNum;
//    std::list<DOF *>::iterator dofNum = dofs.begin();
    //List<Joint *> siblings;
    
    void ClampValues();
    
};

#endif /* Joint_h */
