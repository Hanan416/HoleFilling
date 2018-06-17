#pragma once

#ifndef HoleFilling_h
#define HoleFilling_h

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Pixel.h"
#include <set>
#include <math.h>


#include <iostream>

#define HOLE -1

/*	Macros for calculating the new intensity of a hole Pixel x i.e I(x)
	as a product of the sum weights "w(y_i,x)" of the boundry Pixels y_i, 
	and their Intensity I(y_i), normalized by the sum of weights 
	Formula:
		for each hole Pixel x
		and each boundry Pixel y_i

		I(x) = sum_weights * I(y_i)) / sum_weights

		where sum_weights = sum of w(y_i, x) for each boundry Pixel y_i


	for each y_i the value of w(y_i,x) calculated as follows
	w_z(y_i,x) = 1/(pow(dist(x,y_i), POW_Z) + EPSILON)
*/

#define EPSILON						0.00000001		// to avoid devision by zero, edit this value for different results
#define POW_Z						20				// edit this value for different results, higher z -> more accurate
#define WEIGHT(x, y_i_x, y_i_y)		1 / (pow(dist(x, y_i_x, y_i_y), POW_Z) + EPSILON)	// w(y_i, x), change formula for different results, NOTE: x is Pixel and y_i defined by its coordinates

class HoleFilling
{
public:
	HoleFilling(cv::Mat* srcIm, int k);
	~HoleFilling() {};

	void findHole();
	cv::Mat fillHole();
	double dist(Pixel x, int y_i_x, int y_i_y);

private:
	cv::Mat* _srcIm;	// the source image matrix
	cv::Mat _resIm;		// the result image matrix
	int _k;				// the k-connected neighbors

	std::set<Pixel> holePixels;
	std::set<std::pair<int, int>> boundryIndexes;

};

#endif
