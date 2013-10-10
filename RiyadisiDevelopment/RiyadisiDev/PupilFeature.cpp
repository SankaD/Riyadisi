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
PupilFeature::PupilFeature() : Feature()
{
    //centerPoint = new Point2f();
}
PupilFeature::~PupilFeature()
{
}
void PupilFeature::clearFeature()
{
    Feature::clearFeature();
    centerPoint.x = 0;
    centerPoint.y = 0;
}