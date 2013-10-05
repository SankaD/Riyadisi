#pragma once

#include "FaceFeature.h"
FaceFeature::FaceFeature()
{
}
NoseFeature FaceFeature::getNose()
{
    return nose;
}
EyeFeature &FaceFeature::getLeftEye()
{
    return leftEye;
}
EyeFeature &FaceFeature::getRightEye()
{
    return rightEye;
}
MouthFeature FaceFeature::getMouth()
{
    return mouth;
}
Mat FaceFeature::getImage()
{
    return image;
}
void FaceFeature::setImage ( Mat newImage )
{
    image = newImage;
}