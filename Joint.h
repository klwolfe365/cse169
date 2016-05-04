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
#include <vector>

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
    
    Matrix34 GetLocalMatrix();
    Matrix34 GetWorldMatrix();
    
    int NumberJoints(int n);
    Joint* GetJoint(int jointNum);
    void Print();
    
    DOF* GetCurrentDof();
    DOF* GetNextDof();
    DOF* GetPrevDof();
    DOF* GetDof(int dofNum);
    const char* GetName();
    int GetJointNumber();
    int GetCurrentDofNum();
    
    
    void SetOffset(float x, float y, float z) {Offset.x = x; Offset.y = y; Offset.z = z;}
    void SetColor(float r, float g, float b) {color.x = r; color.y = g; color.z = b;}
    
    void SetDOFColor();
    
    Vector3 GetOffset()         {return Offset;}
    Vector3 GetRotation()       {return Vector3(RotXLimit.GetValue(), RotYLimit.GetValue(), RotZLimit.GetValue());}
    
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
    std::vector<DOF *> dofs;
    Joint *parent;
    std::list<Joint *> children;
    
    const char *name;
    int num;
    DOF* currentDof = NULL;
    int dofNum;
    
    Vector3 color;
//    std::list<DOF *>::iterator dofNum = dofs.begin();
    //List<Joint *> siblings;
    
    void ClampValues();
    
};

#endif /* Joint_h */
