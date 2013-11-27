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

void HeadRotationDetector::updateGroundPosition ( FaceFeature *faceFeature ) 
{
	Point p1( faceFeature->getLeftEye()->getCenterPoint().x, faceFeature->getLeftEye()->getCenterPoint().y );
	Point p2( faceFeature->getRightEye()->getCenterPoint().x, faceFeature->getRightEye()->getCenterPoint().y );
	Point p3( faceFeature->getNose()->getCenterPoint().x, faceFeature->getNose()->getCenterPoint().y );
	
	pl.x += ( p1.x - pl.x ) * 0.2;
	pl.y += ( p1.y - pl.y ) * 0.2;

	pr.x += ( p2.x - pr.x ) * 0.2;
	pr.y += ( p2.y - pr.y ) * 0.2;

	pn.x += ( p3.x - pn.x ) * 0.2;
	pn.y += ( p3.y - pn.y ) * 0.2;
}


vector<float> HeadRotationDetector::calculateRotation ( FaceFeature *faceFeature )
{

	float E, minE, Theta, Phi, Shi;
	/*float theta = 5, phi = 5, shi = 5, alpha = 0.2, dETheta, dEPhi, dEShi;*/
	vector<float> angles;

	fl = faceFeature->getLeftEye()->getCenterPoint();
	fr = faceFeature->getRightEye()->getCenterPoint();
	fn = faceFeature->getNose()->getCenterPoint();
	
	
	minE=1E+27;
	for(float theta = -90; theta <= 90; theta = theta + 15)
	{
		for(float phi = -90; phi <= 90; phi = phi + 15)
		{
			for(float shi = -90; shi <= 90; shi = shi + 15)
			{

				E = calcError( theta, phi, shi );

				if( E < minE ) {
					Theta = theta;
					Phi = phi;
					Shi = shi;

					minE = E;
				}
			}
		}
	}

	
	minE=1E+27;
	for(float theta = Theta - 10; theta <= Theta + 10; theta = theta + 5)
	{
		for(float phi = Phi - 10; phi <= Phi + 10; phi = phi + 5)
		{
			for(float shi = Shi - 10; shi <= Shi + 10; shi = shi + 5)
			{

				E = calcError( theta, phi, shi );

				if( E < minE ) {
					Theta = theta;
					Phi = phi;
					Shi = shi;

					minE = E;
				}
			}
		}
	}


	minE=1E+27;
	for(float theta = Theta - 4; theta <= Theta + 4; theta++)
	{
		for(float phi = Phi - 4; phi <= Phi + 4; phi = phi++)
		{
			for(float shi = Shi - 4; shi <= Shi + 4; shi = shi++)
			{

				E = calcError( theta, phi, shi );

				if( E < minE ) {
					Theta = theta;
					Phi = phi;
					Shi = shi;

					minE = E;
				}
			}
		}
	}

	/*do {
		
		E = calcError( theta, phi, shi );;
						
		dETheta = - cos(radian(phi)) * sin(radian(theta)) * pl.x + cos(radian(phi)) * cos(radian(theta)) * sin(radian(shi)) * pl.y
			- cos(radian(phi)) * sin(radian(theta)) * pr.x + cos(radian(phi)) * cos(radian(theta)) * sin(radian(shi)) * pr.y
			- cos(radian(phi)) * sin(radian(theta)) * pn.x + cos(radian(phi)) * cos(radian(theta)) * sin(radian(shi)) * pn.y
			- sin(radian(phi)) * sin(radian(theta)) * pl.x + sin(radian(phi)) * cos(radian(theta)) * sin(radian(shi)) * pl.y
			- sin(radian(phi)) * sin(radian(theta)) * pr.x + sin(radian(phi)) * cos(radian(theta)) * sin(radian(shi)) * pr.y
			- sin(radian(phi)) * sin(radian(theta)) * pn.x + sin(radian(phi)) * cos(radian(theta)) * sin(radian(shi)) * pn.y;
			

		dEPhi = - sin(radian(phi))* cos(radian(theta)) * pl.x - ( sin(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) + cos(radian(phi))  * cos(radian(shi)) ) * pl.y
			- sin(radian(phi))* cos(radian(theta)) * pr.x - ( sin(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) + cos(radian(phi))  * cos(radian(shi)) ) * pr.y
			- sin(radian(phi))* cos(radian(theta)) * pn.x - ( sin(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) + cos(radian(phi))  * cos(radian(shi)) ) * pn.y
			+ cos(radian(phi)) * cos(radian(theta)) * pl.x + ( cos(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) - sin(radian(phi))  * cos(radian(shi)) ) * pl.y
			+ cos(radian(phi)) * cos(radian(theta)) * pr.x + ( cos(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) - sin(radian(phi))  * cos(radian(shi)) ) * pr.y
			+ cos(radian(phi)) * cos(radian(theta)) * pn.x + ( cos(radian(phi)) * sin(radian(theta)) * sin(radian(shi)) - sin(radian(phi))  * cos(radian(shi)) ) * pn.y;
			
		dEShi =( cos(radian(phi)) * sin(radian(theta)) * cos(radian(shi)) + sin(radian(phi))  * sin(radian(shi)) ) * pl.y
			+ ( cos(radian(phi)) * sin(radian(theta)) * cos(radian(shi)) + sin(radian(phi))  * sin(radian(shi)) ) * pr.y
			+ ( cos(radian(phi)) * sin(radian(theta)) * cos(radian(shi)) + sin(radian(phi))  * sin(radian(shi)) ) * pn.y
			+ ( sin(radian(phi)) * sin(radian(theta)) * cos(radian(shi)) - cos(radian(phi))  * sin(radian(shi)) ) * pl.y
			+ ( sin(radian(phi)) * sin(radian(theta)) * cos(radian(shi)) - cos(radian(phi))  * sin(radian(shi)) ) * pr.y
			+ ( sin(radian(phi)) * sin(radian(theta)) * cos(radian(shi)) - cos(radian(phi))  * sin(radian(shi)) ) * pn.y;
			
		theta += alpha * dETheta / sqrt( pow(dETheta,2) + pow(dEPhi,2) + pow(dEShi,2) );
		shi += alpha * dEPhi / sqrt( pow(dETheta,2) + pow(dEPhi,2) + pow(dEShi,2) );
		phi += alpha * dEShi / sqrt( pow(dETheta,2) + pow(dEPhi,2) + pow(dEShi,2) );
	
	} while ( E < 0.5 );*/
				
	angles.push_back(Theta);
	angles.push_back(Phi);
	angles.push_back(Shi);
		
	return angles;
}

float HeadRotationDetector::radian( float angle ) 
{
	return angle*PI/180;
}	

float HeadRotationDetector::calcError( float theta, float phi, float shi)
{
	float e1, e2, e3, e4, e5, e6, E;
	
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

	E = ( pow(e1,2) + pow(e3,2) + pow(e5,2) ) + ( pow(e2,2) + pow(e4,2) + pow(e6,2) );

	return E;
}