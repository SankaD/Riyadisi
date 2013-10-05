#include "Feature.h"
#include "PupilFeature.h"

class EyeFeature : public  Feature {
private:
    PupilFeature pupil;
public:
    EyeFeature();
    PupilFeature getPupil();
};