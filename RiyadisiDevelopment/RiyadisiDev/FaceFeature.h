#pragma once
#include "Feature.h"
#include "NoseFeature.h"
#include "EyeFeature.h"
#include "MouthFeature.h"
#include "Gaze.h"

#include <opencv2\objdetect\objdetect.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

///<summary>
///Represents facial features
///</summary>
class FaceFeature : public Feature {
private:
    NoseFeature nose;
    EyeFeature leftEye;
    EyeFeature rightEye;
    MouthFeature mouth;
    Mat image;
	string orientation;
public:
    FaceFeature();

    ///<summary>
    ///Gets a reference to the NoseFeature instance within the instance
    ///</summary>
    ///<returns>A reference to the NoseFeature instance</returns>
    NoseFeature *getNose();

    ///<summary>
    ///Gets a 'reference' to the EyeFeature for left eye
    ///</summary>
    ///<returns>A reference to the left EyeFeature</returns>
    EyeFeature *getLeftEye();

    ///<summary>
    ///Gets a 'reference' to the EyeFeature for right eye
    ///</summary>
    ///<returns>A reference to the right EyeFeature</returns>
    EyeFeature *getRightEye();

    ///<summary>
    ///Gets a reference to the MouthFeature instance within this instance
    ///</summary>
    ///<returns>A reference to the MouthFeature instance</returns>
    MouthFeature *getMouth();

    Gaze getGazeData();
    Mat getImage();
    void setImage ( Mat image ) ;
	string getOrientation();
    void setOrientation ( string orientation ) ;
    virtual void clearFeature();
};