#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Contour.h"

using namespace cv;

class InclusionTester
{
    public:
        InclusionTester(int numPoints, vector<bool> expectedAnswers);
        bool test(Contour *contour);
        bool test(Contour *contour, Mat *img);
    
    private:
        vector<Point> *testPoints;
        vector<bool> expectedAnswers;
        int numPoints;
        
        void generateTestPoints(Rect *boundRect);
        bool checkPoints(Contour* contour);
        bool checkAndDrawPoints(Contour* contour, Mat *img);
};
