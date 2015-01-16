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

