#include "HsvRange.h"

HsvRange::HsvRange(Scalar hsvMin, Scalar hsvMax)
{
    this->hsvMin = hsvMin;
    this->hsvMax = hsvMax;
}

bool HsvRange::testPixel(Mat *hsvImg, int x, int y)
{
    Point p = Point(x, y);
    Vec3b pixelColour = hsvImg->at<Vec3b>(p);
    
    for (int i = 0; i < 3; i++) // Iterate over the 3 channels of hsv
        if (pixelColour[i] < hsvMin[i] || pixelColour[i] > hsvMax[i])
            return false;
    return true;
}
