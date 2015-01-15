#include "InclusionTester.h"
#include "utils.h"

InclusionTester::InclusionTester(int numPoints, vector<bool> expectedAnswers)
{
    this->numPoints = numPoints;
    this->expectedAnswers = expectedAnswers;
}

bool InclusionTester::test(Contour *contour)
{
    return test(contour, NULL);
}

bool InclusionTester::test(Contour *contour, Mat *img)
{
    bool ans;
    Rect boundRect = boundingRect(Mat(*contour));
    
    this->testPoints = new vector<Point>;
    
    generateTestPoints(&boundRect);
    if (!img)
        ans = checkPoints(contour);
    else
        ans = checkAndDrawPoints(contour, img);
    
    delete this->testPoints;
    return ans;
}

void InclusionTester::generateTestPoints(Rect *boundRect)
{
    float xInc = (float)boundRect->width  / (numPoints + 1);
    float yInc = (float)boundRect->height / (numPoints + 1);
    float xStop = (float)boundRect->x + boundRect->width - 1;
    float yStop = (float)boundRect->y + boundRect->height - 1;
    
    //cout << "GenTestPoints()  rect (x,y) =  " << boundRect->x << "," << boundRect->y << "   (w,h) = " << boundRect->width << "," << boundRect->height << endl;
    //cout << "  xInc= " << xInc << "  yInc= " << yInc << endl;
    //cout << "  xStop= " << xStop << "  yStop= " << yStop << endl;
    
    for(float curY = boundRect->y + yInc; curY < yStop; curY += yInc) {
        for(float curX = boundRect->x + xInc; curX < xStop; curX += xInc) {
            testPoints->push_back(Point((int)curX, (int)curY));
            //cout << "    (x,y) := " << curX << "," << curY << endl;
        }
    }
}

bool InclusionTester::checkPoints(Contour* contour)
{
    int rc;
        
    for(int i=0; i < testPoints->size(); i++) {
        rc = pointPolygonTest(*contour, (*testPoints)[i], false);
        
        if (rc < 0 && expectedAnswers[i])
            return false;
        if (rc >= 0 && !expectedAnswers[i])
            return false;
    }
    return true;
}

bool InclusionTester::checkAndDrawPoints(Contour* contour, Mat *img)
{
    bool ans = true;
    int rc;
    
    for(int i=0; i < testPoints->size(); i++) {
        rc = pointPolygonTest(*contour, (*testPoints)[i], false);
        
        if (rc < 0 && expectedAnswers[i]) {
            cv::line(*img, (*testPoints)[i], (*testPoints)[i], Scalar(0,0,255), 4);
            ans = false;
        }
        else if (rc >= 0 && !expectedAnswers[i]) {
            cv::line(*img, (*testPoints)[i], (*testPoints)[i], Scalar(0,0,255), 4);
            ans = false;
        }
        else {
            cv::line(*img, (*testPoints)[i], (*testPoints)[i], Scalar(0,255,0), 4);
        }       
    }
    return ans;
}
