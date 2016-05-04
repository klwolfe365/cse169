//
//  Player.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#include "Player.h"

void Player::Update(){
    time += 1; //Increment time
    //Evaluate animation
    
    //Pose skeleton
    //first 3 translate root
    //joint num = current num - 3
        //current joint DOF = current num mod 3
            // = 1: x dof rotate
            // = 2: y dof rotate
            // = 0: z dof rotate
    
    std::vector<Channel *> channels = anim->GetChannels();
    for(int i = 3; i < channels.size()/3; i+=3){
        int jointNum = i - 3;
        
    }
    // 1 2 3
    // 4 5 6
    // x y z
}