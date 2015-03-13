#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <iostream>
#include <cmath>
#include <string>


IplImage * TranslateImage( IplImage * src, int dx, int dy )
{
	IplImage * res = cvCreateImage( cvSize(src->width, src->height), src->depth, src->nChannels );
	cvSet( res, CV_RGB(0,0,0) );

	float a[] = { 1, 0, dx,
		0, 1, dy
	};
	CvMat * M = cvCreateMat(2,3,CV_32F);
	cvSetData(M, a, sizeof(float)*3);
	cvWarpAffine(src, res, M, CV_INTER_LINEAR);
	cvReleaseMat(&M);
	return res;
}
static void onMouse(  int event, int x, int y, int , void * srcp)
{
	if( event != CV_EVENT_LBUTTONDOWN )
		return;
	IplImage * src = (IplImage *) srcp;
	
	cvShowImage("Lena",TranslateImage( src, x,y));

}
int main(int argc, const char* argv[])
{
	IplImage * src = cvLoadImage("lena.jpg", 1);
	cvNamedWindow("Lena", CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback( "Lena", onMouse, src );
	cvShowImage("Lena", src);
	cvWaitKey();
	return 0;
}
