#include "Feature.h"

class PupilFeature : public  Feature {
private:
    Point2f centerPoint;

public:
    Point2f getCenterPoint();
    void setCenterPoint ( Point2f point );
};