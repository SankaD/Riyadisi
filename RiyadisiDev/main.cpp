/* 
 * File:   main.cpp
 * Author: Sanka Darshana
 *
 * Created on May 16, 2013, 5:53 PM
 */
// testing 3
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void detectAndDisplay(Mat frame);

String face_cascade_name = "./haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "./haarcascade_eye_tree_eyeglasses.xml";
String smile_cascade_name = "./haarcascade_smile.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier smile_cascade;
string window_name = "Capture - Face detection";
RNG rng(12345);

int main(int argc, const char** argv) {

    VideoCapture capture;
    Mat frame;

    if (!face_cascade.load(face_cascade_name)) {
        printf("--(!)Error loading\n");
        return -1;
    };
    if (!eyes_cascade.load(eyes_cascade_name)) {
        printf("--(!)Error loading\n");
        return -1;
    };
    if (!smile_cascade.load(smile_cascade_name)) {
        printf("--(!)Error loading\n");
        return -1;
    }
    capture.open(0);
    if (capture.isOpened()) {
        while (true) {
            capture >> frame;
            if (!frame.empty()) {
                detectAndDisplay(frame);
            } else {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if ((char) c == 'c') {
                break;
            }
        }
    }

}

void detectAndDisplay(Mat frame) {
    vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for (int i = 0; i < faces.size(); i++) {
        Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
        ellipse(frame, center, Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

        Mat faceROI = frame_gray(faces[i]);
        vector<Rect> eyes;
        vector<Rect> smiles;

        eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

        for (int j = 0; j < eyes.size(); j++) {
            Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);
            int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
            circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);
        }

        smile_cascade.detectMultiScale(faceROI, smiles, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

        for (int j = 0; j < smiles.size(); j++) {
            Point center(faces[i].x + smiles[j].x + smiles[j].width * 0.5, faces[i].y + smiles[j].y + smiles[j].height * 0.5);
            int radius = cvRound((smiles[j].width + smiles[j].height)*0.25);
            circle(frame, center, radius, Scalar(0, 150, 150), 4, 8, 0);
        }

    }
    imshow(window_name, frame);
}