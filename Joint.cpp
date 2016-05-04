//
//  Joint.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/3/16.
//
//

#include "Joint.h"
Joint::Joint(){
    parent = NULL;
    W = Matrix34();
    L = Matrix34();
    Offset = Vector3(0,0,0);
    Boxmin = Vector3(-0.1,-0.1,-0.1);
    Boxmax = Vector3(0.1,0.1,0.1);
    Pose = Vector3(0,0,0);
    RotXLimit = DOF();
    RotYLimit = DOF();
    RotZLimit = DOF();
    name = "NULL";
    num = -1;
    color = Vector3(1.0,1.0,1.0);
    dofNum = 0;
    dofs.push_back(&RotXLimit);
    dofs.push_back(&RotYLimit);
    dofs.push_back(&RotZLimit);
}

bool Joint::Load(Tokenizer &t){
    char jointname[256];
    
    t.GetToken(jointname);
    name = strdup(jointname);
    
    t.FindToken("{");
    while(1){
        char temp[256];
        t.GetToken(temp);
        if(strcmp(temp, "offset")==0){
            
            Offset.x = t.GetFloat();
            Offset.y = t.GetFloat();
            Offset.z = t.GetFloat();
            if(DEBUG)
                printf("Offset: %f %f %f\n", Offset.x, Offset.y, Offset.z);
        }
        else if(strcmp(temp, "boxmin")==0){
            Boxmin.x = t.GetFloat();
            Boxmin.y = t.GetFloat();
            Boxmin.z = t.GetFloat();
            if(DEBUG){
                printf("Boxmin: %f %f %f\n", Boxmin.x, Boxmin.y, Boxmin.z);
            }
        }
        else if(strcmp(temp, "boxmax")==0){
            Boxmax.x = t.GetFloat();
            Boxmax.y = t.GetFloat();
            Boxmax.z = t.GetFloat();
            if(DEBUG){
                printf("Boxmax: %f %f %f\n", Boxmax.x, Boxmax.y, Boxmax.z);
            }
        }
        else if(strcmp(temp, "rotxlimit")==0){
            RotXLimit.SetMin(t.GetFloat());
            RotXLimit.SetMax(t.GetFloat());
            if(DEBUG){
                printf("RotXLimit: %f %f\n", RotXLimit.GetMin(), RotXLimit.GetMax());
            }
        }
        else if(strcmp(temp, "rotylimit")==0){
            RotYLimit.SetMin(t.GetFloat());
            RotYLimit.SetMax(t.GetFloat());
            if(DEBUG){
                printf("RotXLimit: %f %f\n", RotYLimit.GetMin(), RotYLimit.GetMax());
            }
        }
        else if(strcmp(temp, "rotzlimit")==0){
            RotZLimit.SetMin(t.GetFloat());
            RotZLimit.SetMax(t.GetFloat());
            if(DEBUG){
                printf("RotZLimit: %f %f\n", RotZLimit.GetMin(), RotZLimit.GetMax());
            }
        }
        else if(strcmp(temp, "pose")==0){
            Pose.x = t.GetFloat();
            Pose.y = t.GetFloat();
            Pose.z = t.GetFloat();
            if(DEBUG){
                printf("Pose: %f %f %f\n", Pose.x, Pose.y, Pose.z);
            }
        }
        else if(strcmp(temp,"balljoint")==0){
            if(DEBUG){
                printf("--------------------New Balljoint--------------------\n");
            }
            Joint *j = new Joint();
            j->Load(t);
            AddChild(j);
        }
        else if(strcmp(temp, "}")==0)
            return true;
        
        else t.SkipLine(); //unrecognized token
    }
    return false;
}

void Joint::Initialize(){
    
    RotXLimit.SetValue(Pose.x);
    RotYLimit.SetValue(Pose.y);
    RotZLimit.SetValue(Pose.z);
    ClampValues();
    
    for(Joint *j : children){
        j->Initialize();
    }


}

void Joint::Update(){
    ClampValues();
    L = Matrix34();
    Matrix34 rotations = Matrix34();
    rotations.Identity();
    //Initialize any rotations
    rotations.MakeRotateX(RotXLimit.GetValue());
    L.Dot(rotations, L);
    rotations.MakeRotateY(RotYLimit.GetValue());
    L.Dot(rotations, L);
    rotations.MakeRotateZ(RotZLimit.GetValue());
    L.Dot(rotations, L);
    //Initialize any translations
    rotations.MakeTranslate(Offset);
    L.Dot(rotations, L);


    
    //Compute WorldMatrix - base of parent for all joints except Root
    if(parent != NULL)
        W.Dot(parent->W, L);
    else
        W.Dot(Matrix34(), L);

    for(Joint *j : children){
        j->Update();
    }
}

void Joint::Draw(){
    glLoadMatrixf(W);
    drawWireBoxColored(Boxmin.x, Boxmin.y, Boxmin.z, Boxmax.x, Boxmax.y, Boxmax.z, color.x, color.y, color.z);
    
    for(Joint *j : children){
        j->Draw();
    }
}

void Joint::AddChild(Joint* j){
    j->parent = this;
    children.push_back(j);
    //update siblings?
}

Matrix34 Joint::GetLocalMatrix(){
    return L;
}

Matrix34 Joint::GetWorldMatrix(){
    return W;
}

int Joint::NumberJoints(int n){
    this->num = n;
    for(Joint *j : children){
        n = j->NumberJoints(++n);
    }
    return n;
}

Joint* Joint::GetJoint(int jointNum){
    Joint* retVal = NULL;
    if(jointNum == num)
        return this;
    else{
        for(Joint *j : children){
            retVal = j->GetJoint(jointNum);
            if(retVal != NULL)
                return retVal;
        }
    }
    return retVal;
}

void Joint::Print(){
    printf("Name: (%d)%s\n", num, name);
    for(Joint *j: children)
        j->Print();
}


DOF* Joint::GetCurrentDof(){
    if(currentDof == NULL){
        currentDof = dofs[0];
    }
    return currentDof;
    
}

DOF* Joint::GetNextDof(){
    
    dofNum = (++dofNum)%3;
    currentDof = dofs[dofNum];
    if(dofNum == 0){
//        currentDof = &RotXLimit;
        color.x = 1.0;
        color.y = 0.0;
        color.z = 0.0;
//        color = Vector3(1.0, 0.0, 0.0);
    }
    else if(dofNum == 1){
//        currentDof = &RotYLimit;
        color.x = 0.0;
        color.y = 1.0;
        color.z = 0.0;
//        color = Vector3(0.0, 1.0, 0.0);
    }
    else{
//        currentDof = &RotZLimit;
        color.x = 0.0;
        color.y = 0.0;
        color.z = 1.0;
//        color = Vector3(0.0, 0.0, 1.0);
    }
    
    return currentDof;
}

DOF* Joint::GetPrevDof(){
    dofNum = (--dofNum)%3;
    if(dofNum < 0)
        dofNum = 2;
    currentDof = dofs[dofNum];
    if(dofNum == 0){
//        currentDof = &RotXLimit;
        color.x = 1.0;
        color.y = 0.0;
        color.z = 0.0;
    }
    else if(dofNum == 1){
//        currentDof = &RotYLimit;
        color.x = 0.0;
        color.y = 1.0;
        color.z = 0.0;
    }
    else{
//        currentDof = &RotZLimit;
        color.x = 0.0;
        color.y = 0.0;
        color.z = 1.0;
    }
    
    return currentDof;
}

DOF* Joint::GetDof(int dofNum){
    if(dofNum < 0 || dofNum > dofs.size())
        return NULL;
    return dofs[dofNum];
}

const char* Joint::GetName(){
    return name;
}

int Joint::GetJointNumber(){
    return num;
}

int Joint::GetCurrentDofNum(){
    return dofNum;
}

void Joint::ClampValues(){
    if(RotXLimit.GetValue() > RotXLimit.GetMax()){
        RotXLimit.SetValue(RotXLimit.GetMax());
    } else if(RotXLimit.GetValue() < RotXLimit.GetMin()){
        RotXLimit.SetValue(RotXLimit.GetMin());
    }
    
    if(RotYLimit.GetValue() > RotYLimit.GetMax()){
        RotYLimit.SetValue(RotYLimit.GetMax());
    } else if(RotYLimit.GetValue() < RotYLimit.GetMin()){
        RotYLimit.SetValue(RotYLimit.GetMin());
    }
    
    if(RotZLimit.GetValue() > RotZLimit.GetMax()){
        RotZLimit.SetValue(RotZLimit.GetMax());
    } else if(RotZLimit.GetValue() < RotZLimit.GetMin()){
        RotZLimit.SetValue(RotZLimit.GetMin());
    }
    
    if(DEBUG)
        printf("Rotation Values: %f, %f, %f\n", RotXLimit.GetValue(), RotYLimit.GetValue(), RotZLimit.GetValue());
}

void Joint::SetDOFColor(){
    if(dofNum <= 0){
        color.x = 1.0;
        color.y = 0.0;
        color.z = 0.0;
    }
    else if(dofNum == 1){
        color.x = 0.0;
        color.y = 1.0;
        color.z = 0.0;
    }
    else{
        color.x = 0.0;
        color.y = 0.0;
        color.z = 1.0;
    }
}

