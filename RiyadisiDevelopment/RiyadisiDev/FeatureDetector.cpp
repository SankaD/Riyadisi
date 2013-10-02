#include "FeatureDetector.h";

using namespace cv;
using namespace std;

Rect detectFeature ( Mat sourceFrame, Rect featureLocation, Mat testImage, Rect regionOfInterest )
{
    int minHessian = 100;
    SurfFeatureDetector detector ( minHessian );

    vector<KeyPoint> keypoints1, keypoints2;

    detector.detect ( sourceFrame ( featureLocation ), keypoints1 );
    detector.detect ( testImage ( regionOfInterest ), keypoints2 );



    throw new exception ( "Not implemented yet" );
}
