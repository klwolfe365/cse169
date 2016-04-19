//
//  Skeleton.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/3/16.
//
//

#include "Skeleton.h"

Skeleton::Skeleton(){}

Skeleton::~Skeleton(){}

bool Skeleton::Load(const char *file){
    filename = file;
    Tokenizer token;
    token.Open(file);
    token.FindToken("balljoint");
    
    Root = new Joint();
    Root->Load(token);
    Root->Initialize();
    
    token.Close();
    NumberJoints();
   
    return true;
}
void Skeleton::Update(Matrix34 &parent){
    Root->Update();
}

void Skeleton::Draw(){
    Root->Draw();
}

void Skeleton::Reset(){
    Load(filename);
}

void Skeleton::NumberJoints(){
    totalJointNum = Root->NumberJoints(0);
}

void Skeleton::PrintJoints(){
    Root->Print();
}

Joint* Skeleton::GetJoint(int jointNum){
    return Root->GetJoint(jointNum);
}

Joint* Skeleton::GetCurrentJoint(){
    if(currentJoint == NULL)
        currentJoint = Root;
    return currentJoint;
}

Joint* Skeleton::GetNextJoint(){
    if(currentJointNum >= totalJointNum){
        currentJointNum = 0;
        currentJoint = Root;
    }
    else
        currentJoint = GetJoint(++currentJointNum);
    return currentJoint;
}

Joint* Skeleton::GetPrevJoint(){
    if(currentJointNum == 0)
        currentJointNum = totalJointNum;
    else
        --currentJointNum;
       
    currentJoint = GetJoint(currentJointNum);
    return currentJoint;
}