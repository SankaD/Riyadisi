#pragma once
#include "Detector.h"
#include "Eye.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

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
    /// <returns> if detected,the detected pupil or an empty Pupil object if not.</returns>
    Pupil detectPupil ( Mat eye );

    /// <summary>
    /// Used for drawing a pupil into a video frame. Only used for debugging purposes.
    /// </summary>
    /// <param name="frame"> The image onto which the pupil is drawn </param>
    /// <param name="pupil"> The pupil which should be drawn</param>
    void drawPupil ( Mat frame, Pupil pupil );
};
