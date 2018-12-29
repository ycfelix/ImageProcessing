/*
 * ImageTransform.cpp
 *
 *  Created on: 2018¦~12¤ë27¤é
 *      Author: yauch
 */

#include "ImageTransform.h"
#include <string.h>

double factor = 1.0;
double bias = 0.0;

void GetFilter(Filter filter,double matrix[][3])
{

	switch(filter)
	{
	//case blur:memcpy(matrix,blurer,3*3*sizeof(double));break;
	case sharpe:matrix=sharpen_kernel;break;
	case emboss:matrix=emboss_kernel;break;
	case sharpener:matrix=sharpen_kernel;break;
	case sobel_emboss:matrix=sobel;break;
	case box: matrix=box_blur;break;
	default: break;
	}
}

void Rotate90degrees(int image[HEIGHT][WIDTH])
{
   // Consider all squares one by one
    for (int x = 0; x < WIDTH / 2; x++)
    {
        // Consider elements in group of 4 in
        // current square
        for (int y = x; y < WIDTH-x-1; y++)
        {
            // store current cell in temp variable
            int temp = image[x][y];

            // move values from right to top
            image[x][y] = image[y][WIDTH-1-x];

            // move values from bottom to right
            image[y][WIDTH-1-x] = image[WIDTH-1-x][WIDTH-1-y];

            // move values from left to bottom
            image[WIDTH-1-x][WIDTH-1-y] = image[WIDTH-1-y][x];

            // assign temp to left
            image[WIDTH-1-y][x] = temp;
        }
    }
}

int min(int x,int y)
{
return x>y?y:x;
}
int max(int x,int y)
{
return x>y?x:y;
}

void ImageFiltering(int image[][WIDTH], double filter[][3])
{

	int result[HEIGHT][WIDTH]={0};
	for(int y = 0; y < HEIGHT; y++)
	for(int x = 0; x < WIDTH; x++)
	{
		double color=0;
	    //set the color values in the arrays
	    for(int filterY = 0; filterY < 3; filterY++)
	    	for(int filterX = 0; filterX < 3; filterX++)
	    	{
	    		int imageX = (x - 3 / 2 + filterX + WIDTH) % WIDTH;
	    		int imageY = (y - 3 / 2 + filterY + HEIGHT) % HEIGHT;
	    		color += (double)(image[imageY][imageX]* filter[filterY][filterX]);

	    	}
	    result[y][x]= min(max(int(factor * color + bias), 0), 255);
	 }
	memcpy(image,result,HEIGHT*WIDTH*sizeof(int));

}


