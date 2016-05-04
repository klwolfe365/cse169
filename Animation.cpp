//
//  Animation.cpp
//  cse169
//
//  Created by Karen Wolfe on 5/1/16.
//
//

#include "Animation.h"
Animation::Animation(){}

Animation::~Animation(){}

bool Animation::Load(const char *file){
    filename = file;
    
    Tokenizer token;
    token.Open(file);
    token.FindToken("animation");
    token.FindToken("{");
    
    while(1) {
        char temp[256];
        token.GetToken(temp);
        if(strcmp(temp, "range") == 0) {
            timeStart = token.GetFloat();
            timeEnd = token.GetFloat();
            if(DEBUG)
                printf("timeStart: %f\ttimeEnd: %f\n", timeStart, timeEnd);
        }
        else if(strcmp(temp, "numchannels") == 0) {
            numChannels = token.GetInt();
            if(DEBUG)
                printf("NumChannels: %d\n", numChannels);
        }
        else if(strcmp(temp, "channel") == 0) {
            Channel * c = new Channel();
            c->Load(token);
            channels.push_back(c);
            if(DEBUG){
                printf("Channel #%lu- Extrapolation In/Out: %s/%s\tNumKeys: %d\n", channels.size(), c->GetExtrapIn(), c->GetExtrapOut(), c->GetNumKeys());
                std::vector<Keyframe *> keys = c->GetKeys();
                for(Keyframe * k : keys)
                printf("\tKey- Time: %f\tValue: %f\tTangentMode In/Out: %s/%s\n\t\tTangent_in:%f\tTangent_out:%f\n", k->getTime(), k->getValue(), k->getTanModeIn(), k->getTanModeOut(), k->getTanIn(), k->getTanOut());
            }
        }
        else if(strcmp(temp, "}") == 0) {
            token.Close();
            return true;
        }
        else token.SkipLine();
    }
    return false;
    
}