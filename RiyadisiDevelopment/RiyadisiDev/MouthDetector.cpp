
#include "MouthDetector.h"

using namespace std;
using namespace cv;

MouthDetector::MouthDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_mouth.xml" )
{
	scale = 1.5;
	minSize = Size(75, 50);
}

vector<Rect> MouthDetector::optimizeDetection ( vector<Rect> data )
{
    vector<Rect> optimizedResults;
    // if the number of eyes detected within a face is greater than 2
    if ( data.size() > 2 ) {
        
    }
    return optimizedResults;
}

MouthDetector::~MouthDetector()
{

}


