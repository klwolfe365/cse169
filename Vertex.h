//
//  Vertex.h
//  cse169
//
//  Created by Karen Wolfe on 4/16/16.
//
//

#ifndef Vertex_h
#define Vertex_h

#include <stdio.h>
#include <vector>


#include "vector3.h"

class Vertex{
public:
    static const bool DEBUG = false;
    Vertex();
    ~Vertex();
    
    Vector3 GetPosition();
    void SetPosition(Vector3 position);
    void SetPosition(float x, float y, float z);
    
    Vector3 GetNormal();
    void SetNormal(Vector3 normal);
    void SetNormal(float x, float y, float z);
    
//    std::vector<float> GetSkinweights();
//    void SetSkinweights(int joint, float weight);
//    
//    std::vector<int> GetJointNums();
//    void SetJointNums(int numattachments, std::vector<int> weights);
    
//    float GetSkinweightByJoint(int jointNum);
    
    
    int numAttachments;
    float skinweights[4];
    int joints[4];
    
private:
    Vector3 Position;
    Vector3 Normal;
//    std::vector<int> jointNums;
//    std::vector<float> skinweights;
};

#endif /* Vertex_h */
