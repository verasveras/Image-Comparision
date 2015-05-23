#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "texture.h"

using namespace cv;
using namespace std;


// convert 3 channel color mat into 1 channel greyscale mat
Mat convertGray(Mat src){

	int height = src.rows;
	int width = src.cols;
	Mat gray(src.size(), CV_8U);

	for (int y = 0; y < height; y++){
	     for (int x = 0; x < width; x++){
		                                    //y, x.
	        Vec3b intensity = src.at<Vec3b>(y, x);
            uchar blue = intensity.val[0]; 
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];

			uchar grayVal = (blue + green + red) / 3;
			
	        gray.at<uchar>(y, x) = grayVal;
			
		 }
    }

	return gray;
}
Mat textureMat(Mat src){
	
	int height = src.rows;
	int width = src.cols;
    Mat texture (src.size(), CV_8U);
	
	for (int y = 1; y < height-1; y++){
	     for (int x = 1; x < width-1; x++){

			                                //y, x.
			unsigned char pixel = src.at<uchar>(y,x);
			unsigned char texVal = pixel * 8;

			// subtract surrounding pixels.
			texVal = texVal - src.at<uchar>(y+1, x+1);
			texVal = texVal - src.at<uchar>(y+1, x);
			texVal = texVal - src.at<uchar>(y+1, x-1);

			texVal = texVal - src.at<uchar>(y, x-1);
			texVal = texVal - src.at<uchar>(y, x+1);
			
			texVal = texVal - src.at<uchar>(y-1, x-1);
			texVal = texVal - src.at<uchar>(y-1, x);
			texVal = texVal - src.at<uchar>(y-1, x+1);

	        texture.at<uchar>(y, x) = texVal;
		 }
    }

	return texture;

}

