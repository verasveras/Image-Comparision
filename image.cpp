#include "image.h"
#include "histogram.h"
#include "texture.h"

Image::Image(Mat src){
	
	image = src.clone();
	image2 = src.clone();
	imageGray = convertGray(image);
	imageTexture = textureMat(imageGray);
	imageTextureHist = calcGrayHist(imageTexture);
	// imageColorHist = calc3DHist(image2);
	imageRedHist = calc1DHist(image2, 0);
	imageBlueHist = calc1DHist(image2, 1);
	imageRedHist = calc1DHist(image2, 2);

}