/*
 * LineTracking.h
 *
 *  Created on: 2018¦~12¤ë29¤é
 *      Author: yauch
 */

#ifndef LINETRACKING_H_
#define LINETRACKING_H_
typedef struct
{
	int MinValueActual=0;
	int MaxValueActual=0;
}PixelRange;

typedef struct
{
	int X	= 0;
	int Y	= 0;
}Coordinate;

typedef struct
{
	double Slope		=	0;
	double Intercept	=	0;
}Line;

// return a Line object which contains the slope and intercept
Line GetGeometry(int image[]);

//testing using a 36*36 size image
void TestImageGeometry();

#endif /* LINETRACKING_H_ */
