//
//  DOF.hpp
//  cse169
//
//  Created by Karen Wolfe on 4/3/16.
//
//

#ifndef DOF_h
#define DOF_h

#include <stdio.h>
class DOF{
public:
    DOF();
    ~DOF();
    
    void SetValue(float v)  { value = v; }
    void SetMin(float m)    { min = m; }
    void SetMax(float m)    { max = m; }
    float GetValue()        { return value; }
    float GetMin()          { return min; }
    float GetMax()          { return max; }
    
private:
    float min, max;
    float value;
};
#endif /* DOF_h */
