#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ShapeMatcher.h"
#include "utils.h"

using namespace cv;
using namespace std;

/** @function main */
int main( int argc, char** argv )
{   
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;
    YellowToteMatcher ytm(&HSV_YELLOW);
    bool isMatch;
    for(;;)
    {        
        cap >> frame; // get a new frame from camera
            
        vector<Contour> contours = detectContours_YellowFilter(&frame, 6, 50);
        Contour matchingContour;
        Rect matchingBoundRect;
        
        isMatch = ytm.findMatch(&contours, &frame, &matchingContour, &matchingBoundRect);
        
        // Mask all except yellow :)
        Mat hsvImg, maskImg, masked;
        cvtColor(frame, hsvImg, CV_BGR2HSV);
        Scalar hsvMin = Scalar(20, 100, 100);
        Scalar hsvMax = Scalar(30, 255, 255);
        inRange(hsvImg, hsvMin, hsvMax, maskImg);
        frame.copyTo(frame, maskImg);
        
        if(isMatch) {
            drawContour(&matchingContour, &frame);
        }        
        
        imshow("Yellow Tote Detector Line - Src", frame);
        imshow("Masked", maskImg);
        if(waitKey(30) >= 0) break;
        //usleep(100000);
    }
    return 0;
}

