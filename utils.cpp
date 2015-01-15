#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "utils.h"

using namespace cv;

RNG rng = RNG(12344);

Scalar GREEN = Scalar(0,255,0);
Scalar RED   = Scalar(0,0,255);

void drawRectangle(Mat *img, Rect *rect, Scalar *color)
{
    rectangle(*img, rect->tl(), rect->br(), *color, 2);
}

