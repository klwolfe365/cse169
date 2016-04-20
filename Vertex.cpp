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

void Vertex::SetPosition(float x, float y, float z){
    Position.x = x;
    Position.y = y;
    Position.z = z;
}

Vector3 Vertex::GetNormal(){
    return Normal;
}

void Vertex::SetNormal(Vector3 normal){
    Normal = normal;
}

void Vertex::SetNormal(float x, float y, float z){
    Normal.x = x;
    Normal.y = y;
    Normal.z = z;
}

//
//void Vertex::SetSkinweights(int numattachments, std::vector<float> weights){
//    numAttachments = numattachments;
//    skinweights = weights;
//}
//
//std::vector<float> Vertex::GetSkinweights(){
//    return skinweights;
//}
//
//void Vertex::SetJointNums(int numattachments, std::vector<int> joints){
//    jointNums = joints;
//}
//
//std::vector<int> Vertex::GetJointNums(){
//    return jointNums;
//}
//
//float Vertex::GetSkinweightByJoint(int jointNum){
//    if(jointNum < skinweights.size())
//        return skinweights[jointNum];
//    else
//        return 0.0;
//}