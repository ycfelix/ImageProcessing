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
	blur,sharpe,emboss,sharpener,sobel_emboss,box
}
Filter;

//static double blurer[3][3] =
//{
//{1/9.0, 1/9.0, 1/9.0},
//{1/9.0, 1/9.0, 1/9.0},
//{1/9.0, 1/9.0, 1/9.0}
//};


static double emboss_kernel[3][3] = {
  -2., -1.,  0.,
  -1.,  1.,  1.,
  0.,  1.,  2.,
};

static double sharpen_kernel[3][3] = {
  -1.0, -1.0, -1.0,
  -1.0,  9.0, -1.0,
  -1.0, -1.0, -1.0
};
static double sobel[3][3] = {
  -1., -2., -1.,
  0.,  0.,  0.,
  1.,  2.,  1.,
};
static double box_blur[3][3] = {
  1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
};

void GetFilter(Filter filter,double matrix[][3]);

void ImageFiltering(int image[HEIGHT][WIDTH], double filter[][3]);





#endif /* IMAGETRANSFORM_H_ */
