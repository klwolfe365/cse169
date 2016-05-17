//
//  Channel.h
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#ifndef Channel_h
#define Channel_h

#include <stdio.h>
#include <vector>

#include "token.h"
#include "Keyframe.h"

class Channel {
public:
    static const bool DEBUG = false;
    Channel();
    ~Channel();
    
    bool Load(Tokenizer &t);
    float Evaluate(float t);
    float Extrapolate(float t);
    const char * GetExtrapIn()          { return extrapIn; }
    const char * GetExtrapOut()         { return extrapOut; }
    int GetNumKeys()                    { return numKeys; }
    std::vector<Keyframe *> GetKeys()   { return keys; }
    
    
private:
    const char * extrapIn;
    const char * extrapOut;
    int numKeys;
    std::vector<Keyframe *> keys;
    
    void SetTangentValues();
    
    void SetCoefficients();
    float doLinearExtrapolation(float time);
    float doCyclicExtrapolation(float time);
    float doCyclicOffsetExtrapolation(float time);
    float doBounceExtrapolation(float time);
};
#endif /* Channel_h */
