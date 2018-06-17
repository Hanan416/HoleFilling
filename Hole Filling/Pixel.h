#pragma once

/*
* Pixel class  
* Defines a Pixel attributes and
* Useful methods
*/

#ifndef Pixel_h
#define Pixel_h

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

class Pixel
{
	public:
		Pixel();						
		Pixel(int x, int y, double i);
		~Pixel();					
		
		std::vector<Pixel> _neighbors;	// Defined to be of length k in k-connected boundry

		void setNeighbors(cv::Mat* srcIm, int k);			// setting a Pixel neighbors according to k-connections
		int getX() const;
		int getY() const;
		double getIntensity() const;

		bool checkCoords(int x, int y, cv::Mat* srcIm);		// check for valid image coords
		void addNeighbor(int x, int y, cv::Mat* srcIm);
		bool operator<(Pixel const &rhs) const;


	private:
		int _x;					// x index
		int _y;					// y index
		double _i;				// intensity value

};

	
#endif
