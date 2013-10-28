#include "include\fann.h"
#include "include\fann_cpp.h"
#include "include\floatfann.h"
#include <iostream>

using namespace std;
using namespace FANN;

static const unsigned int numInput = 5;
static const unsigned int numOutput = 1;
static const unsigned int numLayers = 3;
static const unsigned int numNeuronsHidden = 3;
static const float desiredError = 0.0001;
static const unsigned int maxEpochs = 500000;
static const unsigned int epochsBetweenReports = 1000;

///<summary>
///Represents a neural network
///</summary>
class NeuralNetwork {
public:
    ///<summary>
    ///Creates a neural network
    ///</summary>
    ///<param name="isTraining">Whether the network is created for training or not.</param>
    NeuralNetwork ( bool isTraining = false, bool fromFile = true );
    ~NeuralNetwork();
private:
    bool isTraining;
    string neuralDataFilename;;// = "neuralData.neural";


    neural_net network;

    ///<summary>
    ///Trains the network using the given file.
    ///</summary>
    void trainNetwork ( string fileName );

    ///<summary>
    ///Clears the weights and resets the neural network
    ///</summary>
    void resetNetwork();

    ///<summary>
    ///Gets a value representing the necessity of alerting the driver.
    ///</summary>
    ///<param name="weightedPerclose">Accumilated weighted PERCLOSE value at the moment</param>
    ///<param name="noddingOffMeasure">Accumilated weighted Nodding off values</param>
    ///<returns> Whether or not to alert the driver</returns>
    bool getAlertValue ( double weightedPerclose, double noddingOffMeasure,
                         double gazeMeasure, double headRotationMeasure,
                         double yawningMeasure );
};