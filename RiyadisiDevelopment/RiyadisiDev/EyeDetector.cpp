
#include "EyeDetector.h"

using namespace std;
using namespace cv;

EyeDetector::EyeDetector ( void )
{
    eyeCascadeName = "Resources/Cascades/HaarCascades/haarcascade_eye_tree_eyeglasses.xml";
    Detector ( eyeCascadeName );
}