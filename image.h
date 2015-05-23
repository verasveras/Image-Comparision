#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class Image {

public:

	Image(); // default constructor
	Image(Mat src); // constructor

	// things asscoated with image
	Mat image;
	Mat image2;
	Mat imageGray;
	Mat imageTexture;
	Mat imageTextureHist;
	// Mat imageColorHist;
	Mat imageRedHist;
	Mat imageBlueHist;
	Mat imageGreenHist;

};
