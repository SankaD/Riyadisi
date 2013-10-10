
#include "EyeDetector.h"

using namespace std;
using namespace cv;

EyeDetector::EyeDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_lefteye.xml" )
{
	scale = 1.5;
	minSize = Size(30, 30);
	//downsampling??haarcascade_eye_tree_eyeglasses//haarcascade_mcs_lefteye
}


vector<Rect> EyeDetector::optimizeDetection ( vector<Rect> data )
{
    vector<Rect> optimizedResults;
    // if the number of eyes detected within a face is greater than 2
    if ( data.size() > 2 ) {
        
    }
    return optimizedResults;
}

EyeDetector::~EyeDetector()
{

}


