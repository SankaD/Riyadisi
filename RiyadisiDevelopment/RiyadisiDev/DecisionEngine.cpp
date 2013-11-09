#pragma once

#include "DecisionEngine.h"

string DecisionEngine::defaultFilename = "data/trainingData.data";

DecisionEngine::DecisionEngine() : network ( NeuralNetwork ( false ) ) {

}

bool DecisionEngine::trainEngine ( string filename ) {
    try {
        //neural network to train
        NeuralNetwork trainingNetwork ( true );
        ifstream stream ( filename );
        if ( stream.is_open() ) {
            // file contains multiple filenames
            int lineCount = 0;
            stream >> lineCount;
            stringstream str;
            str << "Training using " << lineCount << " files.";
            Log::log (  str.str() );

            // iteratively train the network using each file.
            for ( int i = 0; i < lineCount; i++ ) {
                stream >> filename;
                Log::log ( "Training using : " + filename );
                trainingNetwork.trainNetwork ( filename );

                Log::log ( "Trained using : " + filename );
            }
            trainingNetwork.save();
        }

        return true;
    } catch ( exception e ) {
        Log::log ( e.what() );
    }
}
bool DecisionEngine::shouldAlert ( double eyeState, double noddingOff, double gaze, double headRotation, double yawning ) {
    return network.getAlertValue ( eyeState, noddingOff, gaze, headRotation, yawning );
}
DecisionEngine::~DecisionEngine() {

}