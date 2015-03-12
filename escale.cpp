#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <iostream>
#include <cmath>
#include <string>

int ScaleX;
int ScaleY;
IplImage * src;
IplImage * res;

IplImage * ScaleImage( )
{	
	float dw = ((float)ScaleX)/100;
	float dh = ((float)ScaleY)/100;

	cvSet( res, CV_RGB(0,0,0) );

	float a[] = { dw, 0, 0,
	  	      0, dh, 0
				};
	CvMat * M = cvCreateMat(2,3,CV_32F);
	cvSetData(M, a, sizeof(float)*3);
	cvWarpAffine(src, res, M, CV_INTER_LINEAR);
	cvReleaseMat(&M);
	return res;
}
void onChange( int )
{
	cvShowImage("Lena", ScaleImage() );
}


int main(int argc, const char* argv[])
{
	src = cvLoadImage("lena.jpg", 1);
	res = cvCreateImage( cvSize(src->width, src->height), src->depth, src->nChannels );

	ScaleX = 100;
	ScaleY = 100;
	cvNamedWindow("Lena", CV_WINDOW_AUTOSIZE);
	cvShowImage("Lena", src);
	cvCreateTrackbar("Escala X", "Lena", &ScaleX, 200, onChange );
	cvCreateTrackbar("Escala Y", "Lena", &ScaleY, 200, onChange );

	cvWaitKey();

	return 0;
}
