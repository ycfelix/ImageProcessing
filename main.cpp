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
using namespace std;

int main()
{


	//Rotate90degrees(image);

	//TestImageGeometry();

	Line geometry=OptimalSlope();
	cout<<"slope: "<<geometry.slope<< " intercept is: "<<geometry.intercept<<endl;

	return 0;
}

