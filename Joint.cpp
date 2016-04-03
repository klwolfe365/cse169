//
//  Joint.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/3/16.
//
//

#include "Joint.h"
Joint::Joint(){}

bool Joint::Load(Tokenizer &t){
    t.FindToken("{");
    while(1){
        char temp[256];
        t.GetToken(temp);
        if(strcmp(temp, "offset")==0){
            Offset.x = t.GetFloat();
            Offset.y = t.GetFloat();
            Offset.z = t.GetFloat();
        }
        else if(strcmp(temp, "boxmin")){
            Boxmin.x = t.GetFloat();
            Boxmin.y = t.GetFloat();
            Boxmin.z = t.GetFloat();
        }
        else if(strcmp(temp, "boxmax")){
            Boxmax.x = t.GetFloat();
            Boxmax.y = t.GetFloat();
            Boxmax.z = t.GetFloat();
        }
        else if(strcmp(temp, "rotxlimit")){
            RotXLimit.SetMin(t.GetFloat());
            RotXLimit.SetMax(t.GetFloat());
        }
        else if(strcmp(temp, "rotylimit")){
            RotYLimit.SetMin(t.GetFloat());
            RotYLimit.SetMax(t.GetFloat());
        }
        else if(strcmp(temp, "rotzlimit")){
            RotZLimit.SetMin(t.GetFloat());
            RotZLimit.SetMax(t.GetFloat());
        }
        else if(strcmp(temp, "pose")){
            Pose.x = t.GetFloat();
            Pose.y = t.GetFloat();
            Pose.z = t.GetFloat();
        }
        else if(strcmp(temp,"balljoint")==0){
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

void Joint::Update(Matrix34 &parent){}

void Joint::Draw(){}

void Joint::AddChild(Joint* j){
    j->parent = this;
    children.push_back(j);
    //update siblings?
}

Matrix34* Joint::MakeLocalMatrix(){

    return new Matrix34();
}