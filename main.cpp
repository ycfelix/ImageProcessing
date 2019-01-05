/*
 * main.cpp
 *
 *  Created on: 2018¦~12¤ë27¤é
 *      Author: yauch
 */


//#include "pavlidis.h"
//#include "ImageTransform.h"
//#include "LineTracking.h"
#include "logic.h"
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	//Line geometry=GetGeometry(img);
	//cout<<"slope: "<<geometry.Slope<< " intercept is: "<<geometry.Intercept<<endl;

	Line geometry=OptimalSlope();
	cout<<"slope: "<<geometry.slope<< " intercept is: "<<geometry.intercept<<endl;

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cout<<" time used: "<<elapsed.count()<<endl;
	return 0;
}

