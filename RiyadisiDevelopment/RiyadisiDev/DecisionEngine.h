#pragma once

#include "FaceFeature.h"
#include "FeatureCollection.h"
#include "NeuralNetwork.h"

///<summary>
///Manages the decision making component of the system
///</summary>
class DecisionEngine {
private:
    NeuralNetwork network;
    static string defaultFilename;
public:
    DecisionEngine();
    ~DecisionEngine();

    ///<summary>
    ///Trains the internal neural network using the provided file.
    ///</summary>
    void trainEngine ( string filename = defaultFilename );
    bool shouldAlert ( double eyeState, double noddingOff, double gaze, double headRotation, double yawning );

};