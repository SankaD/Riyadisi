
#include "MouthDetector.h"



//MouthDetector::MouthDetector ( void ) :
//    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_mouth.xml" )
//{
//	scale = 1.5;
//	minSize = Size(75, 50);
//}

MouthDetector::MouthDetector ( void ) {
    mouthTemplate = Mat::zeros ( Size ( 60, 40 ), CV_8U );
    erodeElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 1, 1 ) );
    dilateElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 1, 1 ) );
	timer = 0;
}

vector<vector<Point>> MouthDetector::getContourMap ( Mat image ) {
    Scalar mu, sigma;
    meanStdDev ( image, mu, sigma );
    int upperThreshold = ( mu.val[0] + sigma.val[0] ), lowerThreshold = ( mu.val[0] - sigma.val[0] );
    float cannyRatio = 3;
    vector<vector<Point>> contours;
	Mat im = image.clone();
			
    Canny ( im, im, lowerThreshold, upperThreshold, 3, true );
    findContours ( im, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );

    return contours;
}

void MouthDetector::applyMorphOperations ( Mat* image ) 
{
	int binaryThresold;

	binaryThresold = calculateThreshold ( *image );
    threshold ( *image, *image, binaryThresold, 255, THRESH_BINARY );
    //adaptiveThreshold(image, image, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 0);
	
	erode ( *image, *image, erodeElement );
    dilate ( *image, *image, dilateElement );
	//imshow ( "transformed image", image );
}

Rect MouthDetector::detect ( Mat mouthROI ) {
    Rect mouth(0, 0, 0, 0);
	Mat temp = mouthROI.clone(), tempTemplate = mouthTemplate.clone();

	if( timer < 30 )
	{
		updateTemplate ( mouthROI );
		timer++;
	}

	resize(tempTemplate, tempTemplate, mouthROI.size() );
	applyMorphOperations( &tempTemplate );
	vector<vector<Point>> contours1 = getContourMap( tempTemplate );
	applyMorphOperations( &temp );
	vector<vector<Point>> contours2 = getContourMap( temp );
	imshow ( "Template", tempTemplate );
	imshow ( "mouth", temp );

	for(int i=0; i<temp.rows; i++)
		for(int j=0; j<temp.cols; j++)
		{
			if( (int)tempTemplate.at<uchar>(i,j) == 0 && (int)temp.at<uchar>(i,j)== 0 )
				temp.at<uchar>(i,j)= 255;
		}
	imshow ( "Testing/Images/result.jpg", temp );

    vector<vector<Point>> contours = getContourMap ( temp );
    vector<int> mouthContourIndices;
	vector<Point> mouthPoints;
	int maxAreaIndex = 0, area, maxArea = 0;

	if( contours.size() > 0 )
	{
		maxArea = contourArea( contours[0] );
	}

    for ( int i = 1; i < contours.size(); i++ ) {
        /*Rect rectTemp = minEnclosingRectangle ( contours[i] );
        Point centerTemp ( ( rectTemp.x + rectTemp.width / 2 ), ( rectTemp.y + rectTemp.height / 2 ) );
        int mouthArea = rectTemp.width * rectTemp.height;
        int imageArea = mouthROI.rows * mouthROI.cols;*/

		area = contourArea( contours[i] );
		Rect rectTemp = boundingRect ( contours[i] );
        Point centerTemp ( ( rectTemp.x + rectTemp.width / 2 ), ( rectTemp.y + rectTemp.height / 2 ) );

        if ( centerTemp.x < mouthROI.cols * 0.75
                && centerTemp.x > mouthROI.cols * 0.25
                && centerTemp.y < mouthROI.rows * 0.75
                && centerTemp.y > mouthROI.rows * 0.25 )
            //&& mouthArea > imageArea/100)
        {
            //mouthContourIndices.push_back ( i );
			if( area > maxArea )
			{
				maxAreaIndex = i;
				maxArea = area;
			}
		}
        //rectangle(mouthROI, rectTemp, Scalar(0,255,0), 1, 8);
	}

   /*if ( mouthContourIndices.size() > 0 ) {
        for ( int i = 0; i < mouthContourIndices.size(); i++ )
            for ( int j = 0; j < contours[mouthContourIndices[i]].size(); j++ )
            { 
				mouthPoints.push_back ( contours[mouthContourIndices[i]][j] ); 
			}
    }*/

	if( contours.size() > 0)
		mouth = boundingRect ( contours[maxAreaIndex] );
    //mouth = minEnclosingRectangle ( mouthPoints );

    return mouth;
}

Rect MouthDetector::minEnclosingRectangle ( vector<Point> data ) {
    int minX = numeric_limits<int>::max(),
        maxX = 0,
        minY = numeric_limits<int>::max(),
        maxY = 0;
    Rect ans ( 0, 0, 0, 0 );

    for ( int i = 0; i < data.size(); i++ ) {
        if ( data[i].x < minX ) { minX = data[i].x; }
        if ( data[i].x > maxX ) { maxX = data[i].x; }
        if ( data[i].y < minY ) { minY = data[i].y; }
        if ( data[i].y > maxY ) { maxY = data[i].y; }
    }

    if ( minX < numeric_limits<int>::max() && minY < numeric_limits<int>::max() || maxX > 0 || maxY > 0 )
    { ans = Rect ( minX, minY, maxX - minX, maxY - minY ); }

    return ans;
}


void MouthDetector::updateTemplate ( Mat image ) {
    float alpha = 0.2;
    Mat mouthROI = image.clone();
    resize (	mouthROI, mouthROI, Size ( 60, 40 ), 0, 0, 1 );

    for ( int i = 0; i < mouthROI.cols; i++ ) {
        for ( int j = 0; j < mouthROI.rows; j++ ) {
            mouthTemplate.at<uchar> ( j, i ) += ( mouthROI.at<uchar> ( j, i ) - mouthTemplate.at<uchar> ( j, i ) ) * alpha;
        }
    }
    imwrite ( "Testing/Images/mouth_template.jpg", mouthTemplate );
}

int MouthDetector::calculateThreshold ( Mat image ) {
    int histogram[256];
    int count = image.cols * image.rows, sum = 0, threshold;

    //initialize the array
    for ( int i = 0; i < 256; i++ ) {
        histogram[i] = 0;
    }

    //histogram calculation
    for ( int i = 0; i < image.cols; i++ ) {
        for ( int j = 0; j < image.rows; j++ ) {
            histogram[ ( int ) image.at<uchar> ( j, i )]++;
        }
    }

    //find the threshold
    for ( int i = 0; i < 256; i++ ) {
        if ( sum > count / 4 ) {
            threshold = i;
            break;
        }
        sum += histogram[i];
    }

    return threshold;
}



MouthDetector::~MouthDetector() {

}


