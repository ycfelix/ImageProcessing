/*
 * pavlidis.cpp
 *
 *  Created on: 2018¦~12¤ë27¤é
 *      Author: yauch
 */


#include "pavlidis.h"

typedef enum {
	RIGHT=1, BOTTOM=2, LEFT=3, TOP=4
} Direction;

typedef struct tagPOINT {
	long x;
	long y;
} POINT,POINTL,*PPOINT,*LPPOINT,*PPOINTL,*LPPOINTL;


void BinarizeImage(IplImage src_img, IplImage src_bin)
{
		// Binary
		for (int j=0;j<src_img.height;j++)
		{
			for (int i=0;i<src_img.width;i++)
			{
				int g = src_img.imageData[j*src_img.widthStep+i];

				if( g > 128 )
				{
					src_bin.imageData[j*src_bin.widthStep+i] = 0;
				}
				else
				{
					src_bin.imageData[j*src_bin.widthStep+i] = 255;
				}
			}
		}
}



POINT
Pavlidis_start_point(int* srcbin,
					 int wid, int hei, int widstep)
{
	int x=0, y=0;
	POINT startpoint = {-1, -1};

	for (y=1;y<hei-1;y++)
	{
		for (x=1;x<wid-1;x++)
		{
			if( ! srcbin[y*widstep+x] )
				continue;

			if( ! srcbin[y*widstep+x-1] )
			{
				startpoint.x = x;
				startpoint.y = y;
				return startpoint;
			}
		}
	}

	return startpoint;
}


int
Pavlidis_TurnLeft(int d)
{
	int dnew = d - 1;
	if(dnew == 0)
		dnew = 4;
	return dnew;
}

int
Pavlidis_TurnRight(int d)
{
	int dnew = d + 1;
	if(dnew == 5)
		dnew = 1;
	return dnew;
}

IplImage EdgeFinding(IplImage src_bin, IplImage dst_contour)
{

		Pavlidis_contour_tracing(src_bin.imageData, src_bin.width, src_bin.height, src_bin.widthStep,
			dst_contour.imageData, dst_contour.width, dst_contour.height, dst_contour.widthStep);

		return dst_contour;
}


void
Pavlidis_contour_tracing(int* srcbin,
						 int wid, int hei, int widstep,
						 int* dstbin,
						 int dst_wid, int dst_hei, int dst_widstep)
{
	POINT		startpoint;
	Direction	dir = TOP;
	POINT		cpix;
	int			rightturn_step = 0;
	int			tracetime = 4;
	int			maxloop = 1E5;

	startpoint = Pavlidis_start_point(srcbin, wid, hei, widstep);

	if(startpoint.x < 0)
		return;
	memset(dstbin, 0, dst_widstep*dst_hei);

	cpix = startpoint;
	dir = TOP;
	while( maxloop-- )
	{
		POINT P1,P2,P3;
		int p1, p2, p3;

		// cpix : Current position
		if( cpix.x == startpoint.x
			&&
			cpix.y == startpoint.y)
		{
			tracetime--;

			if(tracetime == 0)
				break;
		}

		switch (dir)
		{
		case TOP:
			// * * *
			//   o
			P1.x=cpix.x-1; P1.y=cpix.y-1;
			P2.x=cpix.x; P2.y=cpix.y-1;
			P3.x=cpix.x+1; P3.y=cpix.y-1;
			break;
		case LEFT:
			// *
			// * o
			// *
			P1.x=cpix.x-1; P1.y=cpix.y+1;
			P2.x=cpix.x-1; P2.y=cpix.y;
			P3.x=cpix.x-1; P3.y=cpix.y-1;
			break;
		case RIGHT:
			//   *
			// o *
			//   *
			P1.x=cpix.x+1; P1.y=cpix.y-1;
			P2.x=cpix.x+1; P2.y=cpix.y;
			P3.x=cpix.x+1; P3.y=cpix.y+1;
			break;
		case BOTTOM:
			//   o
			// * * *
			P1.x=cpix.x+1; P1.y=cpix.y+1;
			P2.x=cpix.x; P2.y=cpix.y+1;
			P3.x=cpix.x-1; P3.y=cpix.y+1;
			break;
		};


		p1= srcbin[P1.y*widstep+P1.x];
		p2= srcbin[P2.y*widstep+P2.x];
		p3= srcbin[P3.y*widstep+P3.x];

		if(p1)
		{
			dstbin[cpix.y*dst_widstep+cpix.x] = 255;

			cpix = P1;
			dir = (Direction) Pavlidis_TurnLeft(dir);
			rightturn_step = 0;
		}
		else if(p2)
		{
			dstbin[cpix.y*dst_widstep+cpix.x] = 255;

			cpix = P2;
			rightturn_step = 0;
		}
		else if(p3)
		{
			dstbin[cpix.y*dst_widstep+cpix.x] = 255;

			cpix = P3;
			rightturn_step = 0;
		}
		else
		{
			dir = (Direction) Pavlidis_TurnRight(dir);
			rightturn_step++;

			if(rightturn_step == 3)
				break;
		}
	}
}

