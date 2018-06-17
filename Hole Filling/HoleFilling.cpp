#include "HoleFilling.h"


HoleFilling::HoleFilling(cv::Mat* srcIm, int k) {
	_srcIm = srcIm;
	_resIm = _srcIm->clone();		//	cloning the original image to manipulate the results here
	_k = k;
}

/*
* @Purpose: iterating over the image matrix _srcIm
*			and find all the pixels with value -1 
*			and set the boundry pixels
*/
void HoleFilling::findHole() {
	for (int i = 0; i < _srcIm->rows; i++) {
		for (int j = 0; j < _srcIm->cols; j++) {
			if (_srcIm->at<double>(i, j) == HOLE) {
				// found a hole
				Pixel holePix = Pixel(i, j, HOLE);
				holePix.setNeighbors(_srcIm, _k);
				holePixels.insert(holePix);	// add the hole pixel to the holePixels vector
				for (int i = 0; i < holePix._neighbors.size(); i++) {
					std::pair<int,int> bInd = std::pair<int,int>(holePix._neighbors.at(i).getX(), holePix._neighbors.at(i).getY());
					boundryIndexes.insert(bInd);  // putting the boundry neighbors, i.e. those with values
				}
			}
		}
	}
	std::cout << "total holes found = " << holePixels.size() << std::endl;
	std::cout << "total boundry found = " << boundryIndexes.size() << std::endl;
}

double HoleFilling::dist(Pixel x, int y_i_x, int y_i_y) {
	const double x_diff = x.getX() - y_i_x;
	const double y_diff = x.getY() - y_i_y;
	return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

cv::Mat HoleFilling::fillHole() {
	
	Pixel currX;
	double xIntensity;
	double y_iIntensity;
	double weightSum;
	double currWeight;

	int y_i_x;
	int y_i_y;
	int x_x;
	int x_y;


	std::set<Pixel>::iterator holeIt;
	std::set<std::pair<int, int>>::iterator boundryIt;

	//for each hole Pixel x
	for (holeIt = holePixels.begin(); holeIt != holePixels.end(); ++holeIt)
	{
		//reset x Params
		x_x = holeIt->getX();
		x_y = holeIt->getY();
		xIntensity = 0;
		weightSum = 0;


		// for each boundry fixel y_i
		for (boundryIt = boundryIndexes.begin(); boundryIt != boundryIndexes.end(); ++boundryIt) {
			y_i_x = boundryIt->first;
			y_i_y = boundryIt->second;

			y_iIntensity = _srcIm->at<double>(y_i_x, y_i_y);
			currWeight = WEIGHT(*holeIt, y_i_x, y_i_y);
			weightSum += currWeight;
			xIntensity += currWeight * y_iIntensity;
		}
		
		// finished calculaing the current hole Pixel intensity
		xIntensity = xIntensity / weightSum;

		// putting the result 
		_resIm.at<double>(holeIt->getX(), holeIt->getY()) = xIntensity;
	}
	return _resIm;
}