#include "Gaze.h"

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