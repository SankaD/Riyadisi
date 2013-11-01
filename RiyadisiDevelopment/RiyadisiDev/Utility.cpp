#include "Utility.h"


void point ( Mat img, Point2f point, Scalar color )
{
    line ( img, Point2f ( point.x + 10, point.y ), Point2f ( point.x - 10, point.y ), color );
    line ( img, Point2f ( point.x , point.y + 10 ), Point2f ( point.x, point.y - 10 ), color );
    circle ( img, point, 8, color );
}