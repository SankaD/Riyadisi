#pragma once

#include "FaceFeature.h"
#include "FeatureCollection.h"

class DecisionEngine {
private:
    FeatureCollection features;
public:
    ///<summary>
    ///Called when the next step of the processing needs to happen.
    ///Specially when a new feature is added for a new frame.
    ///</summary>
    void incrementStep();
    void trainEngine();


};