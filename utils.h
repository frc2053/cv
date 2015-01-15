#ifndef __UTILS_H__
#define __UTILS_H__

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

extern RNG rng;

#define randColor()     Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255))

extern Scalar GREEN;
extern Scalar RED;

void drawRectangle(Mat *img, Rect *rect, Scalar *color);

#endif
