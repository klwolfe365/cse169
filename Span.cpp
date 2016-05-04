//
//  Span.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/3/16.
//
//

#include "Span.h"

void Span::setCoefficients(){
    float t =k1->getTime() - k0->getTime();
    float p0 = k0->getValue();
    float p1 = k1->getValue();
    float v0 = k0->getTanOut();
    float v1 = k1->getTanIn();
    
    a = (2*p0) - (2*p1) + (t*v0) + (t*v1);
    b = (-3*p0) + (3*p1) + (-2*(t*v0)) - (t*v1);
    c = t*v0;
    d = t*v1;
//    
//    a = (2*k0->getValue()) - (2*k1->getValue()) + ((t)*k0->getTanOut()) + ((t)*k1->getTanIn());
//    b = (-3*k0->getValue()) + (3*k1->getValue()) - (2*t*k0->getTanOut()) - (t*k1->getTanIn());
//    c = t * k0->getTanOut();
//    d = t * k1->getTanIn();
}
