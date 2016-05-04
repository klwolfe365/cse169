//
//  Channel.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#include "Channel.h"

Channel::Channel(){}

Channel::~Channel(){}

bool Channel::Load(Tokenizer &t){
    t.FindToken("{");
    while(1){
        char temp[256];
        t.GetToken(temp);
        if(strcmp(temp, "extrapolate") == 0){
            char extrapIn[256];
            t.GetToken(extrapIn);
            this->extrapIn = strdup(extrapIn);
            char extrapOut[256];
            t.GetToken(extrapOut);
            this->extrapOut = strdup(extrapOut);
        }
        else if(strcmp(temp, "keys") == 0){
            numKeys = t.GetInt();
            int n = 0;
            t.FindToken("{");
            while(n < numKeys){
                Keyframe * k = new Keyframe();
                k->setTime(t.GetFloat());
                k->setValue(t.GetFloat());
                
                char tanInMode[256];
                t.GetToken(tanInMode);
                k->setTanModeIn(strdup(tanInMode));
                if(DEBUG)
                    printf("#%d In: %s", n+1, k->getTanModeIn());
                
                char tanOutMode[256];
                t.GetToken(tanOutMode);
                k->setTanModeOut(strdup(tanOutMode));
                if(DEBUG)
                    printf("\tOut: %s\n",k->getTanModeOut());
                
                keys.push_back(k);
                n++;
            }
            SetTangentValues();
            SetCoefficients();
            if(DEBUG){
                for(int i = 0; i < numKeys; i++){
                    printf("\t%d: %f %f\n", i, keys[i]->getTanIn(), keys[i]->getTanOut());
                }
            }
            t.FindToken("}");
        }
        else if(strcmp(temp, "}") == 0)
            return true;
        else t.SkipLine();
    }
    return false;
}

void Channel::SetTangentValues(){
    if(keys.size() < 2)
        return;
    
    Keyframe * curr = keys.front();
    if(strcmp(curr->getTanModeOut(), "flat") == 0)
        curr->setTanOut(0.0f);
    else if((strcmp(curr->getTanModeOut(), "linear") == 0) || strcmp(curr->getTanModeOut(), "smooth") == 0){
        float t = curr->CalculateTangent(curr, keys[1]);
//        float p0 = curr->getValue();
//        float p1 = keys[1]->getValue();
//        float t0 = curr->getTime();
//        float t1 = keys[1]->getTime();
        
        curr->setTanOut(t);
    }
    else {
        curr->setTanOut(strtof(curr->getTanModeIn(), '\0'));
    }

    for(int i = 1; i < numKeys-1; i++){
        curr = keys[i];
        /* Tangent in modes */
        if(strcmp(curr->getTanModeIn(), "flat") == 0){
            curr->setTanIn(0.0f);
        } else if(strcmp(curr->getTanModeIn(), "linear") == 0){
            float t = curr->CalculateTangent(keys[i-1], curr);
//            float p0 = keys[i-1]->getValue();
//            float t0 = keys[i-1]->getTime();
//            float p1 = curr->getValue();
//            float t1 = curr->getTime();
//            float t = (p1-p0)/(t1-t0);
            curr->setTanIn(t);
        } else if(strcmp(curr->getTanModeIn(), "smooth") == 0){
            float t = curr->CalculateTangent(keys[i-1], keys[i+1]);
//            float p0 = keys[i-1]->getValue();
//            float t0 = keys[i-1]->getTime();
//            float p2 = keys[i+1]->getValue();
//            float t2 = keys[i+1]->getTime();
//            float t = (p2-p0)/(t2-t0);
            curr->setTanIn(t);
            curr->setTanOut(t);
        } else {
            curr->setTanIn(strtof(curr->getTanModeIn(), '\0'));
        }
        
        /* Tangent out modes */
        if(strcmp(curr->getTanModeOut(), "flat") == 0){
            curr->setTanOut(0.0f);
        } else if(strcmp(curr->getTanModeOut(), "linear") == 0){
            float t = curr->CalculateTangent(curr, keys[i+1]);
//            float p0 = curr->getValue();
//            float t0 = curr->getTime();
//            float p1 = keys[i+1]->getValue();
//            float t1 = keys[i+1]->getTime();
//            float t = (p1-p0)/(t1-t0);
            curr->setTanOut(t);
        } else if(strcmp(curr->getTanModeOut(), "smooth") == 0){
            float t = curr->CalculateTangent(keys[i-1], keys[i+1]);
            curr->setTanOut(t);
        } else {
            curr->setTanOut(strtof(curr->getTanModeIn(), '\0'));
        }
    }
    
    /* Only set tangent in for last keyframe */
    curr = keys.back();
    if(strcmp(curr->getTanModeIn(), "flat") == 0)
        curr->setTanIn(0.0f);
    else if((strcmp(curr->getTanModeIn(), "linear") == 0) || strcmp(curr->getTanModeIn(), "smooth") == 0){
        float t = curr->CalculateTangent(keys[numKeys-2], curr);
//        float p1 = curr->getValue();
//        float p0 = keys[numKeys-2]->getValue();
//        float t1 = curr->getTime();
//        float t0 = keys[numKeys-2]->getTime();
        
        curr->setTanIn(t);
    }
    else {
        curr->setTanIn(strtof(curr->getTanModeIn(), '\0'));
    }

}

float Channel::Evaluate(float t){
    if(keys.size() <= 0)
        return 0.0f;
    if(keys.size() == 1)
        return keys[0]->getValue();
    
    if(t < keys[0]->getTime() || t > keys.back()->getTime()){
        return Extrapolate(t);
    }
    for(int i = 0; i < numKeys; i++){
        Keyframe * curr = keys[i];
        if(t == curr->getTime())
            return curr->getValue();
        else if(t < curr->getTime()){
            Span * s = spans[i-1];
            float a = s->a;
            float b = s->b;
            float c = s->c;
            float d = s->d;
            float t0 = s->k0->getTime();
            float t1 = s->k1->getTime();
            float u = (t - t0)/(t1 - t0);
            
            return d + u*(c + u*(b + u*(a)));
        }
    }
    return 0.0f;
}


void Channel::SetCoefficients(){
    if(keys.size() < 2)
        return;
    
    for(int i = 0; i < keys.size()-1; i++){
        Span * s = new Span();
        s->k0 = keys[i];
        s->k1 = keys[i+1];
        s->setCoefficients();
        spans.push_back(s);
    }
    
}

/**
  * Evaluates value based off the extrapolation mode
  * for a time not in the base channel range.
  */
float Channel::Extrapolate(float t){
    if(t < keys.front()->getTime()){
        if(strcmp(extrapIn, "flat") == 0)
            return keys.front()->getValue();
        if(strcmp(extrapIn, "linear") == 0)
            return doLinearExtrapolation(t);
        if(strcmp(extrapIn, "cyclic") == 0)
            return doCyclicExtrapolation(t);
        if(strcmp(extrapIn, "cyclic_offset") == 0)
            return doCyclicOffsetExtrapolation(t);
        if(strcmp(extrapIn, "bounce") == 0)
            return doBounceExtrapolation(t);
    }
    if( t > keys.back()->getTime()){
        if(strcmp(extrapOut, "flat") == 0)
            return keys.back()->getValue();
        if(strcmp(extrapOut, "linear") == 0)
            return doLinearExtrapolation(t);
        if(strcmp(extrapOut, "cyclic") == 0)
            return doCyclicExtrapolation(t);
        if(strcmp(extrapOut, "cyclic_offset") == 0)
            return doCyclicOffsetExtrapolation(t);
        if(strcmp(extrapOut, "bounce") == 0)
            return doBounceExtrapolation(t);
    }
    
    return 0.0f;
}


/**
  * Uses the tangent at the first/last key to compute value
  */
float Channel::doLinearExtrapolation(float time){
    if(time < keys.front()->getTime()){
        float p1 = keys.front()->getValue();
        float t1 = keys.front()->getTime();
        float t0 = time;
        float v1In = keys.front()->getTanOut();
        return p1 - (v1In * (t1 - t0));
    } else {
        float p0 = keys.back()->getValue();
        float t0 = keys.back()->getTime();
        float t1 = time;
        float v0Out = keys.back()->getTanIn();
        return v0Out * (t1 - t0) + p0;
    }
}


/**
  * Gets a time within channel window based on offset
  * to compute correct valule
  */
float Channel::doCyclicExtrapolation(float time) {
    float tMin = keys.front()->getTime();
    float tMax = keys.back()->getTime();
    float cIndex = floor((time - tMin)/(tMax - tMin));
    
    float start = cIndex*(tMax-tMin)+tMin;
    float tPrime = time - start + tMin;
    
    return Evaluate(tPrime);
}


/**
  * Repeats the channel + a value offset to compute the value
  */
float Channel::doCyclicOffsetExtrapolation(float time) {
    float tMin = keys.front()->getTime();
    float tMax = keys.back()->getTime();
    float cIndex = floor((time - tMin)/(tMax - tMin));
    
    float start = cIndex*(tMax-tMin)+tMin;
    float tPrime = time - start + tMin;
    float offset = keys.back()->getValue() - keys.front()->getValue();
    return Evaluate(tPrime) + cIndex*offset;
}

/*TODO*/
float Channel::doBounceExtrapolation(float time){
    return 0.0f;
}