/*
 * LineTracking.cpp
 *
 *  Created on: 2018¦~12¤ë29¤é
 *      Author: yauch
 */

#define HEIGHT 36
#define WIDTH 36
#include "LineTracking.h"


PixelRange GetRangeFromImage(int image[HEIGHT][WIDTH])
{
	PixelRange result;

	result.MinValueActual=255;
	result.MaxValueActual=0;
	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<WIDTH;j++)
		{
			if(image[i][j]<result.MinValueActual)
			{
				result.MinValueActual=image[i][j];
			}
			else if(image[i][j]>result.MaxValueActual)
			{
				result.MaxValueActual=image[i][j];
			}
		}
	}
	return result;
}

double DynamicThreshold(int image[][WIDTH])
{
	return .24;
}



void ThresholdTuning(int image[][WIDTH], PixelRange range)
{
	int Threshold = DynamicThreshold(image);

	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<WIDTH;j++)
		{
			if (image[i][j] < (range.MaxValueActual - range.MinValueActual)*Threshold + range.MinValueActual)
			{image[i][j] = 0;}
			else
			{image[i][j] = 255;}
		}
	}
}
Coordinate* GetMiddleCoordinate(int image[][WIDTH])
{
	Coordinate* middleBlacks=new Coordinate[HEIGHT];

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

	int SlopeNumerator = length*s1 - s2*s3;
	int SlopeDenominator = length*s4 - s2*s2;
	if(!(SlopeDenominator<0.0001&&SlopeDenominator>0))
	{
		int Slope = SlopeNumerator/SlopeDenominator;

		int SumX=0,SumY=0;
		for (int i = 0 ;i<length;i++)// n is the number of points collected ¡V watch for 0 in the division!
		{ SumX = SumX + middleBlacks[i].X;
		  SumY = SumY + middleBlacks[i].Y;
		}
		int Intercept = SumY/length - Slope*SumX/length;
	}



	return middleBlacks;
}










