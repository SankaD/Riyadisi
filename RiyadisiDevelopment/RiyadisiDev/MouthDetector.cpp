
#include "MouthDetector.h"



//MouthDetector::MouthDetector ( void ) :
//    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_mouth.xml" )
//{
//	scale = 1.5;
//	minSize = Size(75, 50);
//}

MouthDetector::MouthDetector ( ) 
{ 

}

MouthDetector::~MouthDetector()
{

}

vector<vector<Point>> MouthDetector::getContourMap( Mat image) {
	int cannyThreshold = 10;
    float cannyRatio = 3;
	vector<vector<Point>> contours;

	threshold ( image, image, 125, 255, CV_THRESH_BINARY );
    //imshow ( "mouth threshold", image );

    Mat erodeElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 1, 1 ) );
    erode ( image, image, erodeElement );
	//imshow ( "transformed image", mouthROITemp );

    Canny ( image, image, cannyThreshold, cannyThreshold * cannyRatio, 3, true );
    findContours ( image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
    //drawContours ( mouthROITemp, contours, -1, Scalar ( 255, 255, 255 ), -1 );

	return contours;
}

Rect MouthDetector::detect( Mat mouthROI )
{
	Rect mouth;
	vector<vector<Point>> contours = getContourMap( mouthROI.clone() );
	
 //   double maxArea = 0;
	//int maxAreaIndex = -1;
 //   for ( int i = 0; i < contours.size(); i++ ) {	//find the maximum mouth region 
 //       double area = contourArea ( contours[i] );
	//	float radiusTemp;
	//	Point2f centerTemp;

 //       minEnclosingCircle ( contours[i], centerTemp, radiusTemp );
 //       if ( area > maxArea
	//			&& centerTemp.x < mouthROI.cols * 0.75
 //               && centerTemp.x > mouthROI.cols * 0.25 ) {
	//				maxAreaIndex = i;
	//				maxArea = area;
	//	}
 //   }

	//if(maxAreaIndex > 0 ){
		vector<int> mouthContourIndices;
		
		/*mouthContourIndices.push_back(maxAreaIndex);
		Rect maxAreaRect = minEnclosingRectangle( contours[maxAreaIndex] );
		Point maxAreaCenter( (maxAreaRect.x + maxAreaRect.width/2), (maxAreaRect.y + maxAreaRect.height/2) );
		rectangle(mouthROI, maxAreaRect, Scalar(0,255,0), 4, 8);*/

		for ( int i = 0; i < contours.size(); i++ ) { 
			Rect rectTemp = minEnclosingRectangle( contours[i] );
			Point centerTemp( (rectTemp.x + rectTemp.width/2), (rectTemp.y + rectTemp.height/2) );
			int mouthArea = rectTemp.width * rectTemp.height;
			int imageArea = mouthROI.rows * mouthROI.cols;

			if(centerTemp.x < mouthROI.cols * 0.75 
				&& centerTemp.x > mouthROI.cols * 0.25
				&& centerTemp.y < mouthROI.rows * 0.6
				&& centerTemp.y > mouthROI.rows * 0.1
				&& mouthArea > imageArea/100 
				&& mouthArea < imageArea/5) {
					mouthContourIndices.push_back(i);
					
			}
			//rectangle(test, rectTemp, Scalar(0,255,0), 1, 8);
		}
		
		vector<Point> mouthPoints;
		if( mouthContourIndices.size() > 0) {
			for(int i=0; i<mouthContourIndices.size(); i++)
				for(int j=0; j<contours[mouthContourIndices[i]].size(); j++)
					mouthPoints.push_back(contours[mouthContourIndices[i]][j]);
		}
		
		mouth = minEnclosingRectangle( mouthPoints );
		//imshow ( "mouth", mouthROI );
		//cout << "Mouth Area : " << mouth.area() << endl;
	//}
		imshow("mouth-test", mouthROI);
	
	return mouth;
}

Rect MouthDetector::minEnclosingRectangle( vector<Point> data ) {
	int minX = numeric_limits<int>::max(), 
		maxX = 0, 
		minY = numeric_limits<int>::max(), 
		maxY = 0;
	
	for(int i=0; i<data.size(); i++) {
		if(data[i].x < minX) minX = data[i].x;
		if(data[i].x > maxX) maxX = data[i].x;
		if(data[i].y < minY) minY = data[i].y;
		if(data[i].y > maxY) maxY = data[i].y;
	}
	return Rect(minX, minY, maxX-minX, maxY-minY);
}

void MouthDetector::drawTemplate ( vector<Mat> imageList )
{
	mouthTemplate = Mat::zeros(imageList[0].size(), CV_8U);
	vector<vector<Point>> contours;
	Mat image;
	int T = imageList.size() * 0.2, size;

	for(int i=0; i<imageList.size(); i++) {
		image = imageList[i].clone();
		size = image.rows * image.cols;
		contours = getContourMap( image );
		
		for(int j=0; j<contours.size(); j++) {
			double area = contours[j].size();

			if( area > (size/1000) ) {
				for(int k=0; k<contours[j].size(); k++) {
					mouthTemplate.at<uchar>(contours[j][k].y, contours[j][k].x)++;
				}
			}
		}
		
	}

	threshold ( mouthTemplate, mouthTemplate, T, 255, CV_THRESH_BINARY_INV );
	imwrite("output/template/mouth_template.jpg", mouthTemplate);
	//imshow("mouth", mouthTemplate);
}


