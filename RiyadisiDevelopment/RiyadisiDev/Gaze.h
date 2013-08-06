#pragma once

class Gaze {
private:
    int gazeX, gazeY, gazeZ;
public:
    Gaze ( void );
    ~Gaze ( void );
    void setGaze ( int x, int y, int z );
    int getGaze ( short int axis );
};
