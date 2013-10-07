#include "Feature.h"
#include "PupilFeature.h"

class EyeFeature : public  Feature {
private:
    PupilFeature pupil;
public:
    EyeFeature();

    ///<summary>
    ///Gets a 'reference' to the PupilFeature in the eye
    ///</summary>
    ///<returns>A reference to the PupilFeature</returns>
    PupilFeature *getPupil();
};