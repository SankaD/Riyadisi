#include "FaceDetector.h"

using namespace std;
using namespace cv;

FaceDetector::FaceDetector ( void )
{
    faceCascadeName = "Resources/Cascades/HaarCascades/haarcascade_frontalface_alt.xml";
    Detector ( faceCascadeName );
}
