#include "HeadRotationDetector.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

HeadRotationDetector::HeadRotationDetector ( void )
{
    
}


HeadRotationDetector::~HeadRotationDetector ( void )
{
}

void HeadRotationDetector::setStartPoints ( Point p1, Point p2, Point p3 ){
	pl = p1;
	pr = p2;
	pn = p3;
}


vector<float> HeadRotationDetector::calculateRotation ( FaceFeature *faceFeature ){

	float e1, e2, e3, e4, e5, e6;
	double E = 1E+37, e;
	float thetaF, phiF, shiF;
	Point fl = faceFeature->getLeftEye()->getCenterPoint(),
		fr = faceFeature->getRightEye()->getCenterPoint(),
		fn = faceFeature->getNose()->getCenterPoint();
	vector<float> angles;
		
	for(float theta = -85; theta <= 85; theta=theta+5){
		for(float phi = -85; phi <= 85; phi=phi+5){
			for(float shi = -85; shi <= 85; shi=shi+5){

				e1 = cos(radian(phi))* cos(radian(theta)) * pl.x;
				e1 += ( cos(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) - sin(radian(phi))  * cos(radian(shi)) ) * pl.y;
				e1 -= fl.x;

				e2 = sin(radian(phi)) * cos(radian(theta)) * pl.x;
				e2 += ( sin(radian(phi)) * sin(radian(theta)) * sin(shi) + cos(radian(phi))  * cos(radian(shi)) ) * pl.y;
				e2 -= fl.y;

				e3 = cos(radian(phi)) * cos(radian(theta)) * pr.x;
				e3 += ( cos(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) - sin(radian(phi))  * cos(radian(shi)) ) * pr.y;
				e3 -= fr.x;

				e4 = sin(radian(phi)) * cos(radian(theta)) * pr.x;
				e4 += ( sin(radian(phi)) * sin(radian(theta)) * sin(shi) + cos(radian(phi))  * cos(radian(shi)) ) * pr.y;
				e4 -= fr.y;

				e5 = cos(radian(phi)) * cos(radian(theta)) * pn.x;
				e5 += ( cos(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) - sin(radian(phi))  * cos(radian(shi)) ) * pn.y;
				e5 -= fn.x;

				e6 = sin(radian(phi)) * cos(radian(theta)) * pn.x;
				e6 += ( sin(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) + cos(radian(phi))  * cos(radian(shi)) ) * pn.y;
				e6 -= fn.y;

				e = ( pow(e1,2) + pow(e3,2) + pow(e5,2) ) + ( pow(e2,2) + pow(e4,2) + pow(e6,2) );

				if(e < E ){
					E = e;
					thetaF = theta;
					phiF = phi;
					shiF = shi;
				}
			}
		}
	}

	angles.push_back(shiF);
	angles.push_back(thetaF);
	angles.push_back(phiF);
		
	return angles;
}

float HeadRotationDetector::radian( float angle ) 
{
	return angle*PI/180;
}