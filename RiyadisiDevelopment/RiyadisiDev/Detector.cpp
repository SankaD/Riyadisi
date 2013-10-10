#include "Detector.h"

std::vector<Rect> Detector::detect ( Mat frame )
{
    std::vector<Rect> features;
	
	cascade.detectMultiScale ( frame, features, scale, 2, 0 | CV_HAAR_SCALE_IMAGE, minSize );

    return features;
}

Detector::Detector ( string cascadeName )
{
    this->cascadeName = cascadeName;
    if ( !cascade.load ( cascadeName ) ) {
        printf ( "--(!)-- Error loading cascade : %s", cascadeName );
        exit ( -1 );
    }
}

Detector::Detector ( void )
{

}

Detector::~Detector ( void )
{

}
