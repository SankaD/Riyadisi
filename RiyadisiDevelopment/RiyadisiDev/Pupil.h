#pragma once

#include "Circle.h"

class Pupil {
public:
    Pupil ( void );
    ~Pupil ( void );
    void setPupilLocation ( Circle location );
    Circle getPupilLocation ( void );
private:
    Circle location;
};

