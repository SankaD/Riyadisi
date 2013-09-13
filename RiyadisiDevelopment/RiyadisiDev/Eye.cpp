#include "Eye.h"

Eye::Eye ( void )
{

}
Eye::~Eye ( void )
{
}
void Eye::setEyeType ( EyeType type )
{
    this->type = type;
}
EyeType Eye::getEyeType()
{
    return this->type;
}
void Eye::setInnerPoint ( Point2f point )
{
    this->innerPoint = point;
}
void Eye::setOuterPoint ( Point2f point )
{
    this->outerPoint = point;
}
Point2f Eye::getInnerPoint()
{
    return this->innerPoint;
}
Point2f Eye::getOuterPoint()
{
    return this->outerPoint;
}
void Eye::setPupil ( Pupil pupil )
{
    this->pupil = pupil;
}
Pupil Eye::getPupil()
{
    return this->pupil;
}
