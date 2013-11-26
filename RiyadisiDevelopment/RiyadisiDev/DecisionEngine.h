#pragma once

#include "FaceFeature.h"
#include "FeatureCollection.h"
#include "NeuralNetwork.h"
#include "Log.h"

#include <iostream>
#include <fstream>

using namespace std;

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
    bool trainEngine ( string filename = defaultFilename );

    ///<summary>
    ///Checks whether an alert should be made or not according to the given parameters.
    ///</summary>
    bool shouldAlert ( double eyeState, double noddingOff, double gaze, vector<float> headRotation, double yawning );

};