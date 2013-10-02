#pragma once

#include "PupilFeature.h"

void PupilFeature::setCenterPoint ( Point2f point )
{
    this->centerPoint.x = point.x;
    this->centerPoint.y = point.y;
}
Point2f PupilFeature::getCenterPoint()
{
    Point2f point;
    point.x = this->centerPoint.x;
    point.y = this->centerPoint.y;
    return point;
}