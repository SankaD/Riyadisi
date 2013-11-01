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


class MainProgram {
public:
    const static short int WAIT_PERIOD_PER_FRAME;
    bool isAlertOn;

    MainProgram();
    ///<summary>
    ///Main function of the program
    ///</summary>
    void run();
private:

};