//
//  Keyframe.h
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#ifndef Keyframe_h
#define Keyframe_h

#include <stdio.h>

#include "token.h"
class Keyframe {
public:
    static const bool DEBUG = false;
    Keyframe();
    ~Keyframe();
    
    void setTime(float t)   { time = t; }
    float getTime()         { return time; }
    void setValue(float v)  { value = v; }
    float getValue()         { return value; }
    void setTanIn(float t)  { tangentIn = t; }
    float getTanIn()         { return tangentIn; }
    void setTanOut(float t) { tangentOut = t; }
    float getTanOut()         { return tangentOut; }
    
    void setTanModeIn(const char * t)  { tanModeIn = t; }
    const char * getTanModeIn()         { return tanModeIn; }
    void setTanModeOut(const char * t) { tanModeOut = t; }
    const char * getTanModeOut()         { return tanModeOut; }
    
    void setCoefficients();
    float CalculateTangent(Keyframe* prev, Keyframe* next);
    
private:
    float time, value, tangentIn, tangentOut;
    const char * tanModeIn;
    const char * tanModeOut;
    float a,b,c,d;
    
    bool isValidTangent(const char* s);
    bool isFloat(const char* s);
};
#endif /* Keyframe_h */
