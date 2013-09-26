#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\nonfree\features2d.hpp>

using namespace cv;
using namespace std;

///<summary>
///Used for tracking features between 2 given images.
///</summary>
class FeatureDetector {
public:
    ///<summary>
    ///Tracks a given feature from one image to the other
    ///</summary>
    ///<param name="sourceFrame">Source image where the feature is located</param>
    ///<param name="featureLocation">Location of the feature in the image</param>
    ///<param name="testImage">Image which the feature is needed to be tracked</param>
    ///<param name="regionOfInterest">Region where the feature should be searched for</param>
    ///<returns>The location of the feature if found or an invalid (-1,-1,-1,-1) location if not.</returns>
    Rect detectFeature ( Mat sourceFrame, Rect featureLocation, Mat testImage, Mat regionOfInterest );
};