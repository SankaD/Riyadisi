#include "FaceDetector.h"

Rect FaceDetector::detect ( FaceFeature* faceFeature )
{
    vector<Rect> features;
	Mat frame = faceFeature->getImage();
	
	//frontal face detection
	features = fontalFaceDetector.detect( frame );
	if( features.size() != 0 ) 
	{
		faceFeature->setOrientation( Orientation::FRONTAL );
	}
	else
	{
		//left profile face detection
		features = profileFaceDetector.detect( frame );

		if( features.size() != 0 ) 
		{
			faceFeature->setOrientation( Orientation::LEFT_PROFILE );
		}
		else
		{
			//right profile face detection
			Mat flippedFrame = Mat::zeros( frame.size(), frame.type() );
			flip( frame, flippedFrame, 1);
			features = profileFaceDetector.detect( flippedFrame );

			for(int i=0; i<features.size(); i++) 
			{
				features[i].x = frame.cols - ( features[i].x + features[i].width );
			}

			
			if( features.size() != 0 ) 
			{
				faceFeature->setOrientation( Orientation::RIGHT_PROFILE );
			}
			else
			{
				//rotated face detection
				Mat rotatedFrame = Mat::zeros( frame.size(), frame.type() );
				int angle = -60;

				do 
				{
					if( angle == 0 ) 
					{
						angle += 30;
						continue;
					}

					Point center( frame.cols/2, frame.rows/2 );
					//rotation matrix
					Mat rotM = getRotationMatrix2D( center, angle, 1.0 );
					cv::warpAffine( frame, rotatedFrame, rotM, frame.size() );
			
					features = fontalFaceDetector.detect( rotatedFrame );
					Mat rotTM = rotM.t();
					cout<<rotTM<<endl;
					for(int i=0; i<features.size(); i++) 
					{
						features[i].x = rotM.at<double>(0,0)*features[i].x + rotM.at<double>(0,1)*features[i].y + rotM.at<double>(0,2);
						features[i].y = rotM.at<double>(1,0)*features[i].x + rotM.at<double>(1,1)*features[i].y + rotM.at<double>(1,2);           
					} 
					angle += 30;

				} while ( angle < 90 && features.size() == 0 );

				/*if(features.size() > 0 ){
					rectangle(rotatedFrame, features[0], Scalar(0,255,0), 1,8);
					imshow("rot_test", rotatedFrame);
				}*/
				if( features.size() != 0 ) 
				{
					faceFeature->setOrientation( Orientation::FRONTAL );
				}
			}//end of rotated face detection
		}//end of right profile face detection
	}//end of left profile face detection

	return optimizeDetection( features )[0];
}

vector<Rect> FaceDetector::optimizeDetection ( vector<Rect> data )
{
    vector<Rect> optimizedResults;
	vector<Point> centerPoints;
	Rect temp;

	//calculate center points
	for(int i=0; i<data.size(); i++) 
	{
		centerPoints.push_back(Point( (data[i].x + data[i].width/2), (data[i].y + data[i].height/2) ));
	}

	//find the smallest fitting rectangle
	for(int i=0; i<data.size(); i++) 
	{
		temp = data[i];
		for(int j=0; j<centerPoints.size(); j++) 
		{
			if( data[i].x < centerPoints[j].x && (data[i].x + data[i].width ) > centerPoints[j].x ||
				data[i].y < centerPoints[j].y && (data[i].y + data[i].height ) > centerPoints[j].y ) 
			{
					if( data[j].area() < temp.area() )
						temp = data[j];
			}
		}
		optimizedResults.push_back( temp );
	}

	if( optimizedResults.size() == 0 )
		optimizedResults.push_back( Rect( 0, 0, 0, 0) );

    return optimizedResults;
}

Mat FaceDetector::downsampleImage( Mat src, int factor ) 
{
	for ( int i = 0; i < factor / 2; i++ ) 
	{
        pyrDown ( src, src, Size ( ( src.cols  ) / 2, ( src.rows  ) / 2 ) );
    }

	return src;
}

FaceDetector::FaceDetector ( void )
{
	
}

FaceDetector::~FaceDetector ( void )
{

}
