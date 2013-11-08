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
    bool isOpened();
private:
    VideoCapture capture;
};