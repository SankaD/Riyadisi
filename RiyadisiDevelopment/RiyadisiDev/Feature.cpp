#pragma once

#include "Feature.h"

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
    return this->featureRect;
}
void Feature::setFeatureRect ( Rect rect )
{
    this->featureRect = rect;
}