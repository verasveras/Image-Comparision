#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat calc1DHist(Mat image, int color);
// Mat calc2DHist(Mat image, int color1, int color2);
Mat calc3DHist(Mat image);
Mat calcGrayHist(Mat image);
float hist1DCompare(Mat hist1, Mat hist2);
float hist3DCompare(Mat hist1, Mat hist2);