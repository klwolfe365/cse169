//
//  Rig.h
//  cse169
//
//  Created by Karen Wolfe on 5/2/16.
//
//

#ifndef Rig_h
#define Rig_h

#include <stdio.h>

#include "Skeleton.h"
#include "Skin.h"

class Rig{
public:
    Skeleton skel;
    Skin skin;
    
    Rig();
    ~Rig();
    
private:
};
#endif /* Rig_h */
