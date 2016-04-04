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