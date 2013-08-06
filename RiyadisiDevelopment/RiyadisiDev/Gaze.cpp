#include "Gaze.h"

Gaze::Gaze ( void )
{
    gazeX = gazeY = gazeZ = 0;
}

Gaze::~Gaze ( void )
{
}
void Gaze::setGaze ( int x, int y, int z )
{
    gazeX = x;
    gazeY = y;
    gazeZ = z;
}
int Gaze::getGaze ( short int axis )
{
    int value;
    switch ( axis ) {
        case 0:
            value = gazeX;
            break;
        case 1:
            value = gazeY;
            break;
        case 2:
            value = gazeZ;
            break;

    }
    return value;
}