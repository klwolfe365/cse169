//
//  Player.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#include "Player.h"

Player::Player(){}

Player::~Player(){}

void Player::Update(){
    
    if(time < anim->GetTimeEnd())
        time += 0.01;
    std::vector<Channel *> channels = anim->GetChannels();
    
    Joint * curr = skel->GetJoint(0);
    
    float xTranslate = channels[0]->Evaluate(time);
    float yTranslate = channels[1]->Evaluate(time);
    float zTranslate = channels[2]->Evaluate(time);
    
    curr->SetOffset(xTranslate, yTranslate, zTranslate);
    
    for(int i = 3; i < channels.size(); i+=3){
        int jointNum = floor((i-1)/3);
        Channel * rotX = channels[i];
        Channel * rotY = channels[i+1];
        Channel * rotZ = channels[i+2];
        
        float x = rotX->Evaluate(time);
        float y = rotY->Evaluate(time);
        float z = rotZ->Evaluate(time);
        
        curr = skel->GetJoint(jointNum);
        curr->GetDof(0)->SetValue(x);
        curr->GetDof(1)->SetValue(y);
        curr->GetDof(2)->SetValue(z);
        
    }
}