#include "Gaze.h"

using namespace cv;
using namespace std;

Gaze::Gaze ( void )
{
}
Gaze::~Gaze ( void )
{
}
void Gaze::setGaze ( Circle leftEye, Circle rightEye )
{
    this->leftEye = leftEye;
    this->rightEye = rightEye;
}