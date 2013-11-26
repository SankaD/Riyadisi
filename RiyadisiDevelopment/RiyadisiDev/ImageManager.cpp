#include "ImageManager.h"

ImageManager::ImageManager ( ImageSourceType sourceType, string filename, int cameraID ) {
    videoEnded = false;
    if ( sourceType == ImageSourceType::File ) {
        capture = VideoCapture ( filename );
    } else {
        capture = VideoCapture ( cameraID );
    }
}
Mat &ImageManager::acquireImage() {
    Mat image;

    return acquireImage ( image );
}
Mat &ImageManager::acquireImage ( Mat &image ) {
    capture >> image;
    videoEnded = image.empty();
    return image;
}
bool ImageManager::isOpened() {
    return capture.isOpened();
}
ImageManager::~ImageManager() {
    capture.release();
}
ImageManager::ImageManager() {
}
float ImageManager::getFPS() {
    return capture.get ( CV_CAP_PROP_FPS );
}
bool ImageManager::isVideoEnded() {
    return videoEnded;
}
int ImageManager::getFrameNumber() {
    return capture.get ( CV_CAP_PROP_POS_FRAMES );
}