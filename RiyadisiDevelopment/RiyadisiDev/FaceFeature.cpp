#pragma once

#include "FaceFeature.h"

NoseFeature FaceFeature::getNose()
{
    return this->nose;
}
EyeFeature FaceFeature::getLeftEye()
{
    return this->leftEye;
}
EyeFeature FaceFeature::getRightEye()
{
    return this->rightEye;
}
MouthFeature FaceFeature::getMouth()
{
    return this->mouth;
}
Mat FaceFeature::getImage()
{
    return this->image;
}
void FaceFeature::setImage ( Mat image )
{
    this->image = image;
}