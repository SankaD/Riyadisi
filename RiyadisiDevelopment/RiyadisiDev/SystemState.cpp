#pragma once

#include "FaceFeature.h"

///<summary>
///Represents the state of the system in a specific instance.
///</summary>
class SystemState {
private:
    bool eyeClosed;
    bool yawning;
    float noddingOff;
    FaceFeature faceFeature;

public:
    bool isEyeClosed();
    void setEyeState ( bool closed );
    bool isYawning();
    void setYawning ( bool yawning );
    float getNoddingOffProbability();
    void setNoddingOffProbability();
    FaceFeature getFaceFeature();
    void setFaceFeature();
};