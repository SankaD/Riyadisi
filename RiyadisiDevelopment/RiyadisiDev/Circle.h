#pragma once
#include <opencv2\core\core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Represents a circle
/// </summary>
class Circle {
private:
    float x, y;
    float radius;
public:
    void setCenter ( float x, float y );
    void setCenter ( Point2f center );
    Point2f getCenter();
    void setRadius ( float radius );
    float getRadius();
};