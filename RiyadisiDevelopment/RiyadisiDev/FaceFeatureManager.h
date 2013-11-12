#pragma once
#include "Feature.h"
#include "FeatureCollection.h"
#include "FaceFeature.h"
#include "FaceDetector.h"
#include "EyeDetector.h"
#include "PupilDetector.h"
#include "NoseDetector.h"
#include "MouthDetector.h"
#include "EyeStateDetector.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define DOWNSAMPLE_CONSTANT 4 //should be a power of 2
///<summary>
/// This class identifies and manages the facial features within a sequence of images
///</summary>
class FaceFeatureManager {
public:
    FaceFeatureManager ( void );
    ~FaceFeatureManager ( void );
    FeatureCollection *getFeatureCollection();
    void findFeatures ( Mat image, FaceFeature *faceFeature, Rect faceROI );
    void findNoseFeature ( Mat image, Rect roi, NoseFeature &noseFeature );
    void findLeftEyeFeature ( Mat image, Rect roi, EyeFeature &eyeFeature );
    void findRightEyeFeature ( Mat image, Rect roi, EyeFeature &eyeFeature );
    void findMouthFeature ( Mat image, Rect roi, MouthFeature &mouthFeature );
    void findPupilFeature ( Mat image, Rect roi, PupilFeature &pupilFeature );
	double perclos;
	double preeyeState;
	clock_t time;
private:
    FeatureCollection features;
    FaceDetector faceDetector;
    EyeDetector eyeDetector;
	MouthDetector mouthDetector;
    PupilDetector pupilDetector;
    NoseDetector noseDetector;
	EyeStateDetector eyeStateDetector;
	FileStorage fs;
	
};