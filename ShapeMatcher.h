#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Contour.h"

using namespace std;
using namespace cv;

#define MIN_CONTOUR_SIZE    6
#define MIN_OBJ_WH          20

class ShapeMatcher
{
private:
    virtual bool isMatch(Contour *contour) { return false; }
    
public:
    Mat* img;
    
    ShapeMatcher(Mat *img);
    void setImg(Mat* img);
    bool findMatch(vector<Contour> *contours, Contour *matchingContour, Rect *boundingRect);
};

/***** BackwardsLMatcher *****/
class BackwardsLMatcher: public ShapeMatcher
{
private:
    bool isMatch(Contour *contour);
public:
    BackwardsLMatcher(Mat* img) : ShapeMatcher(img) {}
};

/***** LMatcher *****/
class LMatcher: public ShapeMatcher
{
private:
    bool isMatch(Contour *contour);
public:
    LMatcher(Mat* img) : ShapeMatcher(img) {}
};

/***** YellowToteMatcher *****/
class YellowToteMatcher: public ShapeMatcher
{
private:
    bool isMatch(Contour *contour);
public:
    YellowToteMatcher(Mat* img) : ShapeMatcher(img) {}
};

