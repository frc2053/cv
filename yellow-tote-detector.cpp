#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#include "ShapeMatcher.h"
#include "Contour.h"
#include "utils.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{   
    /// Load & prep src image
    Mat src, drawing;
    src = imread( argv[1], 1 );
    drawing = Mat::zeros(src.size(), CV_8UC3);
       
    vector<Contour> contours = detectContours_YellowFilter(&src, 6, 50);
    YellowToteMatcher ytm(&src);
    
    drawContourList(&contours, &drawing);
    
    for(int i=0; i < contours.size(); i++) {
        contourDrawPoints(&contours[i], &drawing);
        Point centerPoint = contourCentoid(&contours[i]);
        cv::line(src, centerPoint, centerPoint, GREEN, 5);
        cv::line(drawing, centerPoint, centerPoint, GREEN, 5);
    }
    
    Contour matchingContour;
    Rect matchingBoundRect;
    ytm.findMatch(&contours, &matchingContour, &matchingBoundRect);

    /// Show in a window
    imshow( "Contours", drawing );
    imshow( "Src", src );
    
    waitKey(0);
    return 0;
}

