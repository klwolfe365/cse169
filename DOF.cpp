//
//  DOF.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/3/16.
//
//

#include "DOF.h"

DOF::DOF(){
    min = -100000;
    max = 100000;
    value = 0;
}
DOF::DOF(float min, float max, float value){
    this->min = min;
    this->max = max;
    this->value = value;
}
DOF::~DOF(){}