#pragma once
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <fstream>
#include "Log.h"

using namespace cv;
using namespace std;

// Drawing functions
///<summary>
///Draws a point in the provided image
///</summary>
void point ( Mat img, Point2f point, Scalar color );

// IO helper functions
///<summary>
///Checks whether a file exists
///</summary>
bool isExists(string filename);