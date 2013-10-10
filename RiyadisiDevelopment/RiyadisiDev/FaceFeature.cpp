#pragma once

#include "FaceFeature.h"
FaceFeature::FaceFeature() :  Feature()
{
}
NoseFeature *FaceFeature::getNose()
{
    return &nose;
}
EyeFeature *FaceFeature::getLeftEye()
{
    return &leftEye;
}
EyeFeature *FaceFeature::getRightEye()
{
    return &rightEye;
}
MouthFeature *FaceFeature::getMouth()
{
    return &mouth;
}
Mat FaceFeature::getImage()
{
    return image;
}
void FaceFeature::setImage ( Mat newImage )
{
    image = newImage;
}
Gaze FaceFeature::getGazeData()
{
    Gaze gaze;
    if ( isAvailable() ) {
        gaze.setAvailable ( true );
        gaze.setLeftEye ( leftEye.getFeatureRect() );
        gaze.setRightEye ( rightEye.getFeatureRect() );
        gaze.setLeftPupil (  ( leftEye.getPupil()->getCenterPoint() ) );
        gaze.setRightPupil ( ( rightEye.getPupil()->getCenterPoint() ) );
    }
    return gaze;
}
void FaceFeature::clearFeature()
{
    Feature::clearFeature();
    nose.clearFeature();
    leftEye.clearFeature();
    rightEye.clearFeature();
    mouth.clearFeature();
}