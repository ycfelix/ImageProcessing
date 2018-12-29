/*
 * ImageTransform.h
 *
 *  Created on: 2018¦~12¤ë27¤é
 *      Author: yauch
 */
#include <stdio.h>
#ifndef IMAGETRANSFORM_H_
#define IMAGETRANSFORM_H_



#define HEIGHT 36
#define WIDTH  36
void Rotate90degrees(int image[HEIGHT][WIDTH]);

typedef enum
{
	blur,sharpe,emboss,sobel_emboss,box
}
Filter;

void GetFilter(Filter filter,double matrix[][3]);

void ImageFiltering(int image[HEIGHT][WIDTH], double filter[][3]);

void Rotate90degrees(int image[HEIGHT][WIDTH]);



#endif /* IMAGETRANSFORM_H_ */
