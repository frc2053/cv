#include "ShapeMatcher.h"
#include "InclusionTester.h"
#include "utils.h"

using namespace cv;
using namespace std;

ShapeMatcher::ShapeMatcher(HsvRange* matchColor)
{
    this->matchColor = matchColor;
    this->debugDraw = false;
}

bool ShapeMatcher::findMatch(vector<Contour> *contours, Mat *img, Contour *matchingContour, Rect *matchingBoundRect)
{
    for(int i=0; i < contours->size(); i++) {
        Contour *contour = &((*contours)[i]);
        Rect rect = boundingRect(Mat(*contour));
        
        // Is this shape an L shape?
        bool isL = isMatch(contour, img);
        if (!isL) continue;
        cout << "***** Found L :)" << endl;
        
        // If this is the L shape we're looking for, draw green rectangle (and shape end-points) on source image!
        if (this->debugDraw) {
            drawRectangle(img, &rect, &GREEN);
            contourDrawPoints(contour, img);
        }
        
        *matchingContour = *contour;
        *matchingBoundRect = rect;
        return true;
        
    }
    return false;

}   

/***** BackwardsLMatcher *****/

bool BackwardsLMatcher::isMatch(Contour *contour, Mat *img)
{   
    vector<bool> expectedAnswers { false, false, true,
                                   false, false, true,
                                   true,  true,  true
                                   };
    
    InclusionTester it(3, expectedAnswers);
    return it.test(contour, img);
}

/***** LMatcher *****/

bool LMatcher::isMatch(Contour *contour, Mat *img)
{   
    vector<bool> expectedAnswers { true, false, false,
                                   true, false, false,
                                   true, true,  true
                                   };
    
    InclusionTester it(3, expectedAnswers);
    return it.test(contour, img);
}

/***** YellowToteMatcher *****/


bool YellowToteMatcher::isMatch(Contour *contour, Mat *img)
{   
    // Can't use inclusion tester here because the tote has angles, it is not square.
    // We probably want to look at the angles at the edgles
    
    // Aspect ratio check
    Rect rect = boundingRect(Mat(*contour));
    float whRatio = (float)rect.width / rect.height;
    float whRatioMin =  2.0 * 0.9;
    float whRatioMax =  2.0 * 1.1;
    if (whRatio < whRatioMin ||  whRatio > whRatioMax)
        return false;
    
    // Color check - Ensure a portion of the tote is the desired match color
    Mat hsvImg;
    cvtColor(*img, hsvImg, CV_BGR2HSV);
    
    int testX = rect.x + rect.width/20;
    int testY = rect.y + rect.width/20;
    
    return matchColor->testPixel(&hsvImg, testX, testY);    
}

