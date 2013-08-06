
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Gaze.h"

using namespace std;
using namespace cv;

class GazeDetector {
public:
    GazeDetector ( void );
    ~GazeDetector ( void );
    Gaze detectGaze ( std::vector<Rect> eyes );
};

GazeDetector::GazeDetector ( void )
{
}


GazeDetector::~GazeDetector ( void )
{
}


Gaze GazeDetector::detectGaze ( vector<Rect> eyes  )
{
    Gaze gaze;

    throw exception ( "Not implemented yet" );

    return gaze;
}