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
	HeadRotationDetector::pl = p1;
	HeadRotationDetector::pr = p2;
	HeadRotationDetector::pn = p3;
}


vector<float> HeadRotationDetector::calculateRotation ( FaceFeature *faceFeature ){

	float e1, e2, e3, e4, e5, e6;
	double E = 90*90*6, e;
	float thetaF, phiF, shiF;
	Point fl = faceFeature->getLeftEye()->getCenterPoint(),
		fr = faceFeature->getRightEye()->getCenterPoint(),
		fn = faceFeature->getNose()->getCenterPoint();
	vector<float> angles;
		cout<<cos(-90.0)<<" "<<sin(90.0)<<endl;
	/*for(float theta = -90; theta <= 90; theta++){
		for(float phi =- 90; phi <= 90; phi++){
			for(float shi = 90; shi <= 90; shi++){
				e1 = cos(phi) * cos(theta) * pl.x;
				e1 += ( cos(phi) * sin(theta) * sin(shi) - sin(phi)  * cos(shi) ) * pl.y;
				e1 -= fl.x;

				e2 = sin(phi) * cos(theta) * pl.x;
				e2 += ( sin(phi) * sin(theta) * sin(shi) + cos(phi)  * cos(shi) ) * pl.y;
				e2 -= fl.y;

				e3 = cos(phi) * cos(theta) * pr.x;
				e3 += ( cos(phi) * sin(theta) * sin(shi) - sin(phi)  * cos(shi) ) * pr.y;
				e3 -= fr.x;

				e4 = sin(phi) * cos(theta) * pr.x;
				e4 += ( sin(phi) * sin(theta) * sin(shi) + cos(phi)  * cos(shi) ) * pr.y;
				e4 -= fr.y;

				e5 = cos(phi) * cos(theta) * pn.x;
				e5 += ( cos(phi) * sin(theta) * sin(shi) - sin(phi)  * cos(shi) ) * pn.y;
				e5 -= fn.x;

				e6 = sin(phi) * cos(theta) * pn.x;
				e6 += ( sin(phi) * sin(theta) * sin(shi) + cos(phi)  * cos(shi) ) * pn.y;
				e6 -= fn.y;

				e = ( pow(e1,2) + pow(e3,2) + pow(e5,2) ) + ( pow(e2,2) + pow(e4,2) + pow(e6,2) );

				if(e < E ){
					E = e;
					thetaF = theta;
					phiF = phi;
					phiF = shi;
				}
			}
		}
	}*/

	angles.push_back(thetaF);
	angles.push_back(phiF);
	angles.push_back(phiF);

	return angles;
}
