/*
 * LineTracking.cpp
 *
 *  Created on: 2018�~12��29��
 *      Author: yauch
 */

int HEIGHT=60;
#define WIDTH 80
#include <iostream>
#include "LineTracking.h"
using namespace std;

//get the range of value of pixel
//PixelRange GetRangeFromImage(int image[HEIGHT][WIDTH])
//{
//	PixelRange result;
//
//	result.MinValueActual=255;
//	result.MaxValueActual=0;
//	for(int i=0;i<HEIGHT;i++)
//	{
//		for(int j=0;j<WIDTH;j++)
//		{
//			if(image[i][j]<result.MinValueActual)
//			{
//				result.MinValueActual=image[i][j];
//			}
//			else if(image[i][j]>result.MaxValueActual)
//			{
//				result.MaxValueActual=image[i][j];
//			}
//		}
//	}
//	return result;
//}


//dynamically make the threshold
double DynamicThreshold(int image[][WIDTH])
{
	return .5;
}


//Tune the threshold
//void ThresholdTuning(int image[][WIDTH])
//{
//	PixelRange range=GetRangeFromImage(image);
//	int Threshold = DynamicThreshold(image);
//
//	for(int i=0;i<HEIGHT;i++)
//	{
//		for(int j=0;j<WIDTH;j++)
//		{
//			if (image[i][j] < (range.MaxValueActual - range.MinValueActual)*Threshold + range.MinValueActual)
//			{image[i][j] = 0;}
//			else if(image[i][j] > (range.MaxValueActual - range.MinValueActual)*Threshold + range.MinValueActual)
//			{image[i][j] = 255;}
//		}
//	}
//}

//get the geometry from a image
Line GetGeometry(int image[][80])
{
	//ThresholdTuning(image);
	Coordinate middleBlacks[HEIGHT];
	Line result;

	int length=0;
	for(int i=0;i<HEIGHT;i++)
	{
		int BlackCount = 0;
		int BlackSum = 0;
		for(int j=0;j<WIDTH;j++)
		{
			if (image[i][j] == 0)
			{
			 	BlackCount++;
			   	BlackSum+=j;
			}
		}

		if(BlackCount==0){continue;}
		int LineCenterX = BlackSum / BlackCount;
		Coordinate current={LineCenterX,i};
		middleBlacks[length++]=current;
	}

	int s1=0,s2=0,s3=0,s4=0;
	for (int i = 0 ;i<length;i++)// n is the number of center points collected
	{
	  s1 = s1 + middleBlacks[i].X*middleBlacks[i].Y;
	  s2 = s2 + middleBlacks[i].X;
	  s3 = s3 + middleBlacks[i].Y;
	  s4 = s4 + middleBlacks[i].X*middleBlacks[i].X;
	}

	double SlopeNumerator = length*s1 - s2*s3;
	int SlopeDenominator = length*s4 - s2*s2;


	if(!(SlopeDenominator<0.001&&SlopeDenominator>-0.001))
	{
		double Slope = SlopeNumerator/SlopeDenominator;

		result.Slope=Slope;
		int SumX=0,SumY=0;
		for (int i = 0 ;i<length;i++)// n is the number of points collected �V watch for 0 in the division!
		{ SumX = SumX + middleBlacks[i].X;
		  SumY = SumY + middleBlacks[i].Y;
		}
		double Intercept = SumY/length - Slope*SumX/length;
		result.Intercept=Intercept;
	}
	else if(SlopeDenominator==0&&SlopeNumerator!=0)
	{
		result.Slope=999;
	}
	return result;
}


void TestImageGeometry()
{


//
	::HEIGHT=60;
	//Line line=GetGeometry(image);
	//cout<<line.Intercept<<" and slope: "<<line.Slope<<endl;
//
//


}










