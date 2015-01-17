#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "YellowToteFinder.h"

YellowToteFinder::YellowToteFinder()
{
}

bool YellowToteFinder::findTote(Mat* img)
{
    bool isMatch;
    
    vector<Contour> contours = detectContours_YellowFilter(img, 6, 25);
    isMatch = ytm.findMatch(&contours, img, &matchingContour, &matchingBoundRect);
    return isMatch;
}
