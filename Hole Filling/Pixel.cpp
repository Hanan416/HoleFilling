#include "Pixel.h"
#include <iostream>


Pixel::Pixel() {
	_x = -1;
	_y = -1;
}


Pixel::Pixel(int x, int y, double i) {
	_x = x;
	_y = y;
	_i = i;
}


void Pixel::setNeighbors(cv::Mat* srcIm, int k) {
	if (_x == NULL || _y == NULL) {
		std::cout << "Pixel indexes are NULL, aborting.." << std::endl;
		return;
	}

	// create new Pixel and push into neighbors vector
	int pX;
	int pY;


	/***** top ****/ 
	pX = _x;
	pY = _y - 1;
	addNeighbor(pX, pY, srcIm);

	/***** bottom ****/
	pX = _x;
	pY = _y + 1;
	addNeighbor(pX, pY, srcIm);

	/***** left ****/
	pX = _x - 1;
	pY = _y;
	addNeighbor(pX, pY, srcIm);

	/***** right ****/
	pX = _x + 1;
	pY = _y;
	addNeighbor(pX, pY, srcIm);

	// add diagonal neighbors
	if (k == 8) {
		/***** top left ****/
		pX = _x - 1;
		pY = _y - 1;
		addNeighbor(pX, pY, srcIm);

		/***** top right ****/
		pX = _x + 1;
		pY = _y - 1;
		addNeighbor(pX, pY, srcIm);

		/***** bottom left ****/
		pX = _x - 1;
		pY = _y + 1;
		addNeighbor(pX, pY, srcIm);

		/***** bottom right ****/
		pX = _x + 1;
		pY = _y + 1;
		addNeighbor(pX, pY, srcIm);
	}


}
/* Purpose: check the neighbors evaluated coords
*			for valid values i.e. inside the image
*/
bool Pixel::checkCoords(int x, int y, cv::Mat* srcIm) {
	double pi = srcIm->at<double>(x, y);
	if (x >= 0 && x < srcIm->cols) {
		if (y >= 0 && y < srcIm->rows)
			return true;
	}

	return false;
}

// adding a neighbor only if it inside the picture and
// had a value in range [0, 1] i.e. not hole as well
void Pixel::addNeighbor(int x, int y, cv::Mat* srcIm) {
	if (checkCoords(x, y, srcIm)){
		if(srcIm->at<double>(x,y) != -1)
		_neighbors.push_back(Pixel(x, y, srcIm->at<double>(x, y)));
	}
}

bool Pixel::operator<(Pixel const & rhs) const
{
	if (this->getX() == rhs.getX()) {
		return this->getY() < rhs.getY();
	}
	return this->getX() < rhs.getX();
}


int Pixel::getX() const{
	return _x;
}

int Pixel::getY() const{
	return _y;
}

double Pixel::getIntensity() const{
	return _i;
}

Pixel::~Pixel() {
}



