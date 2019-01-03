#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "matrix.h"
#include <vector>
#include <math.h>
using namespace std;
#define WIDTH 80
#define HEIGHT 60

struct Line
{
	float slope;
	float intercept;
};
struct Coordinate
{
	int x;
	int y;
};
vector<Coordinate> Top;
vector<Coordinate> Left;
vector<Coordinate> Right;
vector<Coordinate> Bottom;

void GetPixelsForTop()
{
	for(int i=0;i<80;i++)
	{
		if(image[0][i]==0)
		{
			Coordinate coordinate={i,0};
			Top.push_back(coordinate);
		}
	}
}
void GetPixelsForLeft()
{
	for(int i=0;i<60;i++)
	{
		if(image[i][0]==0)
		{
			Coordinate coordinate={0,i};
			Left.push_back(coordinate);
		}
	}
}
void GetPixelsForBottom()
{
	for(int i=0;i<80;i++)
	{
		if(image[59][i]==0)
		{
			Coordinate coordinate={i,59};
			Bottom.push_back(coordinate);
		}
	}
}
void GetPixelsForRight()
{
	for(int i=0;i<60;i++)
	{
		if(image[i][79]==0)
		{
			Coordinate coordinate={79,i};
			Right.push_back(coordinate);

		}
	}
}

Line GetGeometry(Coordinate source, Coordinate destination);
float LinePercentage(Line line);
int main()
{
	Line temp={0,0};
	Line* max=&temp;

	GetPixelsForTop();
	GetPixelsForLeft();
	GetPixelsForRight();
	GetPixelsForBottom();

	for(int i=0;i<Top.size();i++)
	{
		Coordinate source=Top.at(i);
		for(int j=0;j<Bottom.size();j++)
		{
			Coordinate destination=Top.at(j);
			Line result=GetGeometry(source,destination);
			if(LinePercentage(result)>LinePercentage(*max))
			{
				max=&result;
			}
		}
	}




}

Line GetGeometry(Coordinate source, Coordinate destination)
{
	float slope=(float)((source.y-destination.y)/(source.x-destination.y));
	float intercept=source.y-source.x*slope;
	Line result={slope, intercept};
	return result;
}

float LinePercentage(Line line)
{
	int TotalPixel=0;
	int NumberOfBlack=0;
	for(int i=0;i<WIDTH;i++)
	{
		int y_cor=line.slope*i+line.intercept;
		if(y_cor>=0&&y_cor<HEIGHT)
		{
			if(image[y_cor][i]==0)
			{
				NumberOfBlack++;
			}
			TotalPixel++;
		}
	}
	for(int i=0;i<HEIGHT;i++)
	{
		int x_cor=round((float)((i-line.intercept)/line.slope));
		if(x_cor>=0&&x_cor<WIDTH)
		{
			if(image[i][x_cor]==0)
			{
				NumberOfBlack++;
			}
			TotalPixel++;
		}
	}

	if(TotalPixel<0.5*HEIGHT)
	{
		return 0;
	}
	return (float)(NumberOfBlack/TotalPixel)*100;
}








