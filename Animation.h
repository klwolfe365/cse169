//
//  Animation.h
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#ifndef Animation_h
#define Animation_h

#include <stdio.h>
#include <vector>

#include "token.h"
#include "Channel.h"

class Animation {
public:
    static const bool DEBUG = false;
    Animation();
    ~Animation();
    
    bool Load(const char* file);
    void Update();
    void Draw();
    
    std::vector<Channel *> GetChannels()        { return channels; }

private:
    const char * filename;
    float timeStart, timeEnd;
    int numChannels;
    std::vector<Channel *> channels;
};
#endif /* Animation_h */
