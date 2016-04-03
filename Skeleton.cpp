//
//  Skeleton.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/3/16.
//
//

#include "Skeleton.h"

Skeleton::Skeleton(){}

bool Skeleton::Load(const char *file){
    Tokenizer token;
    token.Open(file);
    token.FindToken("balljoint");
    
    Root = new Joint();
    Root->Load(token);
    
    token.Close();
    return true;
}