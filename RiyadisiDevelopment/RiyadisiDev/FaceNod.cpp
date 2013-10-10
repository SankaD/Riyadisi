#include "FaceNod.h"

Rect FaceNod::getFace()
{
    return face;
}
void FaceNod::setFace ( Rect face )
{
    this->face.x = face.x;
    this->face.y = face.y;
    this->face.width = face.width;
    this->face.height = face.height;
}
bool FaceNod::isAvailable()
{
    return available;
}
void FaceNod::setAvailable ( bool availability )
{
    this->available = availability;
}
time_t FaceNod::getTimestamp()
{
    return this->timestamp;
}
void FaceNod::setTimestamp ( time_t timestamp )
{
    this->timestamp = timestamp;
}