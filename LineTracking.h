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
	int X=0;
	int Y=0;
}Coordinate;

Coordinate* GetMiddleCoordinate(int image[][WIDTH]);


#endif /* LINETRACKING_H_ */
