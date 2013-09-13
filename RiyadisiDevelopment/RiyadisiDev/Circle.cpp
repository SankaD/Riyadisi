
#include "Circle.h"

void Circle::setRadius ( float radius )
{
    this->radius = radius;
}

void Circle::setCenter ( float x, float y )
{
    this->x = x;
    this->y = y;
}

float Circle::getRadius()
{
    return this->radius;
}

Point2f Circle::getCenter()
{
    return Point2f ( this->x, this->y );
}
void Circle::setCenter ( Point2f center )
{
    this->setCenter ( center.x, center.y );
}