/*
 * pavlidis.h
 *
 *  Created on: 2018¦~12¤ë27¤é
 *      Author: yauch
 */



#ifndef __PAVLIDIS_H__
#define __PAVLIDIS_H__

#include <string.h>
typedef struct
{
	int imageData[36*36]={0};
	int 	width=36;
	int 	height=36;
	int 	widthStep=36;

}IplImage;

void BinarizeImage(IplImage, IplImage);

IplImage EdgeFinding(IplImage, IplImage);

void
Pavlidis_contour_tracing(int* srcbin,
						 int wid, int hei, int widstep,
						 int* dstbin,
						 int dst_wid, int dst_hei, int dst_widstep);



#endif /* PAVLIDIS_H_ */
