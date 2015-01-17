#include "Contour.h"
#include "ShapeMatcher.h"
#include "utils.h"

class YellowToteFinder
{       
private:
    YellowToteMatcher ytm = YellowToteMatcher(&HSV_YELLOW);

public:
    Contour matchingContour;
    Rect matchingBoundRect;
    
    YellowToteFinder();
    bool findTote(Mat* img);    
};
