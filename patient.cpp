// patient.cpp : 定义控制台应用程序的入口点。
//

#include "Convert.h"
#include "Feature.h"
#include <cv.h>
#include <highgui.h>

int main(int argc, char* argv[])
{
	IplImage *test =cvLoadImage(argv[1],-1);
	Frame* frame = new Frame(test->width, test->height, true, false, false );
	Mat imgMat(test);
	frame->setImage( imgMat);
	XM::ColorLayoutDescriptor* cl = Feature::getColorLayoutD(frame);
	cl->Print();
	delete cl;
	return 0;
}

