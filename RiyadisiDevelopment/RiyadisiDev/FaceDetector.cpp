#include "FaceDetector.h"

Rect FaceDetector::detect ( Mat frame )
{
    vector<Rect> features;
	
	// downsampling for increased performance
	donwsampleConst = 4;
	Mat downsampledImage = downsampleImage( frame.clone(), donwsampleConst );
	
	features = fontalFaceDetector.detect( downsampledImage );
	if( features.size() == 0 ) {
		features = profileFaceDetector.detect( downsampledImage );
	}
	if( features.size() == 0 ) {
		Mat flippedFrame = Mat::zeros( frame.size(), frame.type() );
		flip( downsampledImage, flippedFrame, 1);
		features = profileFaceDetector.detect( flippedFrame );

		for(int i=0; i<features.size(); i++) {
			features[i].x = frame.cols - ( features[i].x + features[i].width );
		}
	}
	/*if( features.size() == 0 ) {
		Mat rotatedFrame = Mat::zeros( frame.size(), frame.type() );
		int angle = -60;

		while( angle < 90 ){
			if( angle == 0 ) {
				angle += 30;
				continue;
			}

			Point center( frame.cols/2, frame.rows/2 );
			Mat rotM = getRotationMatrix2D( center, angle, 1.0 );
			wrapAffine( frame, rotatedFrame, rotM, frame.size() );

			features = profileFaceDetector.detect( rotatedFrame );
			for(int i=0; i<features.size(); i++) {
				features[i].x = rotM.at<double>(0,0)*features[i].x + rotM.at<double>(0,1)*features[i].y + rotM.at<double>(0,2);
				features[i].y = rotM.at<double>(1,0)*features[i].x + rotM.at<double>(1,1)*features[i].y + rotM.at<double>(1,2);           
			} 
			angle += 30;
		}
	}*/

	return optimizeDetection( features )[0];
}

vector<Rect> FaceDetector::optimizeDetection ( vector<Rect> data )
{
    vector<Rect> optimizedResults;
	vector<Point> centerPoints;
	Rect temp;

	for(int i=0; i<data.size(); i++) {
		centerPoints.push_back(Point( (data[i].x + data[i].width/2), (data[i].y + data[i].height/2) ));
	}

	for(int i=0; i<data.size(); i++) {
		temp = data[i];
		for(int j=0; j<centerPoints.size(); j++) {
			if( data[i].x < centerPoints[j].x && (data[i].x + data[i].width ) > centerPoints[j].x ||
				data[i].y < centerPoints[j].y && (data[i].y + data[i].height ) > centerPoints[j].y ) {
					if( data[j].area() < temp.area() )
						temp = data[j];
			}
		}

		// rescaling into the original size
        temp.x *= donwsampleConst ;
        temp.y *= donwsampleConst ;
        temp.height *= donwsampleConst;
        temp.width *= donwsampleConst;

		optimizedResults.push_back( temp );
	}

	if( optimizedResults.size() == 0 )
		optimizedResults.push_back( Rect( 0, 0, 0, 0) );

    return optimizedResults;
}

Mat FaceDetector::downsampleImage( Mat src, int factor ) 
{
	for ( int i = 0; i < factor / 2; i++ ) {
        pyrDown ( src, src, Size ( ( src.cols  ) / 2, ( src.rows  ) / 2 ) );
    }

	return src;
}

FaceDetector::FaceDetector ( void )
{
	donwsampleConst = 1;
}

FaceDetector::~FaceDetector ( void )
{

}
