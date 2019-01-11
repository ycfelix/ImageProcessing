#include "Slope.h"
typedef uint8_t uint9_t;
typedef uint8_t pixel;
#define Color 0
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#include <vector>
#include <math.h>

vector<Line> r;

/* TODO: count the dm/dx and dm/dy for the camera and multiply it to the slope generated
 *
 *
 *
 * */


bool compareInterval(Line i1, Line i2)
{
    return (i1.intercept < i2.intercept);
}


Line GetGeometry(Coordinate* source, Coordinate* destination)
{
	Line result={0.001,0,0,0};

	//TODO: handle the horizontal geometry
	if((source->x-destination->x)>=-0.001&&(source->x-destination->x)<=0.001){return result;}


	float slope=((float)source->y-(float)destination->y)/((float)source->x-(float)destination->x);
	int intercept=source->y-source->x*slope;
	result.slope=slope;
	result.intercept=intercept;
	result.percentage=0;
	result.angle=atan(slope)* 180.0 / 3.14159;
	return result;
}

float LinePercentage(Line* line,uint9_t image[])
{
	int TotalPixel=0;
	int NumberOfBlack=0;
	for(int i=0;i<WIDTH;i++)
	{

		int y_cor=(float)(line->slope*i)+line->intercept;
		if(y_cor>=0&&y_cor<HEIGHT)
		{
			if(image[y_cor*WIDTH+i]==Color)
			{
				NumberOfBlack++;
			}
			TotalPixel++;
		}

		if(i<HEIGHT)
		{
			if(line->slope>=-0.005&&line->slope<=0.005)
			{
				continue;
			}
			int x_cor=(float)((float)(i-line->intercept)/(float)line->slope);
			if(x_cor>=0&&x_cor<WIDTH)
			{
				if(image[i*WIDTH+x_cor]==Color)
				{
					NumberOfBlack++;
				}
				TotalPixel++;
			}
		}
	}

	if(TotalPixel<0.1*HEIGHT)
	{
		return 0;
	}
	return (num)((num)NumberOfBlack/(num)TotalPixel)*60.0+(float)((float)NumberOfBlack/130.0)*40.0;
}





void GetPixels(List* Top,List* Left,List* Right,List* Bottom,uint9_t image[])
{
	for(int i=0;i<80;i++)
	{
		if(i<HEIGHT)
		{
			if(image[i*WIDTH+3]==Color)
			{
				Coordinate coordinate={3,i};
				Left->array[Left->size++]=coordinate;
			}
			if(image[i*WIDTH+70]==Color)
			{
				Coordinate coordinate={70,i};
				Right->array[Right->size++]=coordinate;
			}
		}


		if(image[i+160]==Color)
		{
			Coordinate coordinate={i,2};
			Top->array[Top->size++]=coordinate;
		}
		if(image[54*WIDTH+i]==Color)
		{
			Coordinate coordinate={i,54};
			Bottom->array[Bottom->size++]=coordinate;
		}
	}
}


int CanAddTo(Candidate* candidate,Line now)
{
	for(int i=0;i<candidate->counter&&i<3;i++)
	{
		if(abs(abs(candidate->candidate[i].angle)-abs(now.angle))<10)
		{
			if(abs(candidate->candidate[i].intercept-now.intercept)<5)
			{
				return 0;
			}
		}
	}
	return 1;
}

num FindMaxSlope(Candidate* candidate,Line* max, List* s, List* d, num maxPercentage, pixel image[])
{
		int maxIntercept = max->intercept;
		float maxSlope = max->slope;
		num LastPercentage = maxPercentage;
		int angle=max->angle;

		Coordinate* source = &s->array[0];
		Coordinate* srcend = source + s->size;

		while (source < srcend)
		{
			Coordinate* destination = &d->array[0];
			Coordinate* dstend = destination + d->size;
			while(destination < dstend)
			{
				Line result=GetGeometry(source,destination);
				num percent=LinePercentage(&result,image);

				if(percent>LastPercentage)
				{

					LastPercentage=percent;
					maxIntercept=result.intercept;
					maxSlope=result.slope;
					result.percentage=percent;
					angle=result.angle;

					if(CanAddTo(candidate,result)==1)
					{
						//cout<<" slope: "<<result.slope<<" inter: "<<result.intercept;
						//cout<<" percentage "<<percent<<" angle: "<<angle<<endl;
						candidate->candidate[candidate->counter++%3]=result;
					}
				}

				destination++;
			}
			source++;
		}
		max->intercept = maxIntercept;
		max->slope = maxSlope;
		max->percentage=LastPercentage;
		max->angle=angle;
		return LastPercentage;
}


Candidate OptimalSlope(pixel image[])
{

	Line temp={0.001,0,0,0};
	Line* max=&temp;

	Candidate* result;
	Candidate t;
	t.counter=0;
	result=&t;

	List Top;
	List Left;
	List Right;
	List Bottom;
	Top.size=0;
	Left.size=0;
	Right.size=0;
	Bottom.size=0;

	List* edge1=&Top;
	List* edge2=&Left;
	List* edge3=&Right;
	List* edge4=&Bottom;

	GetPixels(edge1,edge2,edge3,edge4,image);

	Tuple first={edge1,edge2};
	Tuple second={edge1,edge3};
	Tuple third={edge1,edge4};
	Tuple forth={edge2,edge3};
	Tuple fifth={edge2,edge4};
	Tuple sixth={edge3,edge4};

	Tuple* Graph[6]={&first,&second,&third,&forth,&fifth,&sixth};

	num maxPercentage = LinePercentage(max, image);
	for(int i=0;i<6;i++)
	{
		maxPercentage = FindMaxSlope(result,max,Graph[i]->element1,Graph[i]->element2,maxPercentage,image);
	}
	return *result;
}

int HasCross(Candidate candidate)
{

	if(abs(abs(candidate.candidate[0].angle)-abs(candidate.candidate[2].angle))>70)
	{
		return 1;
	}
	if(abs(abs(candidate.candidate[1].angle)-abs(candidate.candidate[2].angle))>70)
	{
		return 1;
	}
	if(abs(abs(candidate.candidate[0].angle)-abs(candidate.candidate[1].angle))>70)
	{
		return 1;
	}

	return 0;
}

//whole new part of the function
void GetPixelsInMiddle(List* Horizontal,uint9_t image[])
{
	for(int i=0;i<80;i++)
	{
		if(image[WIDTH*(HEIGHT/2-1)+i]==Color)
		{
			Coordinate coordinate={i,HEIGHT/2-1};
			Horizontal->array[Horizontal->size++]=coordinate;
		}
	}
}


Coordinate FindEndPointP(Line* SegmentSlope,pixel image[])
{
	//this one should consider -ve slope and positive slope
	int y=29;
	int x=(y-SegmentSlope->intercept)/SegmentSlope->slope;
	while(x<HEIGHT&&y<WIDTH&&image[y*WIDTH+x]==Color)
	{
		x++;
		y=SegmentSlope->slope*x+SegmentSlope->intercept;
	}

	Coordinate result={x,y};
	return result;
}


Coordinate FindEndPointN(Line* SegmentSlope,pixel image[])
{
	//this one should consider -ve slope and positive slope
	int y=29;
	int x=(y-SegmentSlope->intercept)/SegmentSlope->slope;
	while(x<HEIGHT&&y<WIDTH&&image[y*WIDTH+x]==Color)
	{
		x--;
		y=SegmentSlope->slope*x+SegmentSlope->intercept;
	}

	Coordinate result={x,y};
	return result;
}




float FindAngle(pixel image[])
{
	Candidate* result;
	Candidate t;
	t.counter=0;
	result=&t;

	List Top;
	List Left;
	List Right;
	List Bottom;
	List Horizontal;
	Top.size=0;
	Left.size=0;
	Right.size=0;
	Bottom.size=0;
	Horizontal.size=0;

	List* edge1=&Top;
	List* edge2=&Left;
	List* edge3=&Right;
	List* edge4=&Bottom;
	List* edge5=&Horizontal;


	GetPixels(edge1,edge2,edge3,edge4,image);
	GetPixelsInMiddle(edge5, image);

	Tuple first={edge1,edge5};
	Tuple second={edge5,edge4};
	Tuple third={edge3,edge5};
	Tuple forth={edge2,edge5};

	Tuple* Graph[4]={&first,&second,&third,&forth};

	for(int i=0;i<4;i++)
	{
		Line temp={0.01,0,0,0};
		Line* max=&temp;
		float firstSegment = FindMaxSlope(result,max,Graph[i]->element1,Graph[i]->element2,0,image);

		cout<<"firstSegment percent"<<firstSegment<<endl;
		if(firstSegment>52)
		{


			//it means it pass the horizontal line and its
			Coordinate EndPoint={0,0};
			if(max->slope<0)
			{
				Coordinate t=FindEndPointN(max,image);
				EndPoint.x=t.x;
				EndPoint.y=t.y;
			}
			else
			{

				Coordinate t=FindEndPointP(max,image);
				EndPoint.x=t.x;
				EndPoint.y=t.y;
			}

			List temp1;
			temp1.size=1;
			temp1.array[0]=EndPoint;
			List* ptr=&temp1;

			switch(i)
			{
			case 0:
				{			Line e2={0.001,0,0,0};
							max=&e2;
							int percent2=FindMaxSlope(result,max,ptr,edge2,0,image);
							Line e3={0.001,0,0,0};
							max=&e3;
							int percent3=FindMaxSlope(result,max,ptr,edge3,0,image);
							Line e4={0.001,0,0,0};
							max=&e4;
							int percent4=FindMaxSlope(result,max,ptr,edge4,0,image);

							cout<<"percent4: "<<percent4<<" slope "<<max->slope<<endl;
							int maximum=MAX(MAX(percent2,percent3),percent4);

							if(maximum==percent2){return abs(abs(e2.angle)+abs(temp.angle));}

							if(maximum==percent3){return abs(abs(e3.angle)+abs(temp.angle));}
							if(maximum==percent4){return abs(abs(e3.angle)+abs(temp.angle));}
			break;
			}


			case 1:{
							Line e2={0.001,0,0,0};
							max=&e2;
							int percent1=FindMaxSlope(result,max,edge1,ptr,0,image);
							Line e3={0.001,0,0,0};
							max=&e3;
							int percent2=FindMaxSlope(result,max,edge2,ptr,0,image);
							Line e4={0.001,0,0,0};
							max=&e4;
							int percent3=FindMaxSlope(result,max,ptr,edge3,0,image);
							int maximum=MAX(MAX(percent1,percent2),percent3);

							if(maximum==percent1){return abs(abs(e2.angle)+abs(temp.angle));}


							if(maximum==percent2){return abs(abs(e3.angle)+abs(temp.angle));}

							if(maximum==percent3){return abs(abs(e4.angle)+abs(temp.angle));}
			break;}

			case 2:{
							Line e2={0.001,0,0,0};
							max=&e2;
							int percent2=FindMaxSlope(result,max,ptr,edge4,0,image);

							int maximum=percent2;
							if(maximum==percent2){return abs(abs(e2.angle)+abs(temp.angle));}
			break;}

			case 3:
			{

				Line e2={0.001,0,0,0};
				max=&e2;
				int percent2=FindMaxSlope(result,max,ptr,edge4,0,image);
				int maximum=percent2;
				if(maximum==percent2){return abs(abs(e2.angle)+abs(temp.angle));}
				break;
			}
			}
		}

	}
	return 0;
}





