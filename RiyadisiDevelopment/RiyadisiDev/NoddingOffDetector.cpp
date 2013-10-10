#include "NoddingOffDetector.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

int no_frames=0;
int prv_x_cordinate=0;
int prv_y_cordinate=0;


bool NoddingOffDetector::noddingOffDetect(FaceFeature feature){

	if(!feature.isAvailable()){
	return;	
	}

bool is_nodding_off[10] = {false};
bool is_nodding = false;
bool is_starting = false;

Rect leftEyeRect = feature.getLeftEye()->getFeatureRect();
Rect rightEyeRect = feature.getRightEye()->getFeatureRect();

rightEyeRect.x = rightEyeRect.x + feature.getFeatureRect().x;
rightEyeRect.y = rightEyeRect.x + feature.getFeatureRect().y;

			std::cout<<  rightEyeRect.x << "      ";
			std::cout<<  rightEyeRect.y <<endl;
			if(rightEyeRect.y-prv_y_cordinate>0 )
			{
			 
				is_nodding_off[no_frames]= true;	
				no_frames++;
			} 

			else {
			no_frames = 0;
			
			}
			prv_y_cordinate = rightEyeRect.y;
			

			if(no_frames == 5){
				std::cout<<  "###############################################################################" <<endl;
			
			no_frames = 0;
			return true;
				
			
			}

			else{
				return false;
			}



}


