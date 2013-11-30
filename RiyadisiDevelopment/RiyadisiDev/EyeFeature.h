#include "Feature.h"
#include "PupilFeature.h"

enum EyeState {
    OPEN, CLOSE
};

class EyeFeature : public  Feature {
private:
    PupilFeature pupil;
	EyeState state;
public:
    EyeFeature();

    ///<summary>
    ///Gets a 'reference' to the PupilFeature in the eye
    ///</summary>
    ///<returns>A reference to the PupilFeature</returns>
    PupilFeature *getPupil();
	bool isEyeOpen();
    void setEyeState ( EyeState state );
    virtual void clearFeature();
};