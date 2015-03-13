#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <iostream>
#include <cmath>
#include <string>

static void onMouse(  int event, int x, int y, int , void*)
{
	if( event != CV_EVENT_LBUTTONDOWN )
		return;

}
void drawPoly( IplImage * src, int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int dx4, int dy4 )
{
	CvPoint curve1[4];
	curve1[0].x = dx1;
	curve1[0].y = dy1;
	curve1[1].x = dx2;
	curve1[1].y = dy2;
	curve1[2].x = dx3;
	curve1[2].y = dy3;
	curve1[3].x = dx4;
	curve1[3].y = dy4;
	CvPoint * curves [1];
	curves[0] = curve1;
	int vertexCount[1];
	vertexCount[0] = 4;
	cvPolyLine( src, curves, vertexCount, 1, true, cvScalar(255,255,255), 5);
}

IplImage * PerspectiveImage( IplImage * src )
{
	IplImage * res = cvCreateImage( cvSize(src->width, src->height), src->depth, src->nChannels );
	cvSet( res, CV_RGB(0,0,0) );

	CvPoint2D32f  srcTriang[4];
	srcTriang[0] = cvPoint2D32f(0,0);
	srcTriang[1] = cvPoint2D32f(src->width,0);
	srcTriang[2] = cvPoint2D32f(0,src->height);
	srcTriang[3] = cvPoint2D32f(src->width, src->height);

	CvPoint2D32f  dstTriang[4];
	dstTriang[0] = cvPoint2D32f(0,0);
	dstTriang[1] = cvPoint2D32f(src->width,0);
	dstTriang[2] = cvPoint2D32f(100,src->height-50);
	dstTriang[3] = cvPoint2D32f(src->width-100,src->height-50);

	CvMat * M = cvCreateMat(3,3,CV_32F);
	cvGetPerspectiveTransform( srcTriang, dstTriang, M);
	cvWarpPerspective(src, res, M);
	cvReleaseMat(&M);
	return res;
}
int main(int argc, const char* argv[])
{
	IplImage * src = cvLoadImage("lena.jpg", 1);
	cvNamedWindow("Lena", CV_WINDOW_AUTOSIZE);
	drawPoly(src,0,0,src->width,0,src->width, src->height,0,src->height);

	cvShowImage("Original", src);
	cvShowImage("Traslade", PerspectiveImage(src));


	cvWaitKey();
	return 0;
}
