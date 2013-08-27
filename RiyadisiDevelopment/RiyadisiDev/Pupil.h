#pragma once

struct Circle {
    float x, y;
    float radius;
};

class Pupil {
public:
    Pupil ( void );
    ~Pupil ( void );
private:
    Circle pupil;
};

