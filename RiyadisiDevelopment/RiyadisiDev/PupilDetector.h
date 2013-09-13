#pragma once
#include "Detector.h"
#include "Eye.h"

/// <summary>
/// Detects the pupil given an image of an eye.
/// </summary>
class PupilDetector {
public:
    PupilDetector ( void );
    ~PupilDetector ( void );

    /// <summary>
    /// Detects the pupil from an eye given the eye location and the image.
    /// </summary>
    /// <param name="eye">Location of the eye</param>
    /// <param name="frame">Image where the eye is</param>
    /// <Returns>
    Pupil detectPupil ( Mat eye );

};
