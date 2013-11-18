#include "Detector.h"

std::vector<Rect> Detector::detect ( Mat frame ) {
    std::vector<Rect> features;

    cascade.detectMultiScale ( frame, features, scale, minNeighbors, flags | CV_HAAR_SCALE_IMAGE, minSize, maxSize );
	
	return features;
}

Detector::Detector ( string cascadeName ) {
    this->cascadeName = cascadeName;
    if ( !cascade.load ( cascadeName ) ) {
        printf ( "--(!)-- Error loading cascade : %s", cascadeName );
        exit ( -1 );
    }
}

Detector::Detector ( void ) {
    flags = 0;
    minNeighbors = 3;
    //scale = 1.1;
}

Detector::~Detector ( void ) {

}
