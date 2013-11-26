#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Log.h"
#include "ImageManager.h"

#include "FaceFeatureManager.h"
#include "NoddingOffDetector.h"
#include "YawningDetector.h"
#include "HeadRotationDetector.h"
#include "GazeDetector.h"
#include "Utility.h"

using namespace std;

class TrainingFileCreator {
public:
    TrainingFileCreator ( void );
    ~TrainingFileCreator ( void );
    void trainUsingFile ( string fileName );
private:
    void trainUsingVideo ( string inputFileName, string outputFileName );
    void drawTexts ( Mat &frame, long int ticksForFrame );

    ImageManager imageManager;
    FaceFeatureManager featureManager;
    NoddingOffDetector noddingOffDetector;
    GazeDetector gazeDetector;
    YawningDetector yawningDetector;
    HeadRotationDetector headRotationDetector;

    float gazeScore , percloseScore , noddingOffLevel , yawningScore ;
    vector<float> headRotAngles;
    bool alertStatus;
};

