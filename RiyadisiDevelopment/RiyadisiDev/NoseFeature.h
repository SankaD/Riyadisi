#pragma once
#include "Feature.h"

class NoseFeature : public  Feature {
private:
    int centerAxis;
public:
    ///<summary>
    ///Gets the x value of the center of the nose
    ///</summary>
    int getCenterAxis();
    void setCenterAxis ( int centerAxisX );
};