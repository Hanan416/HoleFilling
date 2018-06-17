/*
* Hole filling algorithm, main class 
* 
* @Params: <fileName> <k> 
*		  + fileName should include the file extension as well
*		  + k is the k-connected neighbors
* @Author: Hanan Peretz
*/


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "HoleFilling.h"

using namespace cv;

int main(int argc, char** argv) {
	
	if (argc != 3)
	{
		std::cout << " Usage: <fileName> <k>" << std::endl;
		return -1;
	}

	Mat grayIm, holed, filledImage;

	grayIm = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!grayIm.data)									// Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	grayIm.convertTo(filledImage, CV_64F);
	grayIm.convertTo(holed, CV_64F);

	filledImage = filledImage / 255;
	holed = holed / 255;

	Mat hole(30, 30, CV_64F, HOLE);
	hole.copyTo(holed(Rect(60, 80, hole.cols, hole.rows)));
	hole.copyTo(filledImage(Rect(60, 80, hole.cols, hole.rows)));

	int kConnection = atoi(argv[2]);
	if (kConnection != 4 && kConnection != 8) {
		std::cout << "k value should be 4 or 8" << std::endl;
		return -1;
	}

	HoleFilling* hf = new HoleFilling(&filledImage, kConnection);
	hf->findHole();
	filledImage = hf->fillHole();


	namedWindow("Gray Image", WINDOW_AUTOSIZE);		// Create a window for display.
	imshow("Gray Image", grayIm);					// Show gray image inside it.

	namedWindow("Holed Image", WINDOW_AUTOSIZE);		// Create a window for display.
	imshow("Holed Image", holed);						// Show holed image inside it.

	namedWindow("Filled Image", WINDOW_AUTOSIZE);		// Create a window for display.
	imshow("Filled Image", filledImage);				// Show res image inside it.

	waitKey(0);                                         // Wait for a keystroke in the window
	return 0;
}
