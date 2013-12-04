#include "Detector.h"

std::vector<Rect> Detector::detect ( Mat frame ) {
    std::vector<Rect> features;
    Mat downsampledImage =  frame.clone();
    equalizeHist ( downsampledImage, downsampledImage );

    //down sampling
    for ( int i = 0; i < donwsampleConst / 2; i++ ) {
        pyrDown ( downsampledImage, downsampledImage, Size ( ( downsampledImage.cols  ) / 2, ( downsampledImage.rows  ) / 2 ) );
    }
    cascade.detectMultiScale ( downsampledImage, features, scale, minNeighbors, flags | CV_HAAR_SCALE_IMAGE, minSize, maxSize );

    // rescale into the original size
	for ( int i = 0; i < features.size(); i++ ) 
	{
        features[i].x *= donwsampleConst ;
        features[i].y *= donwsampleConst ;
        features[i].height *= donwsampleConst;
        features[i].width *= donwsampleConst;
    }

    return features;
}

Detector::Detector ( string cascadeName ) {
    this->cascadeName = cascadeName;
    if ( !cascade.load ( cascadeName ) ) {
        printf ( "--(!)-- Error loading cascade : %s", cascadeName );
        exit ( -1 );
    }
}

void Detector::setMinSize ( Size size )
{
	this->minSize = size;
}

Detector::Detector ( void ) {

}

Detector::~Detector ( void ) {

}
