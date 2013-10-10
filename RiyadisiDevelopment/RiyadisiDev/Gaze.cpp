#include "Gaze.h"

using namespace cv;
using namespace std;

Gaze::Gaze ( void )
{
    available = false;
}
Gaze::~Gaze ( void )
{
}
float Gaze::getPupilDistance()
{
    float xDistanceSq = pow ( ( leftPupil.x - rightPupil.x ) , 2 );
    float yDistanceSq = pow ( ( leftPupil.y - rightPupil.y ), 2 );

    float distance = sqrt ( xDistanceSq + yDistanceSq );

    return distance;
}
Rect Gaze::getLeftEye()
{
    return leftEye;
}
void Gaze::setLeftEye ( Rect eye )
{
    this->leftEye.x = eye.x;
    this->leftEye.y = eye.y;
    this->leftEye.width = eye.width;
    this->leftEye.height = eye.height;
}
Rect Gaze::getRightEye()
{
    return rightEye;
}
void Gaze::setRightEye ( Rect eye )
{
    rightEye.x = eye.x;
    rightEye.y = eye.y;
    rightEye.width = eye.width;
    rightEye.height = eye.height;
}
Point2f Gaze::getLeftPupil()
{
    return leftPupil;
}
void Gaze::setLeftPupil ( Point2f pupil )
{
    leftPupil.x = pupil.x;
    leftPupil.y = pupil.y;
}
Point2f Gaze::getRightPupil()
{
    return rightPupil;
}
void Gaze::setRightPupil ( Point2f pupil )
{
    rightPupil.x = pupil.x;
    rightPupil.y = pupil.y;
}
bool Gaze::isAvailable()
{
    return available;
}
void Gaze::setAvailable ( bool availability )
{
    this->available = availability;
}
