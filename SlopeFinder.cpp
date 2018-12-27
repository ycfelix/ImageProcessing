/*
 * SlopeFinder.cpp
 *
 *  Created on: 2018¦~12¤ë27¤é
 *      Author: yauch
 */

#include "SlopeFinder.h"

int IsValidPoint(int image[HEIGHT][WIDTH], int point, int i, int j)
{
	if(i<1||i>=HEIGHT-1||j<1||j>=WIDTH-1){return false;}
	if(image[i+1][j]==point)//down
	{
		if(image[i][j]==point)//current
		{
			return 1;
		}
	}
	return 0;
}


int PercentageSlope(int image[HEIGHT][WIDTH], int i, int j,float gradian)
{
	int TotalNumberOfBlack=0;
	int CurrentNumberOfBlack=0;
		for(int X_Position=j;X_Position<HEIGHT;X_Position++)
		{
			if(image[(int)(gradian*X_Position)][X_Position]==0)
			{
				CurrentNumberOfBlack++;
			}
			TotalNumberOfBlack++;
		}
	return  ((float)CurrentNumberOfBlack/(float)TotalNumberOfBlack)*100.0;
}



int MaxSlope(int image[HEIGHT][WIDTH], int i, int j)
{
	int MaxNumberSlope=0;
	int OptimalGradian=0;
	for(float slope=0;slope<=1;slope+=0.1)
	{
		int Percent=PercentageSlope(image,i,j,slope);
		if(Percent>MaxNumberSlope)
		{
			MaxNumberSlope=Percent;
			OptimalGradian=slope;
		}
	}

	return OptimalGradian;
}

int ImageProcessing(int image[HEIGHT][WIDTH])
{
	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<WIDTH;j++)
		{
			if(IsValidPoint(image, image[i][j],i,j)==1)
			{
				return MaxSlope(image,i,j);
			}
		}
	}
	return 0;
}



