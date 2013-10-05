#pragma once

#include "PupilFeature.h"

void PupilFeature::setCenterPoint ( Point2f point )
{
    centerPoint.x = point.x;
    centerPoint.y = point.y;
}
Point2f PupilFeature::getCenterPoint()
{
    Point2f point;
    point.x = centerPoint.x;
    point.y = centerPoint.y;
    return point;
}
PupilFeature::PupilFeature()
{
    //centerPoint = new Point2f();
}
PupilFeature::~PupilFeature()
{
}