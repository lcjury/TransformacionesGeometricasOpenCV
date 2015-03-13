#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <iostream>
#include <cmath>
#include <string>

int Alpha;
int centerX;
int centerY;
IplImage * src = cvLoadImage("lena.jpg", 1);

IplImage * RotateImage( IplImage * src )
{
	IplImage * res = cvCreateImage( cvSize(src->width, src->height), src->depth, src->nChannels );
	cvSet( res, CV_RGB(0,0,0) );

	CvMat * M = cvCreateMat(2,3,CV_32F);

	CvPoint2D32f center = cvPoint2D32f( centerX, centerY  );

	cv2DRotationMatrix( center, Alpha, 1.0, M);
	cvWarpAffine(src, res, M);
	cvReleaseMat(&M);
	return res;
}

static void onMouse(  int event, int x, int y, int , void*)
{
	if( event != CV_EVENT_LBUTTONDOWN )
		return;
	centerX = x;
	centerY = y;
	cvShowImage("Lena", RotateImage(src));
}

void onChange( int )
{
	cvShowImage("Lena", RotateImage(src));
}

int main(int argc, const char* argv[])
{
	cvNamedWindow("Lena", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar( "Angulo", "Lena", &Alpha, 360, onChange );
	cvSetMouseCallback( "Lena", onMouse);
	centerX = src->width/2;
	centerY = src->height/2;
	onChange(0);
	cvWaitKey();
	return 0;
}
