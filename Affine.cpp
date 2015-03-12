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

IplImage * AffineImage( IplImage * src )
{
	IplImage * res = cvCreateImage( cvSize(src->width, src->height), src->depth, src->nChannels );
	cvSet( res, CV_RGB(0,0,0) );

	CvPoint2D32f  srcTriang[3];
	srcTriang[0] = cvPoint2D32f(0,0);
	srcTriang[1] = cvPoint2D32f( src->width,0);
	srcTriang[2] = cvPoint2D32f(0,src->height);

	CvPoint2D32f  dstTriang[3];
	dstTriang[0] = cvPoint2D32f(50,50);
	dstTriang[1] = cvPoint2D32f(src->width,0);
	dstTriang[2] = cvPoint2D32f(0,src->height);


	CvMat * M = cvCreateMat(2,3,CV_32F);
	cvGetAffineTransform( srcTriang, dstTriang, M);
	cvWarpAffine(src, res, M);
	cvReleaseMat(&M);	
	return res;
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

int main(int argc, const char* argv[])
{
	IplImage * src = cvLoadImage("lena.jpg", 1);
	cvNamedWindow("Lena", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Lena2", CV_WINDOW_AUTOSIZE);
	drawPoly(src,0,0,src->width,0,src->width, src->height,0,src->height);

	cvSetMouseCallback( "Lena", onMouse );

	cvShowImage("Lena", src);
	cvShowImage("Lena2", AffineImage(src));
	
	cvCreateTrackbar("Q: ", 

	cvWaitKey();
	return 0;
}
