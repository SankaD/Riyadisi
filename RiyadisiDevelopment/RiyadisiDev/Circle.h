#pragma once
#include <opencv2\core\core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Circle {
private:
    float x, y;
    float radius;
public:
    void setCenter ( float x, float y );
    Point2f getCenter();
    void setRadius ( float radius );
    float getRadius();
};