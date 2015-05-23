#include "histogram.h"

using namespace cv;
using namespace std;

Mat calc1DHist(Mat image, int color){

	vector<Mat> bgr_planes;
	split(image, bgr_planes);

	int histSize = 256;
	float range[2] = {0, 256};
	const float * histRange = {range};
	bool uniform = true;
	bool accumulate = false;

	Mat hist;           // plane
	calcHist(&bgr_planes[color], 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	return hist;
}

/* Mat calc2DHist(Mat image, int color1, int color2){

	// brg
	// 0 - blue, 1 - red, 2 - green.

	vector<Mat> bgr_planes;
	split(image, bgr_planes);

	int histSize = 256;
	float range[2] = {0, 256};
	const float * histRange = {range};
	bool uniform = true;
	bool accumulate = false; 

	Mat hist;           // plane
	// calcHist(&bgr_planes[color], 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	return hist;
} */

Mat calcGrayHist(Mat image){

	int histSize = 64;
	float range[2] = {0, 256};
	const float *histRange = {range};
	bool uniform = true;
	bool accumulate = false;

	Mat hist;
	calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	return hist;

}

/* Mat calc3DHist(Mat image){

    int histSize[3] = {2, 2, 2};
    float range[2] = {0, 256};
    const float * ranges[3] = {range, range, range};
    int channels[3] = {0, 0, 0};
	bool uniform = true;
	bool accumulate = false;
	
    Mat hist;
	calcHist(&image, 1, channels, Mat(), hist, 3, histSize, ranges, uniform, accumulate);
	

} */



float hist1DCompare(Mat hist1, Mat hist2){

    int height = hist1.rows; // number of bims in hist.
	float distance = 0;

	for (int i = 0; i < height; i++){
			distance = distance + abs(hist1.at<float>(i) - hist2.at<float>(i));
	     }

	distance = distance / (2*(89*60));

	float similarity = 1 - distance;
	return similarity;
}

float hist3DCompare(Mat hist1, Mat hist2){

	int histSize[] = {8, 8, 8};
	float distance = 0;

	 for (int i=0; i<histSize[0]; i++) {
            for (int j=0; j<histSize[1]; j++) {
                for (int k=0; k<histSize[2]; k++) {
                    // distance = distance + abs ( hist1.at<float>(i, j, k) - hist2.at<float>(i, j, k)  );
                }
            }
        }

	distance = distance / (6*(89*60));

    float similarity = 1 - distance;
	return similarity;
}