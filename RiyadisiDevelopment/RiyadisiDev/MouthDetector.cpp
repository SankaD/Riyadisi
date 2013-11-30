
#include "MouthDetector.h"



//MouthDetector::MouthDetector ( void ) :
//    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_mouth.xml" )
//{
//	scale = 1.5;
//	minSize = Size(75, 50);
//}

MouthDetector::MouthDetector ( void ) { 
	mouthTemplate = Mat::zeros(Size(60,40), CV_8U);
	erodeElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 1, 1 ) );
	dilateElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 1, 1 ) );
}

vector<vector<Point>> MouthDetector::getContourMap( Mat image) {
	Scalar mu, sigma;
	meanStdDev( image, mu, sigma );
	int upperThreshold = (mu.val[0] + sigma.val[0]), lowerThreshold = (mu.val[0] - sigma.val[0]), binaryThresold;
    float cannyRatio = 3;
	vector<vector<Point>> contours;

	binaryThresold = calculateThreshold( image );
	threshold(image, image, binaryThresold, 255, THRESH_BINARY );
	//adaptiveThreshold(image, image, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 0);
    
	erode ( image, image, erodeElement );
    dilate( image, image, dilateElement );
	
	//imshow ( "transformed image", image );

	Canny ( image, image, lowerThreshold, upperThreshold, 3, true );
    findContours ( image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
	
	return contours;
}

Rect MouthDetector::detect( Mat mouthROI )
{
	Rect mouth;
	Mat temp = mouthROI.clone();
	/*, tempTemplate;
	resize(mouthTemplate, tempTemplate, mouthROI.size(), 0, 0, 1 );
	
	int binaryThresold = calculateThreshold( temp );
	threshold(temp, temp, binaryThresold, 255, THRESH_BINARY );
	erode ( temp, temp, erodeElement );

	binaryThresold = calculateThreshold( tempTemplate );
	threshold(tempTemplate, tempTemplate, binaryThresold, 255, THRESH_BINARY );
	dilate( tempTemplate, tempTemplate, dilateElement );*/
	
	//for(int i=0; i < mouthROI.cols; i++) {
	//	for(int j=0; j < mouthROI.rows; j++) {
	//		if( temp.at<uchar>(j, i) == 0 && tempTemplate.at<uchar>(j, i) == 0 )
	//			temp.at<uchar>(j, i) = 255;
	//		/*if( i < mouthROI.cols * 0.2 || i > mouthROI.cols * 0.8 || j > mouthROI.rows * 0.7 || j < mouthROI.rows * 0.1 )
	//			temp.at<uchar>(j, i) = 255;*/
	//	} 
	//}
	//imshow ( "transformed image", temp );

	vector<vector<Point>> contours = getContourMap( temp );
	vector<int> mouthContourIndices;
			
	for ( int i = 0; i < contours.size(); i++ ) { 
		Rect rectTemp = minEnclosingRectangle( contours[i] );
		Point centerTemp( (rectTemp.x + rectTemp.width/2), (rectTemp.y + rectTemp.height/2) );
		int mouthArea = rectTemp.width * rectTemp.height;
		int imageArea = mouthROI.rows * mouthROI.cols;

		if(centerTemp.x < mouthROI.cols * 0.75 
			&& centerTemp.x > mouthROI.cols * 0.25
			&& centerTemp.y < mouthROI.rows * 0.75
			&& centerTemp.y > mouthROI.rows * 0.25)
			//&& mouthArea > imageArea/100)
		{
				mouthContourIndices.push_back(i);
		}
		//rectangle(mouthROI, rectTemp, Scalar(0,255,0), 1, 8);
	}
		
	vector<Point> mouthPoints;
	if( mouthContourIndices.size() > 0) {
		for(int i=0; i<mouthContourIndices.size(); i++)
			for(int j=0; j<contours[mouthContourIndices[i]].size(); j++)
				mouthPoints.push_back(contours[mouthContourIndices[i]][j]);
	}
		
	mouth = minEnclosingRectangle( mouthPoints );
	
	return mouth;
}

Rect MouthDetector::minEnclosingRectangle( vector<Point> data ) {
	int minX = numeric_limits<int>::max(), 
		maxX = 0, 
		minY = numeric_limits<int>::max(), 
		maxY = 0;
	Rect ans(0,0,0,0);
	
	for(int i=0; i<data.size(); i++) {
		if(data[i].x < minX) minX = data[i].x;
		if(data[i].x > maxX) maxX = data[i].x;
		if(data[i].y < minY) minY = data[i].y;
		if(data[i].y > maxY) maxY = data[i].y;
	}

	if( minX < numeric_limits<int>::max() && minY < numeric_limits<int>::max() || maxX > 0 || maxY > 0 )
		ans = Rect(minX, minY, maxX-minX, maxY-minY);

	return ans;
}


void MouthDetector::updateTemplate ( Mat image )
{
	float alpha = 0.2;
	Mat mouthROI = image.clone();
	resize(	mouthROI, mouthROI, Size(60,40), 0, 0, 1);	
			
	for(int i=0; i < mouthROI.cols; i++) {
		for(int j=0; j < mouthROI.rows; j++) {
			mouthTemplate.at<uchar>(j, i) += ( mouthROI.at<uchar>(j, i) - mouthTemplate.at<uchar>(j, i) ) * alpha;
		}
	}
	imwrite("Testing/Images/mouth_template.jpg", mouthTemplate);
}

int MouthDetector::calculateThreshold( Mat image ) 
{
	int histogram[256];
	int count = image.cols * image.rows, sum = 0, threshold;

	//initialize the array
	for(int i=0; i<256; i++)
	{
		histogram[i] = 0;
	}
	
	//histogram calculation
	for(int i=0; i<image.cols; i++)
	{
		for( int j=0; j<image.rows; j++) 
		{
			histogram[(int)image.at<uchar>(j,i)]++;
		}
	}

	//find the threshold
	for(int i=0; i<256; i++)
	{
		if( sum > count/4 ) {
			threshold = i;
			break;
		}
		sum += histogram[i];
	}
	
	return threshold;
}



MouthDetector::~MouthDetector()
{

}


