//
//  Light.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/18/16.
//
//

#include "Light.h"

Light::Light(){
    Position = Vector3();
    Direction = Vector3();
    Color = Vector3();
}

Light::~Light(){}

Vector3 Light::GetPosition(){
    return Position;
}
void Light::SetPosition(Vector3 pos){
    Position = pos;
}

Vector3 Light::GetDirection(){
    return Direction;
}

void Light::SetDirection(Vector3 dir){
    Direction = dir;
}

Vector3 Light::GetColor(){
    return Color;
}

void Light::SetColor(Vector3 c){
    Color = c;
}