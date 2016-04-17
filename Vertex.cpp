//
//  Vertex.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/16/16.
//
//

#include "Vertex.h"
Vertex::Vertex(){}
Vertex::~Vertex(){}

Vector3 Vertex::GetPosition(){
    return Position;
}

void Vertex::SetPosition(Vector3 position){
    Position = position;
}

Vector3 Vertex::GetNormal(){
    return Normal;
}

void Vertex::SetNormal(Vector3 normal){
    Normal = normal;
}