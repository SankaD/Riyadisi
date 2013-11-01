#include "ImageManager.h"

ImageManager::ImageManager ( ImageSourceType sourceType, string filename, int cameraID )
{
    if ( sourceType == ImageSourceType::File ) {
        capture = VideoCapture ( filename );
    } else {
        capture = VideoCapture ( cameraID );
    }
}
Mat &ImageManager::acquireImage()
{
    Mat image;
    return acquireImage ( image );
}
Mat &ImageManager::acquireImage ( Mat &image )
{
    capture >> image;
    return image;
}
bool ImageManager::isOpened()
{
    return capture.isOpened();
}
ImageManager::~ImageManager()
{
}