#pragma once
//opencv includes
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

//standard c++ includes
#include <iostream>
#include <time.h>

//project related includes
#include "MainProgram.h"
#include "FaceFeatureManager.h"
#include "NoddingOffDetector.h"
#include "GazeDetector.h"
#include "ImageManager.h"
#include "Utility.h"
#include "DecisionEngine.h"
#include "Log.h"


class MainProgram {
public:
    MainProgram();
    const static short int WAIT_PERIOD_PER_FRAME;

    ///<summary>
    ///Main function of the program
    ///</summary>
    void run();
    void trainingRun();
    void processImage();
private:
    bool isAlertOn;
    ImageManager imageManager;
    FaceFeatureManager featureManager;
    NoddingOffDetector noddingOffDetector;
    GazeDetector gazeDetector;
    Mat frame, grayFrame;
    long int frameCount;// for keeping the frame count
    int key;// for the key pressed by the user
    time_t systemTime;// used to keep the time in the system
    bool firstRun;
    bool trainingMode;
    DecisionEngine decisionEngine;
};