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
    static const bool DEBUG = true;
    Joint();
    ~Joint();
    
    bool Load(Tokenizer &t);
    void Initialize();
    void Update();
    void Draw();
    void AddChild(Joint *j);
    Matrix34* MakeLocalMatrix();
    
private:
    Vector3 *Offset;
    Vector3 *Boxmin;
    Vector3 *Boxmax;
    Vector3 *Pose;
    DOF *RotXLimit;
    DOF *RotYLimit;
    DOF *RotZLimit;
    
    Matrix34 *W;
    Matrix34 *L;
    std::list<DOF *> dofs;
    Joint *parent;
    std::list<Joint *> children;
    //List<Joint *> siblings;
    
    void ClampValues();
    
};

#endif /* Joint_h */
