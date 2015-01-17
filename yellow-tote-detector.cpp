#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#include "Contour.h"
#include "YellowToteFinder.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{   
    /// Load & prep src image
    Mat src;
    src = imread( argv[1], 1 );
    
    YellowToteFinder ytf = YellowToteFinder();
    bool isMatch = ytf.findTote(&src);
    
    if (isMatch)
        drawContour(&ytf.matchingContour, &src);

    imshow( "Src", src );    
    waitKey(0);
    return 0;
}

