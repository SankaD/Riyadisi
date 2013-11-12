#pragma once

#include "FaceFeature.h"
#include "FeatureCollection.h"
#include "FaceNod.h"

using namespace cv;
using namespace std;

class NoddingOffDetector {
private:
    /// stores the face locations
    FaceNod faceArray[FEATURE_ARRAY_LENGTH];
public :
    FaceNod getRect ( int indexFromCurrent );
    void setCurrentRect ( FaceNod rectangle );
    float calculateNoddingOffProbability();
	double noddingOffDetect(FaceFeature feature);
	void train();
	void trainBaumWelch(const cv::Mat &seq, const int max_iter, cv::Mat &TRANS, cv::Mat &EMIS, cv::Mat &INIT,bool UseUniformPrior=false);	
	void viterbi(const cv::Mat &seq, const cv::Mat &_TRANS, const cv::Mat &_EMIS, const cv::Mat &_INIT, cv::Mat &states);
	void getUniformModel(const int &n_states,const int &n_observations, cv::Mat &TRANS,cv::Mat &EMIS,cv::Mat &INIT);
	void correctModel(cv::Mat &TRANS, cv::Mat &EMIS, cv::Mat &INIT);
	void collectTraningData(FaceFeature feature);
	
};
