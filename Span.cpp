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
    a = 2*k0->getValue() - 2*k1->getValue() + (t)*k0->getTanOut() +(t)*k1->getTanIn();
    b = -3*k0->getValue() + 3*k1->getValue() - 2*t*k0->getTanOut() - t*k1->getTanIn();
    c = t * k0->getTanOut();
    d = t * k1->getTanIn();
}
