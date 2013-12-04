#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork ( bool isTraining ) {
    try {
        // use the .data extension for the training data and .neural for the data generated from the neural network
        neuralDataFilename = "data/neuralData.neural";

        this->isTraining = isTraining;
        if ( isTraining ) {
            // if the data file is available resume from there.otherwise create a new network
            if ( isExists ( neuralDataFilename ) ) {
                network.create_from_file ( neuralDataFilename );
            } else {
                network.create_standard ( numLayers, numInput, numNeuronsHidden, numOutput );
            }
            network.set_activation_function_hidden ( FANN::SIGMOID_SYMMETRIC );
            network.set_activation_function_output ( FANN::SIGMOID_SYMMETRIC );
        } else {
            if ( isExists ( neuralDataFilename ) ) {
                network.create_from_file ( neuralDataFilename );
            }
        }
    } catch ( exception ex ) {
        Log::log (  ex.what() );
    }
}
NeuralNetwork::~NeuralNetwork() {
    try {
        // deletion

    } catch ( exception ex ) {
        Log::log ( ex.what() );
    }
}
void NeuralNetwork::trainNetwork ( string fileName ) {
    if ( !isTraining ) {
        throw exception ( "Unsupported mode" );
    }
    try {
        network.train_on_file ( fileName, maxEpochs, epochsBetweenReports, desiredError );
        network.save ( neuralDataFilename );
    } catch ( exception ex ) {
        Log::log (  ex.what() );
    }
}
void NeuralNetwork::save() {
    // only save in the operation mode.
    if ( !isTraining ) {
        throw exception ( "Unsupported mode" );
    }
    try {
        network.save ( neuralDataFilename );
    } catch ( exception ex ) {
        Log::log ( ex.what()  );
    }
}

void NeuralNetwork::resetNetwork() {
    throw exception ( "Not implemented yet" );
}
bool NeuralNetwork::getAlertValue ( double weightedPerclose, double noddingOffMeasure,
                                    DirectedGaze gazeMeasure, vector<float> headRotationMeasure,
                                    double yawningMeasure ) {
    if ( isTraining ) {
        throw exception ( "Unsupported mode" );
    }
    try {
        fann_type input[8], output;
        input[0] = weightedPerclose;
        input[1] = noddingOffMeasure;
        input[2] = gazeMeasure.horizontal;
        input[3] = gazeMeasure.vertical;
        input[4] = yawningMeasure;
        input[5] = ( headRotationMeasure.size() > 1 ) ? headRotationMeasure[0] : 0;
        input[6] = ( headRotationMeasure.size() > 1 ) ? headRotationMeasure[1] : 0;
        input[7] = ( headRotationMeasure.size() > 1 ) ? headRotationMeasure[2] : 0;
        output = * ( network.run ( input ) );

        return ( output > 0.5 );
    } catch ( exception ex ) {
        Log::log (  ex.what() );
    }
}