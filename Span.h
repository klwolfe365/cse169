//
//  Span.h
//  cse169
//
//  Created by Karen Wolfe on 5/3/16.
//
//

#ifndef Span_h
#define Span_h

#include <stdio.h>
#include "Keyframe.h"

class Span {
public:
    float a, b, c, d, u;
    Keyframe* k0;
    Keyframe* k1;
    
    void setCoefficients();
};
#endif /* Span_h */
