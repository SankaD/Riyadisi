#include "Pupil.h"

Pupil::Pupil ( void )
{

}
Pupil::~Pupil ( void )
{

}
void Pupil::setPupilLocation ( Circle location )
{
    this->location.setCenter ( location.getCenter() );
    this->location.setRadius ( location.getRadius() );
}
Circle Pupil::getPupilLocation ( void )
{
    Circle center;
    center.setCenter ( this->location.getCenter() );
    center.setRadius ( this->location.getRadius() );
    return center;
}
