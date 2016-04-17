//
//  Triangle.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/16/16.
//
//

#include "Triangle.h"
Triangle::Triangle(){
    v1 = v2 = v3 = -1;
}
Triangle::~Triangle(){}

void Triangle::SetVertices(int v1, int v2, int v3){
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

void Triangle::SetVertex1(int v){
    v1 = v;
}

void Triangle::SetVertex2(int v){
    v2 = v;
}

void Triangle::SetVertex3(int v){
    v3 = v;
}

int Triangle::GetVertex1(){
    return v1;
}

int Triangle::GetVertex2(){
    return v2;
}

int Triangle::GetVertex3(){
    return v3;
}