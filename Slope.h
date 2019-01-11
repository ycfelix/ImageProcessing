#define WIDTH 80
#define HEIGHT 60
//#include "stm32f4xx.h"
typedef float num;
#include <math.h>
#include <iostream>
using namespace std;
//typedef int uint8_t;

//typedef int uint8_t;
typedef struct
{
	int x;
	int y;
} Coordinate;

typedef struct
{
	Coordinate array[80];
	int size;
}List;

typedef struct
{
	List* element1;
	List* element2;
}Tuple;

typedef struct
{
	float slope;
	int intercept;
	float percentage;
	int angle;
} Line;

typedef struct
{
	Line candidate[3];
	int counter;
}Candidate;


Candidate OptimalSlope(uint8_t image[]);
int HasCross(Candidate);
float FindAngle(uint8_t image[]);
