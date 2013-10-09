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
    bool isYawning();
};