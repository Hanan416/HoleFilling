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
		
		//std::vector<Pixel> _neighbors;	// Defined to be of length k in k-connected boundry
		std::vector<std::pair<int, int>> _neighbors;	// Defined to be of length k in k-connected boundry

		void setNeighbors(cv::Mat* srcIm, int k, bool allNeighbors);	// setting a Pixel neighbors according to k-connections, bool flag to add all neighbors or just the ones without -1 Intensity

		int getX() const;
		int getY() const;
		double getIntensity() const;

		bool checkCoords(int x, int y, cv::Mat* srcIm);		// check for valid image coords
		void addNeighbors(int x, int y, cv::Mat* srcIm);	// for exact solution, with HoleFilling::fillHole()
		void addAllNeighbors(int x, int y, cv::Mat* srcIm);	// for approximated linar solution with HoleFilling::fillHoleApprox()

		bool operator<(Pixel const &rhs) const;


	private:
		int _x;					// x index
		int _y;					// y index
		double _i;				// intensity value

};

	
#endif
