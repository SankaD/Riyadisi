#pragma once

#include "DecisionEngine.h"

string DecisionEngine::defaultFilename = "trainData.data";

DecisionEngine::DecisionEngine()
{
    network = NeuralNetwork ( false );
}

void DecisionEngine::trainEngine ( string filename )
{
    NeuralNetwork trainingNetwork ( true, true );
    trainingNetwork.trainNetwork ( filename );

}
bool DecisionEngine::shouldAlert ( double eyeState, double noddingOff, double gaze, double headRotation, double yawning )
{
    return network.getAlertValue ( eyeState, noddingOff, gaze, headRotation, yawning );
}
