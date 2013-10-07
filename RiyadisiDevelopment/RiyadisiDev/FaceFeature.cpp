#pragma once

#include "FaceFeature.h"
FaceFeature::FaceFeature()
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
Point2f FaceFeature::getGazePoint()
{
    // need to check when both eyes are open, single eye is open and no eye is detected or opened.

    /*Point2f point ( 0, 0 );
    if ( getLeftEye().isAvailable() && getRightEye().isAvailable() ) {
        point.x =  ( getLeftEye().getFeatureRect().x + getRightEye().getFeatureRect().x
                     + getLeftEye().getPupil().getCenterPoint().x
                     + getRightEye().getPupil().getCenterPoint().x ) / 2;
        point.y =  ( getLeftEye().getFeatureRect().y + getRightEye().getFeatureRect().y
                     + getLeftEye().getPupil().getCenterPoint().y
                     + getRightEye().getPupil().getCenterPoint().y ) / 2;
    }


    return point;*/
    throw new exception ( "Not implemented yet" );
}