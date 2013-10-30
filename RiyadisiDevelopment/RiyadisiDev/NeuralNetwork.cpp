#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork ( bool isTraining, bool fromFile )
{
    // use the .data extension for the training data and .neural for the data generated from the neural network
    neuralDataFilename = "neuralData.neural";

    this->isTraining = isTraining;

    if ( isTraining ) {
        // if the data file is available resume from there.otherwise create a new network
        if ( fromFile ) {
            network.create_from_file ( neuralDataFilename );
        } else {
            network.create_standard ( numLayers, numInput, numNeuronsHidden, numOutput );
        }
        network.set_activation_function_hidden ( FANN::SIGMOID_SYMMETRIC );
        network.set_activation_function_output ( FANN::SIGMOID_SYMMETRIC );
    } else {
        network.create_from_file ( neuralDataFilename );
    }
}
NeuralNetwork::~NeuralNetwork()
{
    network.destroy();
}
void NeuralNetwork::trainNetwork ( string fileName )
{
    if ( !isTraining ) {
        throw exception ( "Unsupported mode" );
    }

    network.train_on_file ( fileName, maxEpochs, epochsBetweenReports, desiredError );
    network.save ( neuralDataFilename );
}
void NeuralNetwork::resetNetwork()
{
    throw exception ( "Not implemented yet" );
}
bool NeuralNetwork::getAlertValue ( double weightedPerclose, double noddingOffMeasure,
                                    double gazeMeasure, double headRotationMeasure,
                                    double yawningMeasure )
{
    if ( isTraining ) {
        throw exception ( "Unsupported mode" );
    }
    fann_type input[5], output;
    input[0] = weightedPerclose;
    input[1] = noddingOffMeasure;
    input[2] = gazeMeasure;
    input[3] = headRotationMeasure;
    input[4] = yawningMeasure;

    output = * ( network.run ( input ) );

    return ( output > 0.5 );
}