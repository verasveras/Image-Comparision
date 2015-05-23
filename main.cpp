#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "histogram.h"
#include "texture.h"
#include "image.h"

using namespace cv;
using namespace std;


vector <vector<float>> allRedCompared(vector<Image> images){

	char * filename = "..\\Red.txt";
	FILE * file = fopen(filename, "w");

	vector <vector<float>> imageTextures;
	for (int i = 0; i < images.size(); i++){
		vector<float> tmpAdd;
		for (int j = 0;  j < images.size(); j++){

			float compare = hist1DCompare(images[i].imageRedHist, images[j].imageRedHist);
			tmpAdd.push_back(compare);

			fprintf(file, "%f ", compare);
		}

		imageTextures.push_back(tmpAdd);
		fprintf(file, "\n");
	}
	
	fclose(file);
	return imageTextures;
}
vector <vector<float>> allBlueCompared(vector<Image> images){

	char * filename = "..\\Red.txt";
	FILE * file = fopen(filename, "w");

	vector <vector<float>> imageTextures;
	for (int i = 0; i < images.size(); i++){
		vector<float> tmpAdd;
		for (int j = 0;  j < images.size(); j++){

			float compare = hist1DCompare(images[i].imageBlueHist, images[j].imageBlueHist);
			tmpAdd.push_back(compare);

			fprintf(file, "%f ", compare);
		}

		imageTextures.push_back(tmpAdd);
		fprintf(file, "\n");
	}
	
	fclose(file);
	return imageTextures;
}
vector <vector<float>> allGreenCompared(vector<Image> images){

	char * filename = "..\\Red.txt";
	FILE * file = fopen(filename, "w");

	vector <vector<float>> imageTextures;
	for (int i = 0; i < images.size(); i++){
		vector<float> tmpAdd;
		for (int j = 0;  j < images.size(); j++){

			float compare = hist1DCompare(images[i].imageGreenHist, images[j].imageGreenHist);
			tmpAdd.push_back(compare);

			fprintf(file, "%f ", compare);
		}

		imageTextures.push_back(tmpAdd);
		fprintf(file, "\n");
	}
	
	fclose(file);
	return imageTextures;
}
vector <vector<float>> allTextCompared(vector<Image> images){

	char * filename = "..\\Textures.txt";
	FILE * file = fopen(filename, "w");

	vector <vector<float>> imageTextures;
	for (int i = 0; i < images.size(); i++){
		vector<float> tmpAdd;
		for (int j = 0;  j < images.size(); j++){

			float compare = hist1DCompare(images[i].imageTextureHist, images[j].imageTextureHist);
			tmpAdd.push_back(compare);

			fprintf(file, "%f ", compare);
		}

		imageTextures.push_back(tmpAdd);
		fprintf(file, "\n");
	}
	
	fclose(file);
	return imageTextures;
}

vector <vector<int>> mostSimilar(vector <vector<float>> textures){

	char * filename = "..\\similarTexture.txt";
	FILE * file = fopen(filename, "w");

	char * filename2 = "C:\\Users\\Lisa\\Desktop\\similarTextureLocation.txt";
	FILE * file2 = fopen(filename2, "w");

	vector <vector<float>> texturesSorted = textures;
	vector <vector<int>> mostSim;


	// SORT the texture list, descending order. 
	for (int i = 0; i < texturesSorted.size(); i++){

		sort(texturesSorted[i].begin(), texturesSorted[i].end());
		
		vector<float> printTest = texturesSorted[i];
		for (int j = 0; j < printTest.size(); j++){
		     fprintf(file, "%f ", printTest[j], j);
		} 

        fprintf(file, "\n");
	}
	

    // find locations of last four most 
	for (int i = 0; i < texturesSorted.size(); i++){
		vector<float> currentSorted = texturesSorted[i];
		vector<float> currentUnsorted = textures[i]; 
		vector<int> locations;
		
		/*
		for (int x = 0; x < currentSorted.size(); x++){
		    fprintf(file2, "%f ", currentSorted[x]);
		}*/

		// look at last four (largest elements);
		for (int j = currentSorted.size() - 1; j > currentSorted.size() - 5; j--){	
			
			// compare element in currentSorted to currentUnsorted; add their locations to vector<int>.
			for (int k = 0; k < currentUnsorted.size();  k++){
				if (currentSorted[j] == currentUnsorted[k]){
					if (locations.size() < 4){
					    locations.push_back(k);
					    fprintf(file2, "%d ", k);
					}
				} 
			}
		}

		mostSim.push_back(locations);
        fprintf(file2, "\n");
	}                                                                                                                                                                         

	fclose(file);
	return mostSim;
}
vector <vector<int>> leastSimilar(vector <vector<float>> textures){

	char * filename2 = "..\\leastsimilarTextureLocation.txt";
	FILE * file2 = fopen(filename2, "w");

	vector <vector<float>> texturesSorted = textures;
	vector <vector<int>> leastSim;

	// SORT the texture list, ascending order. 
	for (int i = 0; i < texturesSorted.size(); i++){
		sort(texturesSorted[i].begin(), texturesSorted[i].end());
	}
	

    // find locations of last three least like image
	for (int i = 0; i < texturesSorted.size(); i++){
		vector<float> currentSorted = texturesSorted[i];
		vector<float> currentUnsorted = textures[i]; 
		vector<int> locations;

		// look at first three(smallest));
		for (int j = 0; j < 4; j++){	
			
			// compare element in currentSorted to currentUnsorted; add their locations to vector<int>.
			for (int k = 0; k < currentUnsorted.size();  k++){
				if (currentSorted[j] == currentUnsorted[k]){
					if (locations.size() < 3){
					    locations.push_back(k);
					    fprintf(file2, "%d ", k);
					}
				} 
			}
		}

		leastSim.push_back(locations);
        fprintf(file2, "\n");
	}                                                                                                                                                                         

	fclose(file2);
	return leastSim;
}
Mat drawImages(vector <vector<int>> simlist, vector <vector<int>> leastlist, vector <Image> images){

	int width = 89;
	int height = 60;

	Mat imageGrid(7*height, 40*width, CV_8UC1); // treat the Mat image like a grid.

    // iterate through grid
    for (int i = 0; i < 40; i++) {
		vector <int> locationsSim = simlist[i];
		vector <int> locationsDiff = leastlist[i];

        for (int j = 0; j < 7; j++) {
			if (j <= 3){
			   Mat source = (images[locationsSim[j]].imageGray).clone();
			   source.copyTo(imageGrid(Rect(width*i, height*j, source.cols, source.rows)));
			}

			if (j > 3){
				Mat source = (images[locationsDiff[j-4]].imageGray).clone();
			    source.copyTo(imageGrid(Rect(width*i, height*j, source.cols, source.rows)));
			   }

        }
    }

	return imageGrid;
}
Mat drawColorImages(vector <vector<int>> simlist, vector <vector<int>> leastlist, vector <Image> images){

	int width = 89;
	int height = 60;

	Mat imageGrid(7*height, 40*width, CV_8UC3); // treat the Mat image like a grid.

    // iterate through grid
    for (int i = 0; i < 40; i++) {
		vector <int> locationsSim = simlist[i];
		vector <int> locationsDiff = leastlist[i];

        for (int j = 0; j < 7; j++) {
			if (j <= 3){
			   Mat source = (images[locationsSim[j]].image).clone();
			   source.copyTo(imageGrid(Rect(width*i, height*j, source.cols, source.rows)));
			}

			if (j > 3){
				Mat source = (images[locationsDiff[j-4]].image).clone();
			    source.copyTo(imageGrid(Rect(width*i, height*j, source.cols, source.rows)));
			   }

        }
    }

	return imageGrid;
}

/* vector <vector<int>> cluster (vector <vector<float>> matrix){

	vector <float> row;
	vector <vector<int>> clusters;
	vector <int> locations;

	for (int i = 0; i < 40; 4++){
		vector <int> locations;
		locations.pushback(i);
		clusters.pushback(locations);
	}

	while (clusters.size() > 7){
		for (int j = 0; j < clusters.size() < j++){

			for (int k = 0, k < clusters[k].size() < j++ {
				int currentClusterSmallestLoc = 0;
                int currentClusterLargestLoc = 0;

			    vector <int> currentCluster = clusters[k];
				    // loop through to find largest values in cluster
					for (int x = 0; x < currentCluster.size()) {
						if (currentCluster[x] < currentCluster[currentClusterSmallestLoc)}
							currentClusterSmallestLoc = x;
						
						if (currentCluster[x] < currentCluster[currentClusterLargestLoc)}
							currentClusterLargestLoc = x;
					}

		           for (int q = 0, q < clusters[k].size ||  
			}

		}
	}

	return clusters;
} */


int main()
{
	//Load all the images into a vector;
	vector <Image> images;
	string imagelocs;

	ifstream file("..\\pics.txt");
	while (getline(file, imagelocs));
		Mat source = imread(imagelocs);
		Image toAdd(source);
		images.push_back(toAdd);
	}


	// test write to write out to.
	// char * filename = "C:\\Users\\Lisa\\Desktop\\text2.txt";
	// FILE * file2 = fopen(filename, "w");
	// fprintf(file2, "Size of image vector is %d.\n", images.size());


	// create a 2d vector of all the image texture values, compared. 
	vector <vector<float>> imageTextures =  allTextCompared(images);
	vector <vector<int>> similarTextures = mostSimilar(imageTextures);
	vector <vector<int>> leastTextures = leastSimilar(imageTextures);
    Mat imageTexturesCompared = drawImages (similarTextures, leastTextures, images);
	imshow("Texture Comparisions", imageTexturesCompared);
	imwrite("..\\Textures.jpg", imageTexturesCompared);
    
	//
	int textureSame1 [] = {10, 2, 4, 3, 6, 15, 9, 3, 7, 1,
		                   10, 14, 12, 12, 6, 15, 18, 17, 38, 22,
						   24, 30, 24, 23, 26, 25, 31, 25, 30, 29,
						   32, 31, 40, 22, 36, 35, 39, 38, 33};

	int textureDiff1 [] = {29, 15, 35, 20, 39, 18, 34, 22, 26, 26,
		                  37, 26, 25, 31, 27, 26, 29, 26, 26, 31,
						  12, 1, 11, 22, 36, 1, 26, 29, 31, 31,
						  35, 36, 27, 7, 1, 10, 3, 8, 3, 19};

	int colorSame1 [] = {16, 25, 4, 3, 23, 11, 9, 4, 7, 16,
		                 6, 14, 22, 39, 7, 10, 25, 35, 8, 23,
						 17, 34, 5, 3, 2, 25, 30, 35, 22, 27,
						 11, 27, 40, 22, 18, 3, 24, 1, 22, 33};

	int colorDiff1 [] = {13, 31, 23, 5, 37, 24, 36, 26, 19, 25,
		                1, 32, 31, 23, 1, 15, 30, 31, 18, 36,
						27, 5, 24, 7, 30, 36, 17, 16, 12, 26,
						32, 31, 2, 5, 32, 35, 23, 5, 5, 6};
 
    //
    int textureSame2 [] = {8, 6, 4, 3, 6, 5, 38, 3, 6, 25,
		                   16, 14, 14, 12, 16, 15, 18, 32, 18, 40,
						   24, 35, 18, 23, 26, 25, 28, 27, 30, 29,
						   32, 31, 40, 21, 29, 39, 40, 39, 38, 33};

	int textureDiff2 [] = {29, 29, 37, 37, 38, 39, 35, 26, 35, 29,
		                   37, 7, 1, 1, 24, 24, 8, 15, 25, 6,
						   5, 11, 14, 15, 20, 3, 8, 7, 7, 7,
						   14, 13, 11, 1, 2, 2, 11, 6, 6, 3};

	int colorSame2 [] = {3, 26, 4, 3, 11, 7, 6, 3, 11, 1,
                         5, 9, 14, 15, 20, 10, 21, 35, 24, 23,
						 17, 29, 6, 19, 21, 18, 32, 21, 30, 29,
						 32, 27, 40, 21, 18, 38, 3, 30, 22, 33};

	int colorDiff2 [] = {23, 31, 6, 6, 4, 16, 16, 6, 3, 7,
		                 3, 32, 26, 35, 16, 15, 10, 16, 6, 16,
						 16, 28, 16, 7, 29, 32, 26, 13, 25, 25,
						 26, 12, 31, 31, 4, 13, 6, 12, 8, 1};

	///////////////////////////
	// Lissa
	int textureSame3 [] = {11, 16, 04, 03, 12, 16, 9, 1, 7, 1,
	                       1, 14, 5, 12, 2, 6, 27, 18, 19, 21,
	                       19, 12, 24, 23, 26, 25, 31, 25, 30, 29,
	                       32, 31, 17, 39, 36, 35, 40, 21, 22, 9};

	int textureDiff3 [] = {26, 40, 34, 20, 39, 29, 39, 25, 22, 33,
		                   28, 26, 40, 32, 28, 22, 25, 2, 34, 1,
						   11, 1, 16, 18, 12, 16, 40, 34, 16, 31,
						   8, 1, 15, 11, 16, 15, 1, 38, 12, 13};

	int colorSame3 [] = {10, 34, 4, 3, 6, 5, 9, 3, 7, 16,
				         7, 33, 39, 15, 20, 10, 35, 21, 36, 35,
						 22, 39, 5, 37, 17, 2, 30, 35, 34, 27,
						 32, 27, 40, 39, 18, 16, 24, 36, 34, 7};

	int colorDiff3 [] = {11, 31, 11, 6, 16, 10, 10, 25, 16, 9,
	                     10, 32, 31, 27, 16, 6, 30, 27, 23, 36,
	                     30, 13, 24, 23, 30, 32, 33, 27, 31, 21,
	                     2, 26, 32, 31, 30, 40, 5, 21, 31, 32};


	///////////////////////////////////////////////////////////////////////////////////////////////////	
	// create a 2d vector of the red color values, compared.
	vector <vector<float>> imageRed =  allRedCompared(images);
    vector <vector<int>> similarRed = mostSimilar(imageRed);
	vector <vector<int>> leastRed = leastSimilar(imageRed);
	Mat imageRedCompared = drawColorImages (similarRed, leastRed, images);
    imshow("Red Comparisions", imageRedCompared);
	imwrite("C:\\Users\\Lisa\\Desktop\\Red.jpg", imageRedCompared);


	//  create a 2d vector of the blue color values, compared.
	vector <vector<float>> imageBlue =  allBlueCompared(images);
    vector <vector<int>> similarBlue = mostSimilar(imageBlue);
	vector <vector<int>> leastBlue = leastSimilar(imageBlue);
	Mat imageBlueCompared = drawColorImages (similarBlue, leastBlue, images);
    imshow("Blue Comparisions", imageBlueCompared);
	imwrite("C:\\Users\\Lisa\\Desktop\\Blue.jpg", imageBlueCompared);


	//  create a 2d vector of the green color values, compared.
	vector <vector<float>> imageGreen =  allGreenCompared(images);
    vector <vector<int>> similarGreen = mostSimilar(imageGreen);
	vector <vector<int>> leastGreen = leastSimilar(imageGreen);
	Mat imageGreenCompared = drawColorImages (similarGreen, leastGreen, images);
    imshow("Blue Comparisions", imageGreenCompared);
	imwrite("C:\\Users\\Lisa\\Desktop\\Blue.jpg", imageGreenCompared);


    waitKey(0);
	return 0;
}