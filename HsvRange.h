#ifndef __HSV_RANGE__
#define __HSV_RANGE__

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class HsvRange
{
    public:
        Scalar hsvMin;
        Scalar hsvMax;
        HsvRange(Scalar hsvMin, Scalar hsvMax);
};

#endif
