#pragma once
#include "Feature.h"
#include "NoseFeature.h"
#include "EyeFeature.h"
#include "MouthFeature.h"

#include <opencv2\objdetect\objdetect.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

///<summary>
///Represents facial features
///</summary>
class FaceFeature : public Feature {
private:
    NoseFeature *nose;
    EyeFeature *leftEye;
    EyeFeature *rightEye;
    MouthFeature *mouth;
    Mat *image;
public:
    FaceFeature();
    NoseFeature *getNose();
    EyeFeature *getLeftEye();
    EyeFeature *getRightEye();
    MouthFeature *getMouth();
    Mat *getImage();
    void setImage ( Mat *image ) ;
};