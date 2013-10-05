#pragma once

#include "Feature.h"

Feature::Feature()
{
    available = false;
    rotation = 0.0f;
    //featureRect = new Rect();
}

bool Feature::isAvailable()
{
    return available;
}
void Feature::setAvailable ( bool availability )
{
    available = availability;
}
void Feature::setRotation ( float rotation )
{
    this->rotation = rotation;
}
Rect Feature::getFeatureRect()
{
    return featureRect;
}
void Feature::setFeatureRect ( Rect rect )
{
    this->featureRect = rect;
}