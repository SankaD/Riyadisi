#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

///<summary>
///Represents the image source type
///</summary>
enum ImageSourceType {
    Camera, File
};

///<summary>
///Retrieves images from a given video source
///</summary>
class ImageManager {
public:

    ImageManager ( ImageSourceType sourceType, string fileName = "", int cameraID = 0 );
    ImageManager();
    ~ImageManager();
    Mat &acquireImage ();
    Mat &acquireImage ( Mat &image );

    ///<summary>
    ///Checks whether the video is opened.
    ///</summary>
    bool isOpened();

    ///<summary>
    ///Gets the Frame rate of the video
    ///</summary>
    float getFPS();

    ///<summary>
    ///Checks whether the video has reached its end.
    ///</summary>
    bool isVideoEnded();

    ///<summary>
    ///Gets the index of current frame
    ///</summary>
    int getFrameNumber();

    ///<summary>
    ///Gets the length of the video in terms of frames
    ///</summary>
    int getVideoFrameLength();
private:
    VideoCapture capture;
    bool videoEnded;
};