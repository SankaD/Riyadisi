#pragma once
#include <opencv2\objdetect\objdetect.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

#define FEATURE_ARRAY_LENGTH  30

///<summary>
///Represents a general feature used in the feature managing in the system.
///The class should always use relative coordinates with its container Feature instance.
///</summary>
class Feature {
private:
    Rect featureRect;
    float rotation;
    bool available;
public:
    ///<summary>
    ///Used to get the location of the feature
    ///</summary>
    ///<returns>The location of the feature</returns>
    Rect getFeatureRect();

    ///<summary>
    ///Gets the rotation of the feature
    ///</summary>
    ///<returns>Rotation</returns>
    float getRotation();
    void setRotation ( float rotation );

    ///<summary>
    ///Checks weather the feature is available
    ///</summary>
    bool isAvailable();

    void setAvailable ( bool availability );
    void setFeatureRect ( Rect featureRect );
};
