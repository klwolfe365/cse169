//
//  Player.h
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#ifndef Player_h
#define Player_h

#include <stdio.h>

#include "Skeleton.h"
#include "Skin.h"
#include "Animation.h"

class Player{
public:
    Player();
    ~Player();
    
    void SetSkeleton(Skeleton* s)           { skel = s; }
    void SetSkin(Skin* s)                   { skin = s; }
    void SetAnimation(Animation* a)         { anim = a; }
    void SetTime(float t)                   { time = t; }
    
    Skeleton* GetSkeleton()                 { return skel; }
    Skin* GetSkin()                         { return skin; }
    Animation* GetAnimation()               { return anim; }
    float GetTime()                         { return time; }
    
    void Update();

private:
    Skeleton* skel;
    Skin* skin;
    Animation* anim;
    float time;

};
#endif /* Player_h */
