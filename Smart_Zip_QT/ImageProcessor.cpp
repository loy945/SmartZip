#pragma once

#include "ImageProcessor.h"
#include "ijgLibEx.h"
#include <sys\stat.h>
#include <fstream>

using namespace std;
bool ImageProcessor::MAT2FI(Mat&src, FIBITMAP**dst)
{
	/*  These are openCV types
	#define CV_8U   0
	#define CV_8S   1
	#define CV_16U  2
	#define CV_16S  3
	#define CV_32S  4
	#define CV_32F  5
	#define CV_64F  6
	*/

	/*  these are FI types
	FIT_UNKNOWN = 0,    // unknown type
	FIT_BITMAP  = 1,    // standard image           : 1-, 4-, 8-, 16-, 24-, 32-bit
	FIT_UINT16  = 2,    // array of unsigned short  : unsigned 16-bit
	FIT_INT16   = 3,    // array of short           : signed 16-bit
	FIT_UINT32  = 4,    // array of unsigned long   : unsigned 32-bit
	FIT_INT32   = 5,    // array of long            : signed 32-bit
	FIT_FLOAT   = 6,    // array of float           : 32-bit IEEE floating point
	FIT_DOUBLE  = 7,    // array of double          : 64-bit IEEE floating point
	FIT_COMPLEX = 8,    // array of FICOMPLEX       : 2 x 64-bit IEEE floating point
	FIT_RGB16   = 9,    // 48-bit RGB image         : 3 x 16-bit
	FIT_RGBA16  = 10,   // 64-bit RGBA image        : 4 x 16-bit
	FIT_RGBF    = 11,   // 96-bit RGB float image   : 3 x 32-bit IEEE floating point
	FIT_RGBAF   = 12    // 128-bit RGBA float image : 4 x 32-bit IEEE floating point

	*/

	if (*dst)  // get rid of the current dib. 
		FreeImage_Unload(*dst);

	int width = src.size().width;
	int height = src.size().height;

	switch (src.type())
	{
	case CV_8U:{*dst = FreeImage_AllocateT(FIT_BITMAP, width, height, 8); }break;  // 8  bit grayscale
	case CV_8UC3:{*dst = FreeImage_AllocateT(FIT_BITMAP, width, height, 24); }break;  // 24 bit RGB
	case CV_16U:{*dst = FreeImage_AllocateT(FIT_UINT16, width, height, 16); }break;  // 16 bit grayscale
	case CV_16S:{*dst = FreeImage_AllocateT(FIT_INT16, width, height, 16); }break;
	case CV_32S:{*dst = FreeImage_AllocateT(FIT_INT32, width, height, 32); }break;
	case CV_32F:{*dst = FreeImage_AllocateT(FIT_FLOAT, width, height, 32); }break;
	case CV_64F:{*dst = FreeImage_AllocateT(FIT_DOUBLE, width, height, 32); }break;
	}

	if (*dst == NULL)
		return FALSE;


	int srcRowBytes = width  * src.elemSize();

	for (int ih = 0; ih<height; ih++)
	{
		BYTE* ptr2Line = FreeImage_GetScanLine(*dst, ih);
		memcpy(ptr2Line, src.ptr(ih), srcRowBytes);
	}
	
	return TRUE;
}
void ImageProcessor::FI2MAT(FIBITMAP* src, Mat& dst)
{
	////FIT_BITMAP    //standard image : 1 - , 4 - , 8 - , 16 - , 24 - , 32 - bit
	////FIT_UINT16    //array of unsigned short : unsigned 16 - bit
	////FIT_INT16     //array of short : signed 16 - bit
	////FIT_UINT32    //array of unsigned long : unsigned 32 - bit
	////FIT_INT32     //array of long : signed 32 - bit
	////FIT_FLOAT     //array of float : 32 - bit IEEE floating point
	////FIT_DOUBLE    //array of double : 64 - bit IEEE floating point
	////FIT_COMPLEX   //array of FICOMPLEX : 2 x 64 - bit IEEE floating point
	////FIT_RGB16     //48 - bit RGB image : 3 x 16 - bit
	////FIT_RGBA16    //64 - bit RGBA image : 4 x 16 - bit
	////FIT_RGBF      //96 - bit RGB float image : 3 x 32 - bit IEEE floating point
	////FIT_RGBAF     //128 - bit RGBA float image : 4 x 32 - bit IEEE floating point

	//int bpp = FreeImage_GetBPP(src);
	//FREE_IMAGE_TYPE fit = FreeImage_GetImageType(src);

	//int cv_type = -1;
	//int cv_cvt = -1;

	//switch (fit)
	//{
	//case FIT_UINT16: cv_type = DataType<ushort>::type; break;
	//case FIT_INT16: cv_type = DataType<short>::type; break;
	//case FIT_UINT32: cv_type = DataType<unsigned>::type; break;
	//case FIT_INT32: cv_type = DataType<int>::type; break;
	//case FIT_FLOAT: cv_type = DataType<float>::type; break;
	//case FIT_DOUBLE: cv_type = DataType<double>::type; break;
	//case FIT_COMPLEX: cv_type = DataType<Complex<double>>::type; break;
	//case FIT_RGB16: cv_type = DataType<Vec<ushort, 3>>::type; cv_cvt = COLOR_RGB2BGR; break;
	//case FIT_RGBA16: cv_type = DataType<Vec<ushort, 4>>::type; cv_cvt = COLOR_RGBA2BGRA; break;
	//case FIT_RGBF: cv_type = DataType<Vec<float, 3>>::type; cv_cvt = COLOR_RGB2BGR; break;
	//case FIT_RGBAF: cv_type = DataType<Vec<float, 4>>::type; cv_cvt = COLOR_RGBA2BGRA; break;
	//case FIT_BITMAP:
	//	switch (bpp) {
	//	case 8: cv_type = DataType<Vec<uchar, 1>>::type; break;
	//	case 16: cv_type = DataType<Vec<uchar, 2>>::type; break;
	//	case 24: cv_type = DataType<Vec<uchar, 3>>::type; break;
	//	case 32: cv_type = DataType<Vec<uchar, 4>>::type; break;
	//	default:
	//		// 1, 4 // Unsupported natively
	//		cv_type = -1;
	//	}
	//	break;
	//default:
	//	// FIT_UNKNOWN // unknown type
	//	dst = Mat(); // return empty Mat
	//	return;
	//}

	//int width = FreeImage_GetWidth(src);
	//int height = FreeImage_GetHeight(src);
	//int step = FreeImage_GetPitch(src);

	//if (cv_type >= 0) {
	//	dst = Mat(height, width, cv_type, FreeImage_GetBits(src), step);
	//	if (cv_cvt > 0)
	//	{
	//		cvtColor(dst, dst, cv_cvt);
	//	}
	//}
	//else {

	//	vector<uchar> lut;
	//	int n = pow(2, bpp);
	//	for (int i = 0; i < n; ++i)
	//	{
	//		lut.push_back(static_cast<uchar>((255 / (n - 1))*i));
	//	}

	//	FIBITMAP* palletized = FreeImage_ConvertTo8Bits(src);
	//	BYTE* data = FreeImage_GetBits(src);
	//	for (int r = 0; r < height; ++r) {
	//		for (int c = 0; c < width; ++c) {
	//			dst.at<uchar>(r, c) = saturate_cast<uchar>(lut[data[r*step + c]]);
	//		}
	//	}
	//}
	int width = FreeImage_GetWidth(src);
	int height = FreeImage_GetHeight(src);

	BYTE intensity;
	BYTE* pIntensity = &intensity;
	if (FreeImage_GetBPP(src) != 8)
		src = FreeImage_ConvertTo8Bits(src); //必须转化为8bit
	RGBQUAD* pixels = new RGBQUAD;
	pixels = FreeImage_GetPalette(src);
	dst = Mat::zeros(height, width, CV_8UC3);

	uchar* p;
	for (int i = 0; i < height; i++)
	{
		p = dst.ptr<uchar>(i);
		for (int j = 0; j < width; j++)
		{
			FreeImage_GetPixelIndex(src, j, i, pIntensity);

			p[3 * j] = pixels[intensity].rgbBlue;
			p[3 * j + 1] = pixels[intensity].rgbGreen;
			p[3 * j + 2] = pixels[intensity].rgbRed;
		}
	}

}
ImageProcessor::ImageProcessor()
{
	
	m_iQuality = 10;
	m_iWidth = 0;
	m_iHeight = 0;
	m_quality.clear();
	for (int i = 0; i < 2;i++ )
	{
		m_quality.push_back(0);
	}
	m_cur_chrominance_tbl = nullptr;
	m_cur_luminance_tbl = nullptr;
	m_icomponents = 0;
	/*标准的亮度量化表*/
	

}


ImageProcessor::~ImageProcessor()
{
}
bool ImageProcessor::readImages(const string & srcImg,const string dstImg)
{
	
	m_srcImg = srcImg;
	m_dstImg = dstImg;
	string type;
	int size = srcImg.size();
	if (size > 4)
	{
		type.assign(m_srcImg, size - 4, 4);
		if (type == ".gif" || type == ".GIF")
		{
			//读取GIF
			 m_srcImg_fibitmap = FreeImage_Load(FIF_GIF, m_srcImg.c_str());
			 FI2MAT(m_srcImg_fibitmap, m_mSrcImage);
		}else if (type == ".png" || type == ".PNG")
		{
			//读取PNG
			m_srcImg_fibitmap = FreeImage_Load(FIF_PNG, m_srcImg.c_str());
			FI2MAT(m_srcImg_fibitmap, m_mSrcImage);
		}
		else
		{
			m_mSrcImage = cv::imread(m_srcImg, 1);
		}
	}
	else
	{
		return false;
	}

	if (m_mSrcImage.empty()){
		printf("The image doesn't exists yo!\n");
		return false;
	}
	if (m_mSrcImage.rows < 8 || m_mSrcImage.cols < 8){
		printf("The image needn't be compressed\n");
		return false;
	}
	if (type == ".gif" || type == ".GIF")
	{

	}
	else
	{	
		cv::Mat m_mGraySrcImage;
		cv::cvtColor(m_mSrcImage, m_mGraySrcImage, CV_RGB2GRAY);
	}
	
	m_iWidth = m_mSrcImage.cols;
	m_iHeight = m_mSrcImage.rows;
	int nBottomQuality = 60;
	m_quality[0] = CV_IMWRITE_JPEG_QUALITY;
	m_quality[1] = nBottomQuality;


	return true;
}
imageType ImageProcessor::getImageFormat()
{

	FILE *input_file = NULL;
	unsigned char signature;
	if ((input_file = fopen(m_srcImg.c_str(), "rb")) == NULL)//打开文件
	{
		return NotAccept;
	}
	string type;
	int size = m_srcImg.size();
	if (size <= 4)
	{
		return NotAccept;
	}
	else
	{
		type.assign(m_srcImg, size - 4, 4);
	}
	
	fread(&signature, 1, 1, input_file);
	fclose(input_file);
	if (signature == 0xff && (type == ".jpeg" || type == ".JPEG"||type == ".jpg" || type == ".JPG"))
		return JPEG;
	else if (signature == 0x42 && (type == ".bmp" || type == ".BMP"))
		return BMP;
	else if (signature == 0x89 && (type == ".png" || type == ".PNG"))
		return PNG;
	else if (signature == 0x47 && (type == ".gif" || type == ".GIF"))
		return GIF;
	return NotAccept;
}

int ImageProcessor::getOptQuality(Mat& src, float scoreThreshold, int bottomQuality, int initQuality)
{
	if (initQuality == 100)
		return 75;
	vector<uchar> tmpVec;
	vector<int> quality(2);
	quality[0] = CV_IMWRITE_JPEG_QUALITY;
	quality[1] = bottomQuality;


	cv::Mat tmpImage;

	bool r1 = cv::imencode (".jpg", src, tmpVec, quality);
	cv::imdecode(tmpVec, CV_LOAD_IMAGE_COLOR, &tmpImage);

	float score2 = ComputeSimilarScore2(src, tmpImage);
	tmpImage.release();

	tmpVec.clear();
	vector<uchar>(tmpVec).swap(tmpVec);
	quality.clear();
	vector<int>(quality).swap(quality);

	float log1 = std::log(100.0f / initQuality - 1.0f + 0.0000001);
	float log2 = std::log(100.0f / bottomQuality - 1.0f + 0.0000001);
	float a = -(log1 - log2) / (1 - score2);
	float b = (log1 + a) / a;

	int optQ = static_cast<int>(100.0f / (1 + std::exp(-a * (scoreThreshold - b))));
	if (optQ >= bottomQuality && optQ <= initQuality)
	{
		return optQ;
	}
	else{
		int returnValue = (bottomQuality + initQuality) / 2;
		return returnValue;
	}
}

float ImageProcessor::ComputeSimilarScore2(const Mat& srcImg, const Mat& dstImg)
{
	int bound = floor(11.0 / 2);
	Mat psnrSim = Mat::zeros(Size(srcImg.cols, srcImg.rows), CV_32F);
	Mat tdSim = Mat::zeros(Size(srcImg.cols, srcImg.rows), CV_32F);
	Mat graSim = Mat::zeros(Size(srcImg.cols, srcImg.rows), CV_32F);


	//convert to YIQ
	Mat Y1(Size(srcImg.cols, srcImg.rows), CV_32F), Y2(Size(srcImg.cols, srcImg.rows), CV_32F);
	if (srcImg.channels() == 3)
	{
		Mat srcChan[3], dstChan[3];
		split(srcImg, srcChan);
		split(dstImg, dstChan);
		Y1 = 0.299 * srcChan[2] + 0.587 * srcChan[1] + 0.114 * srcChan[0];
		Y2 = 0.299 * dstChan[2] + 0.587 * dstChan[1] + 0.114 * dstChan[0];
		for (int i = 0; i < 3; i++)
		{
			srcChan[i].release(); dstChan[i].release();
		}
	}
	else
	{
		Y1 = srcImg;
		Y2 = dstImg;
	}

	Y1.convertTo(Y1, CV_32F); Y2.convertTo(Y2, CV_32F);

	//compute PSNR similarity
	int THRpsnr = 53;
	Mat diff_sqr;
	cv::GaussianBlur((Y1 - Y2).mul(Y1 - Y2), diff_sqr, Size(11, 11), 1.5);
	log(255 * 255 / (diff_sqr + 0.0001), diff_sqr);
	psnrSim = (cv::min)((10 / log(10.0))* diff_sqr / THRpsnr, 1);
	diff_sqr.release();


	// compute texture distortion
	float T = 0.0000001;
	Mat mu1, mu2;
	GaussianBlur(Y1, mu1, Size(11, 11), 1.5);
	GaussianBlur(Y2, mu2, Size(11, 11), 1.5);
	Mat sigma1_sqr, sigma2_sqr;
	GaussianBlur(Y1.mul(Y1), sigma1_sqr, Size(11, 11), 1.5);
	GaussianBlur(Y2.mul(Y2), sigma2_sqr, Size(11, 11), 1.5);
	sigma1_sqr = abs(sigma1_sqr - mu1.mul(mu1));
	sigma2_sqr = abs(sigma2_sqr - mu2.mul(mu2));
	Mat sigma1, sigma2;
	pow(sigma1_sqr, 0.5, sigma1);
	pow(sigma2_sqr, 0.5, sigma2);
	tdSim = (2 * sigma1.mul(sigma2) + T) / (sigma1_sqr + sigma2_sqr + T);
	mu1.release();
	mu2.release();
	sigma1.release();
	sigma2.release();
	sigma1_sqr.release();
	sigma2_sqr.release();

	// gradient similarity
	T = 160;
	Mat graSrc(Y1.size(), CV_32F);
	Mat graDst(Y1.size(), CV_32F);
	Gradient(Y1, graSrc);
	Gradient(Y2, graDst);
	graSim = (2 * graSrc.mul(graDst) + T) / (graSrc.mul(graSrc) + graDst.mul(graDst) + T);
	graSrc.release();
	graDst.release();

	Y1.release();
	Y2.release();

	// pooling
	float score = 0;
	for (int r = bound; r < srcImg.rows - bound; r++)
	{
		const float* grat = graSim.ptr<float>(r);
		const float* psnrt = psnrSim.ptr<float>(r);
		const float* tdt = tdSim.ptr<float>(r);

		for (int c = bound; c < srcImg.cols - bound; c++)
		{
			score += grat[c] * psnrt[c] * tdt[c];
		}
	}
	graSim.release();
	psnrSim.release();
	tdSim.release();
	score = score / ((srcImg.rows - 11)*(srcImg.cols - 11));

	return score;
}
void ImageProcessor::Gradient(const Mat &gray, Mat &dst)
{
	//Mat gray;
	//cvtColor(img, gray, CV_RGB2GRAY);
	Mat dst_x, dst_y;
	//Mat dst(gray.size(), CV_32F);
	Sobel(gray, dst_x, dst.depth(), 1, 0);
	Sobel(gray, dst_y, dst.depth(), 0, 1);
	//dst = dst_x.mul(dst_x) + dst_y.mul(dst_y);
	dst = abs(dst_x) + abs(dst_y);
	dst_x.release();
	dst_y.release();
	//sqrt(dst, dst);
	//return dst;
}
bool ImageProcessor::BMPCompress(double dScoreThresHold, double nBottomQuality, double nInitQuality)
{
	vector<uchar> tmp;
	cv::Mat tmpImage;
	m_quality[1] = 90;
	cv::imencode(".jpg", m_mSrcImage, tmp, m_quality);
	cv::imdecode(tmp, CV_LOAD_IMAGE_COLOR, &tmpImage);

	m_quality[1] = getOptQuality(tmpImage, dScoreThresHold, nBottomQuality, nInitQuality);
	m_iQuality = m_quality[1];
	tmpImage.release();
	tmp.clear();
	fstream logFile("Compress.log", ios::app);
	logFile << "------BMP----------" << endl;
	logFile << "dScoreThresHold " << dScoreThresHold<<endl;
	logFile << "nBottomQuality " <<  nBottomQuality << endl;
	logFile << "nInitQuality " << nInitQuality << endl;
	logFile << "m_quality " << m_quality[1] << endl;
	logFile.close();
	return true;
}
/*
函数功能：压缩JPEG格式图片
参数说明：

返回值：

*/
bool ImageProcessor::JPEGCompress(double dScoreThresHold, double nBottomQuality)
{

	double var = 100;
	bool returnValue = false;
	fstream logFile1("srcImgType.log", ios::app);
	logFile1 << "GetDecompressInfo start" << endl;
	logFile1.close();
	if (!GetDecompressInfo())
	{
		return false;
	}
	fstream logFile2("srcImgType.log", ios::app);
	logFile2 << "GetDecompressInfo done" << endl;
	logFile2.close();
	int nInitQuality = getNearestQuality(m_cur_luminance_tbl, std_luminance_quant_tbl);//
	var = getVar(nInitQuality, m_cur_luminance_tbl);
	fstream logFile("Compress.log", ios::app);
	logFile << "------JPEG----------" << endl;
	logFile << "dScoreThresHold " << dScoreThresHold << endl;
	logFile << "nBottomQuality " << nBottomQuality << endl;
	logFile << "nInitQuality " << nInitQuality << endl;
	logFile << "var " << var << endl;
	
	if (m_cur_chrominance_tbl[0] == 0 && m_icomponents > 1)
	{
		returnValue= false;
	}
	else
	{
		if (var >= 10 && nInitQuality >= 80)
		{
			m_quality[1] = 75;
			logFile << "var >= 10 && nInitQuality >= 80" << endl;
			logFile << "m_quality" << m_quality[1] << endl;
			returnValue = true;
		}
		if (var >= 10 && nInitQuality < 80)
		{
			logFile << "var >= 10 && nInitQuality >= 80" << endl;
			saveJpegUseQuaTable(m_srcImg, m_dstImg, nInitQuality);
			returnValue = false;
		}
		if (var < 10 && nInitQuality > nBottomQuality)
		{
			m_quality[1] = getOptQuality(m_mSrcImage, dScoreThresHold, nBottomQuality, nInitQuality);
			logFile << "m_quality" << m_quality[1] << endl;
			returnValue = true;
		}
		if (var < 10 && nInitQuality <= nBottomQuality)
		{
			copyFile(m_srcImg, m_dstImg);
			returnValue = false;
		}
	}
	logFile.close();
	return returnValue;
}
bool ImageProcessor::PNGCompress(double dScoreThresHold, double nBottomQuality)
{
	bool returnValue = false;

	if (!m_srcImg_fibitmap)
	{
		return false;
	}
	else
	{
		testShrinkGif tsg;
		m_dstImg_fibitmap = m_srcImg_fibitmap;

		tsg.t = 50;
		cv::Mat src11;
		cv::Mat src22;
		if (!m_srcImg_fibitmap)
		{
			return false;
		}
		else
		{
			int t = 50;
			FI2MAT(m_srcImg_fibitmap, src11);
			m_dstImg_fibitmap = FreeImage_ColorQuantizeEx(m_srcImg_fibitmap, FIQ_WUQUANT, t);
			FI2MAT(m_dstImg_fibitmap, src22);
			double ssim = 0;
			ssim = tsg.getMSSIM(src11, src22);
			tsg.initialize(t, ssim);
			int colorNums = 255;
			colorNums = tsg.dichotomization(1, 256, t);
			m_dstImg_fibitmap = FreeImage_ColorQuantizeEx(m_srcImg_fibitmap, FIQ_WUQUANT, colorNums);
			returnValue = true;
		}
	}
	return returnValue;
}
bool ImageProcessor::GIFCompress(double dScoreThresHold, double nBottomQuality)
{
	bool returnValue = false;

	if (!m_srcImg_fibitmap)
	{
		return false;
	}
	else
	{
		testShrinkGif tsg;
		m_dstImg_fibitmap = m_srcImg_fibitmap;
		
		tsg.t = 50;

		IplImage *src1 = tsg.gif2IplImage(m_srcImg.data());
		cv::Mat src11(src1);
		m_mSrcImage = src11;
		cv::Mat src22;
		MAT2FI(m_mSrcImage, &m_srcImg_fibitmap);
		if (!m_srcImg_fibitmap)
		{
			return false;
		}
		else
		{
			int t = 50;
			m_dstImg_fibitmap = FreeImage_ColorQuantizeEx(m_srcImg_fibitmap, FIQ_WUQUANT, t);
			FI2MAT(m_dstImg_fibitmap, src22);
			double ssim = 0;
			ssim = tsg.getMSSIM(m_mSrcImage, src22);
			tsg.initialize(t, ssim);
			int colorNums = 255;
			colorNums = tsg.dichotomization(1, 256, t);
			m_dstImg_fibitmap = FreeImage_ColorQuantizeEx(m_srcImg_fibitmap, FIQ_WUQUANT, colorNums);
			returnValue = true;
		}
		//gifCompress(srcName, ss.str().c_str(), tsg.t);//50色压缩

		//IplImage *src1, *src2;
		//src1 = tsg.gif2IplImage(srcName.data());
		//src2 = tsg.gif2IplImage(ss.str().c_str());

		//cv::Mat src11(src1);
		//cv::Mat src22(src2);
		//tsg.r = tsg.getMSSIM(src11, src22);

		////cout << ss.str().c_str() << endl;
		//tsg.initialize(tsg.t, tsg.r);
		//tsg.t = tsg.dichotomization(1, 256, tsg.t);
		//st << name << "_result.gif";
		//gifCompress(srcName, st.str().c_str(), tsg.t);;
		//returnValue = true;
	}
	return returnValue;
}
bool ImageProcessor::writeImage(const string & dstImg)
{
	m_dstImg = dstImg;
	fstream logFile("writeImage.log", ios::app);
	logFile << "------writeImage---------" << endl;
	logFile << "m_quality " << m_quality[1] << endl;
	logFile.close();
	
	imageType type = getImageFormat();
	switch (type)
	{
	case JPEG:
		cv::imwrite(m_dstImg, m_mSrcImage, m_quality);
		break;
	case BMP:
		cv::imwrite(m_dstImg, m_mSrcImage, m_quality);
		break;
	case PNG:
		FreeImage_Save(FIF_PNG, m_dstImg_fibitmap, m_dstImg.c_str());
		break;
	case GIF:
		FreeImage_Save(FIF_GIF, m_dstImg_fibitmap, m_dstImg.c_str());
		break;
	case NotAccept:
		break;
	default:
		break;
	}
	return true;
}

bool ImageProcessor::GetDecompressInfo()
{
	if (m_cur_chrominance_tbl)
	{
		delete m_cur_chrominance_tbl;
		m_cur_chrominance_tbl = nullptr;
	}
	m_cur_chrominance_tbl = new unsigned short[64]();
	if (m_cur_luminance_tbl)
	{
		delete m_cur_luminance_tbl;
		m_cur_luminance_tbl = nullptr;
	}
	m_cur_luminance_tbl = new unsigned short[64]();

	struct jpeg_decompress_struct srcinfo;
	const char *srcfilename = m_srcImg.c_str();
	//struct jpeg_error_mgr jsrcerr;
	FILE *inputfile = NULL;
	safe_jpeg_error_mgr em;
	try{
		srcinfo.err = jpeg_std_error(&em.pub);
		jpeg_create_decompress(&srcinfo);

		em.pub.error_exit = safe_jpeg_error_exit;

		if (setjmp(em.setjmp_buffer)){
			jpeg_destroy_decompress(&srcinfo);
			if (inputfile != NULL){
				fclose(inputfile);
			}
			return false;
		}
		if ((inputfile = fopen(srcfilename, "rb")) == NULL){
			fprintf(stderr, "can't open %s\n", srcfilename);
			jpeg_destroy_decompress(&srcinfo);
			if (inputfile != NULL){
				fclose(inputfile);
			}
		}
		jpeg_stdio_src(&srcinfo, inputfile);
		//jcopy_markers_setup(&srcinfo,JCOPYOPT_ALL);
		//JPP(&srcinfo,JCOPYOPT_ALL);

		(void)jpeg_read_header(&srcinfo, TRUE);

		for (int i = 0; i < 64; i++)//将得到的量化表保存到lumi_quant[]和chro_quant[]数组中。
		{
			if (srcinfo.quant_tbl_ptrs[0] != 0)
				m_cur_luminance_tbl[i] = srcinfo.quant_tbl_ptrs[0]->quantval[i];
			if (srcinfo.quant_tbl_ptrs[1] != 0)
				m_cur_chrominance_tbl[i] = srcinfo.quant_tbl_ptrs[1]->quantval[i];
		}
		m_icomponents = srcinfo.num_components;

		fclose(inputfile);
		jpeg_destroy_decompress(&srcinfo);
		return true;
	}
	catch (...){
		jpeg_destroy_decompress(&srcinfo);//释放资源
		if (inputfile != NULL)
			fclose(inputfile);

		jpeg_destroy_decompress(&srcinfo);


		return false;
	}

}
double ImageProcessor::getVariance(unsigned short lumi_quant[], const unsigned short q_table[], int n, bool isAbs){
	double sum = 0;
	if(isAbs){
		for(int i = 0 ;i < n; i ++){
			sum += abs((int)lumi_quant[i] - (int)q_table[i]);//采用绝对值,getVar计算方差时用到
		}
		return sum;
	}
	else{
		for(int i = 0; i < n ;i ++){
			sum += (lumi_quant[i] - q_table[i])*1.0/q_table[i];//getNearestQuality用到
		}
		return sum;
	}
}
//根据q生成的量化表T成线性递增关系,从100-->0增大，而T与标准量化表之间的距离从小到大增加
//当q=50时，生成的量化表qtable和标准量化表之间的距离dist为0
//则当dist>eps时，查找范围为1-49；否则查找范围为50-100
int ImageProcessor::getNearestQuality(unsigned short lumi_quant[], const unsigned short basic_table[])
{
	int q;
	unsigned short quaTable[64];
	double dist;
	double eps = 0.001;
	dist = getVariance(lumi_quant, basic_table, 64, false); //计算量化表的方差。
	int q_min;
	int q_max;
	if (dist > eps)
	{
		q_min = 1;
		q_max = 49;
		while (q_min <= q_max)//使用二分查找
		{
			q = (q_min + q_max) / 2;
			get_q_table_by_quality(q, quaTable, basic_table);//根据质量因子得到量化表
			dist = getVariance(lumi_quant, quaTable, 64, false);//计算得到的量化表和原标准量化表的方差。
			if (abs(dist) <= eps)
				break;
			if (dist < 0)
				q_min = q + 1;
			else
				q_max = q - 1;
		}
	}
	else
	{
		q_min = 50;
		q_max = 100;
		while (q_min <= q_max)
		{
			q = (q_min + q_max) / 2;
			get_q_table_by_quality(q, quaTable, basic_table);//根据质量因子得到量化表
			dist = getVariance(lumi_quant, quaTable, 64, false);//计算量化表的方差
			if (abs(dist) <= eps)
				break;
			if (dist < 0)
				q_min = q + 1;
			else
				q_max = q - 1;
		}
	}
	return q;
}
void ImageProcessor::get_q_table_by_quality(int quality, unsigned short qua_table[], const unsigned short basic_table[])
{
	int temp;
	int scale_factor = 0;
	if (quality < 0)
		quality = 1;
	if (quality > 100)
		quality = 100;
	if (quality < 50)
		scale_factor = 5000 / quality;
	else
		scale_factor = 200 - quality * 2;

	for (int i = 0; i<64; i++)
	{
		temp = (basic_table[i] * scale_factor + 50) / 100;
		if (temp <= 0) temp = 1;
		if (temp > 32767) temp = 32767; /* max quantizer needed for 12 bits */
		if (temp>255)
			temp = 255;
		qua_table[i] = temp;
	}
}
double ImageProcessor::getVar(int q_closet, unsigned short luminance_quant[])
{
	unsigned short quaTable[64];
	double dist = 100;
	get_q_table_by_quality(q_closet, quaTable, std_luminance_quant_tbl);
	dist = getVariance(luminance_quant, quaTable, 64, true);
	return dist;
}

unsigned long ImageProcessor::get_file_size(string src){
	struct _stat info;
	if (_stat(src.c_str(), &info) < 0){
		return 0;
	}
	return (unsigned long)info.st_size;
}

bool ImageProcessor::saveJpegUseQuaTable(const std::string &srcFile, const std::string&dstFile, int quality){
	struct jpeg_decompress_struct srcInfo;
	struct jpeg_error_mgr  injerr;

	FILE * infile = NULL;		//source file 
	JSAMPARRAY  buffer = NULL;		// Output row buffer 
	int row_stride;		// physical row width in output buffer 

	srcInfo.err = jpeg_std_error(&injerr);

	if ((infile = fopen(srcFile.c_str(), "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", srcFile);
		fclose(infile);
		return false;
	}

	struct jpeg_compress_struct dstInfo;
	struct jpeg_error_mgr outjerr;
	FILE * outfile;		// target file 

	dstInfo.err = jpeg_std_error(&outjerr);

	if ((outfile = fopen(dstFile.c_str(), "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", dstFile);
		fclose(infile);
		fclose(outfile);
		return false;
	}

	jpeg_create_decompress(&srcInfo);
	jpeg_stdio_src(&srcInfo, infile);

	(void)jpeg_read_header(&srcInfo, TRUE);
	(void)jpeg_start_decompress(&srcInfo);

	row_stride = srcInfo.output_width * srcInfo.output_components;

	jpeg_create_compress(&dstInfo);
	jpeg_stdio_dest(&dstInfo, outfile);

	dstInfo.image_width = srcInfo.image_width; 	// image width and height, in pixels 
	dstInfo.image_height = srcInfo.image_height;
	dstInfo.input_components = srcInfo.output_components;		// # of color components per pixel 
	dstInfo.in_color_space = srcInfo.out_color_space; 	// colorspace of input image 

	//按照默认初始化参数
	jpeg_set_defaults(&dstInfo);
	//默认设置可能设置错误的颜色空间，从新修改为原来image的color_space
	dstInfo.in_color_space = srcInfo.out_color_space;
	dstInfo.jpeg_color_space = srcInfo.jpeg_color_space;

	if (srcInfo.quant_tbl_ptrs[0]->quantval[0] != 0){
		for (int i = 0; i < 64; i++)
		{
			dstInfo.quant_tbl_ptrs[0]->quantval[i] = srcInfo.quant_tbl_ptrs[0]->quantval[i];
		}
	}
	if (srcInfo.quant_tbl_ptrs[1]->quantval[0] != 0){
		for (int i = 0; i < 64; i++){
			dstInfo.quant_tbl_ptrs[0]->quantval[i] = srcInfo.quant_tbl_ptrs[1]->quantval[i];
		}
	}
	//更改亮度和色度量化表，取最大值
	unsigned short *lumitab = new unsigned short[64]();
	unsigned short *chromtab = new unsigned short[64]();
	get_q_table_by_quality(quality, lumitab, std_luminance_quant_tbl);
	get_q_table_by_quality(quality, chromtab, std_chrominance_quant_tbl);

	for (int i = 0; i < 64; i++)
	{
		if (lumitab[i] > dstInfo.quant_tbl_ptrs[0]->quantval[i])
			dstInfo.quant_tbl_ptrs[0]->quantval[i] = lumitab[i];
		if (chromtab[i] > dstInfo.quant_tbl_ptrs[1]->quantval[i])
			dstInfo.quant_tbl_ptrs[1]->quantval[i] = chromtab[i];
	}

	jpeg_start_compress(&dstInfo, TRUE);

	row_stride = srcInfo.image_width * srcInfo.num_components;	// JSAMPLEs per row in image_buffer 

	//jcopy_markers_execute(&srcInfo, &dstInfo, JCOPYOPT_ALL);

	buffer = (*srcInfo.mem->alloc_sarray)
		((j_common_ptr)&srcInfo, JPOOL_IMAGE, row_stride, 1);

	while (srcInfo.output_scanline < srcInfo.output_height)
	{
		(void)jpeg_read_scanlines(&srcInfo, buffer, 1);
		(void)jpeg_write_scanlines(&dstInfo, buffer, 1);

	}

	jpeg_finish_decompress(&srcInfo);
	jpeg_destroy_decompress(&srcInfo);

	fclose(infile);

	jpeg_finish_compress(&dstInfo);
	jpeg_destroy_compress(&dstInfo);
	fclose(outfile);

	double srcSize = get_file_size(srcFile);
	double dstSize = get_file_size(dstFile);
	if (dstSize > srcSize){
		copyFile(srcFile, dstFile);
	}
	delete[] lumitab;
	delete[] chromtab;

	//free(buffer);

	return true;
}
bool ImageProcessor::copyFile(const std::string & srcFile, const std::string & dstFile){
	ifstream in;
	ofstream out;
	in.open(srcFile.c_str(), ios::binary);//打开源文件
	if (in.fail())//打开源文件失败
	{
		cout << "Error 1: Fail to open the source file." << endl;
		in.close();
		out.close();
		return false;
	}
	out.open(dstFile.c_str(), ios::binary);//创建目标文件
	if (out.fail())//创建文件失败
	{
		cout << "Error 2: Fail to create the new file." << endl;
		out.close();
		in.close();
		return false;
	}
	else//复制文件
	{
		out << in.rdbuf();
		out.close();
		in.close();
		return true;
	}
}
