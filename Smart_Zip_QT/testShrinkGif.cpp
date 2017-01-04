#pragma once
#include "testShrinkGif.h"
#include "FreeImage.h"
using namespace std;
using namespace cv;
testShrinkGif::testShrinkGif()
{
	t = 50;
	y = 0.99;
}
testShrinkGif::~testShrinkGif()
{

}
IplImage*  testShrinkGif::gif2IplImage(const char* filename)
{
	FreeImage_Initialise();         //load the FreeImage function lib  
	FREE_IMAGE_FORMAT fif = FIF_GIF;
	FIBITMAP* fiBmp = FreeImage_Load(fif, filename, GIF_DEFAULT);
	FIMULTIBITMAP * pGIF = FreeImage_OpenMultiBitmap(fif, filename, 0, 1, 0, GIF_PLAYBACK);
	int gifImgCnt = FreeImage_GetPageCount(pGIF);
	FIBITMAP * pFrame;
	int width, height;
	width = FreeImage_GetWidth(fiBmp);
	height = FreeImage_GetHeight(fiBmp);
	IplImage * iplImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	iplImg->origin = 1;//should set to 1-top-left structure(Windows bitmap style)  
	RGBQUAD* ptrPalette = new RGBQUAD; // = FreeImage_GetPalette(fiBmp);  
	BYTE intens;
	BYTE* pIntensity = &intens;
	//printf("gifImgCnt %d \n", gifImgCnt);
	for (int curFrame = 0; curFrame<gifImgCnt; curFrame++)
	{
		pFrame = FreeImage_LockPage(pGIF, curFrame);
		//ptrPalette = FreeImage_GetPalette(pFrame);  
		char * ptrImgDataPerLine;
		for (int i = 0; i<height; i++)
		{
			ptrImgDataPerLine = iplImg->imageData + i*iplImg->widthStep;
			for (int j = 0; j<width; j++)
			{
				//get the pixel index   
				//FreeImage_GetPixelIndex(pFrame,j,i,pIntensity);    
				FreeImage_GetPixelColor(pFrame, j, i, ptrPalette);
				ptrImgDataPerLine[3 * j] = ptrPalette->rgbBlue;
				ptrImgDataPerLine[3 * j + 1] = ptrPalette->rgbGreen;
				ptrImgDataPerLine[3 * j + 2] = ptrPalette->rgbRed;
				//ptrImgDataPerLine[3*j] = ptrPalette[intens].rgbBlue;  
				//ptrImgDataPerLine[3*j+1] = ptrPalette[intens].rgbGreen;  
				//ptrImgDataPerLine[3*j+2] = ptrPalette[intens].rgbRed;  
			}
		}

		//printf("convert curFrame end %d \n", curFrame);
		FreeImage_UnlockPage(pGIF, pFrame, 1);
	}
	FreeImage_Unload(fiBmp);
	FreeImage_DeInitialise();
	return iplImg;
}


double testShrinkGif::getMSSIM(const Mat & i1, const Mat & i2)
{
	const double C1 = 6.5025, C2 = 58.5225;
	//------------------------------ INITS -------------------------------------//
	int d = CV_32F;

	Mat I1, I2;
	i1.convertTo(I1, d);           // cannot calculate on one byte large values
	i2.convertTo(I2, d);

	Mat I2_2 = I2.mul(I2);        // I2^2
	Mat I1_2 = I1.mul(I1);        // I1^2
	Mat I1_I2 = I1.mul(I2);        // I1 * I2

	//----------------------------- END INITS -------------------------------------//

	Mat mu1, mu2;   // PRELIMINARY COMPUTING
	GaussianBlur(I1, mu1, Size(11, 11), 1.5);
	GaussianBlur(I2, mu2, Size(11, 11), 1.5);

	Mat mu1_2 = mu1.mul(mu1);
	Mat mu2_2 = mu2.mul(mu2);
	Mat mu1_mu2 = mu1.mul(mu2);

	Mat sigma1_2, sigma2_2, sigma12;

	GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
	sigma1_2 -= mu1_2;

	GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
	sigma2_2 -= mu2_2;

	GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
	sigma12 -= mu1_mu2;

	//----------------------------- FORMULA ---------------------------------
	Mat t1, t2, t3;

	t1 = 2 * mu1_mu2 + C1;
	t2 = 2 * sigma12 + C2;
	t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

	t1 = mu1_2 + mu2_2 + C1;
	t2 = sigma1_2 + sigma2_2 + C2;
	t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

	Mat ssim_map;
	divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;

	cvtColor(ssim_map, ssim_map, CV_RGB2GRAY);

	Scalar mssim = mean(ssim_map); // mssim = average of ssim map
	return mssim[0];
}


int testShrinkGif::sign(double x) {//符号函数
	if (x < 0) return -1;
	else
	if (x > 0) return 1;
	else return 0;
}

void testShrinkGif::initialize(int t, double r){//预处理求导数
	double del1, del2;
	int h1, h2;
	h1 = t - 1;
	h2 = 256 - t;
	del1 = r / h1;
	del2 = (1 - r) / h2;
	double w1, w2;
	w1 = (2 * h1 + h2) / (3 * 255.0);
	w2 = (h1 + 2 * h2) / (3 * 255.0);
	d2 = del1*del2 / (w1*del1 + w2*del2);
	d3 = ((2 * h2 + h1)*del2 - h2*del1) / (h2 + h1);
	if (sign(d3) != sign(del2))		d3 = 0; else
	if ((sign(del2) != sign(del1)) && (abs(d3) > abs(3 * del2)))	d3 = 3 * del2;
}

double testShrinkGif::interpolation(int x){//插值
	double answer;
	answer = pow((x - 256.0) / (t - 256.0), 2)*(1 + 2.0 * (x - t) / (256.0 - t))*r\
		+ pow((x - t) / (256.0 - t), 2)*(1 + 2.0 * (x - 256) / (t - 256)) * 1\
		+ pow((x - 256.0) / (t - 256.0), 2)*(x - t)*d2\
		+ pow((x - t) / (256.0 - t), 2)*(x - 256.0)*d3;
	return answer;
}

int testShrinkGif::dichotomization(int s, int e, int temp){//二分法反解插值函数
	double i = interpolation(temp);
	double i1 = interpolation(temp + 1);
	double i2 = interpolation(temp - 1);
	if ((i - y)*(i1 - y) <= 0 || (i - y)*(i2 - y) <= 0)
	{
		return temp;
	}
	if (i>y){
		dichotomization(s, temp, (s + temp) / 2);
	}
	else{
		dichotomization(temp, e, (e + temp) / 2);
	}

}

int testShrinkGif::run(string srcName,int t,double y){


	int imageTpye = 1;
	string name = srcName.substr(0, srcName.length() - 4);//取子串去掉扩展名
	stringstream ss,st;
	if (imageTpye==1)
	{
		ss << name << "_" << t << "_opti.gif";
	}
	else
	{	
		ss << name << "_" << t << "_opti.png";
	}

	gifCompress(srcName,ss.str().c_str(),t);//50色压缩
	
	IplImage *src1, *src2;
	src1 = gif2IplImage(srcName.data());
	src2 = gif2IplImage(ss.str().c_str());

	cv::Mat src11(src1);
	cv::Mat src22(src2);
	r = getMSSIM(src11, src22);

	//cout << ss.str().c_str() << endl;
	initialize(t, r);
	t = dichotomization(1, 256, t);
	cout << t << endl;
	if (imageTpye == 1)
	{
		st << name << "_result.gif";
		gifCompress(srcName, st.str().c_str(), t);
	}
	
	cout << st.str().c_str() << endl;


	return 0;
}