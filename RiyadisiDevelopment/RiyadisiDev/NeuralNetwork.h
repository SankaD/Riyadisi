#include "include\fann.h"
#include "include\fann_cpp.h"
#include <iostream>

using namespace std;

///<summary>
///Represents a neural network
///</summary>
class NeuralNetwork {
public:
    NeuralNetwork();
    ~NeuralNetwork();
private:
    ///<summary>
    ///Trains the network using the given file.
    ///</summary>
    void trainNetwork ( string fileName );

    double getValue ( double weightedPerclose, double noddingOffValue,
                      double gazeValue, double headRotation, double yawningValue );
}