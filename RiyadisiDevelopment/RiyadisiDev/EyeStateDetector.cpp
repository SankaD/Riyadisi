#include "EyeStateDetector.h"


Mat training_mat ( 1, 60 * 40, CV_32FC1 );

EyeStateDetector::EyeStateDetector ( void ) {
    for ( int i = 0; i < FEATURE_ARRAY_LENGTH; i++ ) {
        scores[i] = 0;
    }
	currentIndex=0;
}

EyeStateDetector::~EyeStateDetector ( void ) {
}


float EyeStateDetector:: calculateEyeState ( Mat eye, FileStorage fs ) {


    double result = 0;
    processImage ( eye );


    PCA pca; // declare pca variable
    // FileStorage fs("eye_state_pca",FileStorage::READ); //load the pca model of trained data
    Mat trainbpca(200,2400,CV_32FC1);
  // fs["bpca"] >> trainbpca;
	 fs["sobel_bpca"] >> trainbpca;
   fs.release();

    Mat afterPca ( 1, 200, CV_32FC1 );

    //pca.project ( training_mat, afterPca ); // project eye image to pca space of training data
	afterPca=training_mat*(trainbpca.t());
    CvSVM SVM;
  //  SVM.load ( "eye_state_svm" ); //loading trained svm

	SVM.load ( "eye_state_sobel_svm" ); //loading trained svm

    if ( SVM.predict ( afterPca ) == 0 ) {
        // cout << "open eye" << endl;
    } else {
        //  cout << "close eye" << endl;
    }

    return SVM.predict ( afterPca );

}

void EyeStateDetector:: processImage ( Mat image ) {



    resize ( image, image, Size ( 60, 40 ) ); //resize to standard size

    if ( image.channels() == 3 )
    { cvtColor ( image, image, CV_BGR2GRAY ); } //convert to greyscale


    equalizeHist ( image, image ); //histogram equalization

    blur ( image, image, Size ( 3, 3 ) ); //gaussian blur
  //  Canny ( image, image, 50, 300, 3 );

	//do sobel
		int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    /// Gradient X
	Mat grad_x,grad_y,abs_grad_x,abs_grad_y;
    cv::Sobel( image, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );   
    cv::convertScaleAbs( grad_x, abs_grad_x );
    
    /// Gradient Y  
    cv::Sobel( image, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );   
    cv::convertScaleAbs( grad_y, abs_grad_y );
    
    /// Total Gradient (approximate)
    cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, image );
	 /*Scalar mu, sigma;
meanStdDev(image, mu, sigma);*/

double minVal; 
        double maxVal; 
        Point minLoc; 
        Point maxLoc;
		minMaxLoc( image, &minVal, &maxVal, &minLoc, &maxLoc );


threshold(image,image, maxVal*0.4, 255, THRESH_BINARY);
	//end sobel

    normalize ( image, image, 0, 255, NORM_MINMAX, CV_8UC1 ); // normalize to have 0-1

    /*int ii=0;
    		for (int i = 0; i<image.rows; i++) {
    	for (int j = 0; j < image.cols; j++) {
    		training_mat.at<float>(0,ii++) = image.at<uchar>(i,j);
    	}
    }*/

    Mat xi = training_mat.row ( 0 );

    if ( image.isContinuous() )
    { image.reshape ( 1, 1 ).convertTo ( xi, CV_32FC1, 1, 0 ); }
    else
    { image.clone().reshape ( 1, 1 ).convertTo ( xi, CV_32FC1, 1, 0 ); }


}

float EyeStateDetector::getPerclosScore( FaceFeature *faceFeature, String eyeType, FileStorage fs) 
{
	Mat eye;
	double eyestate=0;
	if( eyeType == "left" ) eye = faceFeature->getImage()( faceFeature->getLeftEye()->getFeatureRect() );
	else eye = faceFeature->getImage()( faceFeature->getRightEye()->getFeatureRect() );

	currentIndex = ( currentIndex + 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH;
    float score = 0;
    
	eyestate= calculateEyeState ( eye, fs );
	
	scores[currentIndex] =eyestate;
	if(scores[currentIndex]==0){
		score = scores[ ( currentIndex - 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH] * 0.8 + scores[currentIndex] * 0.2 ;}
	else score = scores[ ( currentIndex - 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH] * 0.6 + scores[currentIndex] * 0.4 ;
    
	scores[currentIndex] = score;

	if( eyeType == "left" )
		faceFeature->getLeftEye()->setEyeState( (eyestate == 0.0)? EyeState::OPEN: EyeState::CLOSE );
	else
		faceFeature->getRightEye()->setEyeState( (eyestate == 0.0)? EyeState::OPEN: EyeState::CLOSE );

    return abs ( score );
	//return abs ( scores[currentIndex] );
}