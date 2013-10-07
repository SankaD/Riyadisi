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
    this->available = availability;
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
    this->featureRect.x = rect.x;
    featureRect.y = rect.y;
    featureRect.width = rect.width;
    featureRect.height = rect.height;
}
Rect Feature::getRelativeRect ( Rect rect )
{
    Rect returnValue;
    returnValue.x = this->featureRect.x + rect.x;
    returnValue.y = this->featureRect.y + rect.y;
    returnValue.width = rect.width;
    returnValue.height = rect.height;

    return returnValue;
}