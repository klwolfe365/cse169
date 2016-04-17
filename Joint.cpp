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
}

bool Joint::Load(Tokenizer &t){
    char name[256];
    t.GetToken(name);
    this->name = name;
    
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
    
//    Matrix34 rotations = Matrix34();
//    rotations.Identity();
//    //Initialize any rotations
//    rotations.MakeRotateX(RotXLimit.GetValue());
//    L.Dot(rotations, L);
//    rotations.MakeRotateY(RotYLimit.GetValue());
//    L.Dot(rotations, L);
//    rotations.MakeRotateZ(RotZLimit.GetValue());
//    L.Dot(rotations, L);
//    //Initialize any translations
//    rotations.MakeTranslate(Offset);
//    L.Dot(rotations, L);
    
    for(Joint *j : children){
        j->Initialize();
    }


}

void Joint::Update(){
    //Compute LocalMatrix
//    L->MakeTranslate(*Offset);
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
    drawWireBox(Boxmin.x, Boxmin.y, Boxmin.z, Boxmax.x, Boxmax.y, Boxmax.z);
    
    for(Joint *j : children){
        j->Draw();
    }
}

void Joint::AddChild(Joint* j){
    j->parent = this;
    children.push_back(j);
    //update siblings?
}

Matrix34* Joint::MakeLocalMatrix(){

    return new Matrix34();
}

void Joint::ClampValues(){
    if(Pose.x > RotXLimit.GetMax()){
        RotXLimit.SetValue(RotXLimit.GetMax());
    } else if(Pose.x < RotXLimit.GetMin()){
        RotXLimit.SetValue(RotXLimit.GetMin());
    }
    
    if(Pose.y > RotYLimit.GetMax()){
        RotYLimit.SetValue(RotYLimit.GetMax());
    } else if(Pose.y < RotYLimit.GetMin()){
        RotYLimit.SetValue(RotYLimit.GetMin());
    }
    
    if(Pose.z > RotZLimit.GetMax()){
        RotZLimit.SetValue(RotZLimit.GetMax());
    } else if(Pose.z < RotZLimit.GetMin()){
        RotZLimit.SetValue(RotZLimit.GetMin());
    }
    
    if(DEBUG)
        printf("Rotation Values: %f, %f, %f\n", RotXLimit.GetValue(), RotYLimit.GetValue(), RotZLimit.GetValue());
}