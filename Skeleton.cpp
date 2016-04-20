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
    
    currentJointNum = 0;
    currentJoint = joints[0];
   
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
    totalJointNum = Root->NumberJoints(0) + 1;
    joints = std::vector<Joint *>(totalJointNum);
    
    int n = 0;
    while(n < totalJointNum){
        joints[n] = GetJoint(n);
        n++;
    }
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
    
    currentJoint->SetColor(1.0,1.0,1.0);
    if(currentJointNum >= (totalJointNum-1)){
        currentJointNum = 0;
        currentJoint = Root;
    }
    else{
        currentJoint = GetJoint(++currentJointNum);
    }
    currentJoint->SetDOFColor();
    return currentJoint;
}

Joint* Skeleton::GetPrevJoint(){
    
    currentJoint->SetColor(1.0,1.0,1.0);
    if(currentJointNum <= 0){
        currentJointNum = totalJointNum - 1;
    }
    else{
        --currentJointNum;
    }
    
    currentJoint = GetJoint(currentJointNum);
    currentJoint->SetDOFColor();
    return currentJoint;
}

std::vector<Joint *> Skeleton::GetJoints(){
    return joints;
}
