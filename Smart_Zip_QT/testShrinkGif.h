#pragma once
#include "gifCompress.h"
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include <sstream>
#include <stdio.h>




using namespace cv;
class testShrinkGif
{
public:

	double y, r, d2, d3;
	int t;//½Úµã
	testShrinkGif();
	~testShrinkGif();
	double getMSSIM(const Mat & i1, const Mat & i2);
	IplImage*  gif2IplImage(const char* filename);
	
	int sign(double x);
	void initialize(int t, double r);
	double interpolation(int x);
	int dichotomization(int s, int e, int temp);
	int run(string srcName, int t, double y);
};