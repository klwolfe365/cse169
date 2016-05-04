//
//  Keyframe.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#include "Keyframe.h"

Keyframe::Keyframe(){}

Keyframe::~Keyframe(){}

bool Keyframe::isValidTangent(const char* tangentType){
    if((strcmp(tangentType, "flat") == 0) || (strcmp(tangentType, "linear") == 0) || (strcmp(tangentType, "smooth") == 0))
        return true;
    return false;
}

float setTangents(const char* tangentType){
    if(strcmp(tangentType, "flat") == 0)
        return 0.0f;
    else if(strcmp(tangentType, "linear") == 0) return 0.0f;
    
    return 0.0f;
//        return 
}

void Keyframe::setCoefficients(){
    
}

float Keyframe::CalculateTangent(Keyframe * prev, Keyframe * next){
    float p1 = next->getValue();
    float p0 = prev->getValue();
    float t1 = next->getTime();
    float t0 = prev->getTime();
    
    return (p1-p0)/(t1-t0);
}