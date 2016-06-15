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
}

void Keyframe::SetCoefficients(Keyframe* k0, Keyframe* k1){
    float t0 = k0->getTime();
    float t1 = k1->getTime();
    float t = t1-t0;
    float p0 = k0->getValue();
    float p1 = k1->getValue();
    float v0 = k0->getTanOut();
    float v1 = k1->getTanIn();
    
    a = (2*p0) - (2*p1) + (t*v0) + (t*v1);
    b = (-3*p0) + (3*p1) + (-2*(t*v0)) - (t*v1);
    c = t*v0;
    d = p0;
}

float Keyframe::CalculateTangent(Keyframe * prev, Keyframe * next){
    float p1 = next->getValue();
    float p0 = prev->getValue();
    float t1 = next->getTime();
    float t0 = prev->getTime();
    
    return (p1-p0)/(t1-t0);
}