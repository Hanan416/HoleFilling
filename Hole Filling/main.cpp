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

	Mat grayIm, holed, filledImage, approxImage;

	grayIm = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!grayIm.data)									// Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	/* Copy to display */
	grayIm.convertTo(filledImage, CV_64F);
	grayIm.convertTo(holed, CV_64F);
	grayIm.convertTo(approxImage, CV_64F);

	/* normalizing values to [0,1]*/
	filledImage = filledImage / 255;
	holed = holed / 255;
	approxImage = approxImage/ 255;

	/* Put a hole in the images */
	Mat hole(5, 100, CV_64F, HOLE);
	hole.copyTo(holed(Rect(60, 60, hole.cols, hole.rows)));
	hole.copyTo(filledImage(Rect(60, 60, hole.cols, hole.rows)));
	hole.copyTo(approxImage(Rect(60, 60, hole.cols, hole.rows)));

	/* check for valid k-connection */
	int kConnection = atoi(argv[2]);
	if (kConnection != 4 && kConnection != 8) {
		std::cout << "k value should be 4 or 8" << std::endl;
		return -1;
	}

	HoleFilling* hf = new HoleFilling(&filledImage, kConnection, false);
	HoleFilling* hfApprox = new HoleFilling(&filledImage, kConnection, true);

	hf->findHole();
	hfApprox->findHole();
	
	filledImage = hf->fillHole();
	approxImage = hfApprox->fillHoleApprox();


	namedWindow("Gray Image", WINDOW_AUTOSIZE);			// Create a window for display.
	imshow("Gray Image", grayIm);						// Show gray image inside it.

	namedWindow("Holed Image", WINDOW_AUTOSIZE);		// Create a window for display.
	imshow("Holed Image", holed);						// Show holed image inside it.

	namedWindow("Filled Image", WINDOW_AUTOSIZE);		// Create a window for display.
	imshow("Filled Image", filledImage);				// Show res image inside it.

	namedWindow("Approx Image", WINDOW_AUTOSIZE);		// Create a window for display.
	imshow("Approx Image", approxImage);				// Show Approx image inside it.
	
	waitKey(0);                                         // Wait for a keystroke in the window

	return 0;
}
