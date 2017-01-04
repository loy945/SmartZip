#pragma once

#include<string>
#include "imageNames.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "FreeImage.h"
#include "testShrinkGif.h"
using namespace std;
using namespace cv;

/*标准的亮度量化表。*/
static const unsigned short std_luminance_quant_tbl[64] = {
	16, 11, 10, 16, 24, 40, 51, 61,
	12, 12, 14, 19, 26, 58, 60, 55,
	14, 13, 16, 24, 40, 57, 69, 56,
	14, 17, 22, 29, 51, 87, 80, 62,
	18, 22, 37, 56, 68, 109, 103, 77,
	24, 35, 55, 64, 81, 104, 113, 92,
	49, 64, 78, 87, 103, 121, 120, 101,
	72, 92, 95, 98, 112, 100, 103, 99
};

/*标准的色度量化表。*/
const unsigned short std_chrominance_quant_tbl[64] = {
	17, 18, 24, 47, 99, 99, 99, 99,
	18, 21, 26, 66, 99, 99, 99, 99,
	24, 26, 56, 99, 99, 99, 99, 99,
	47, 66, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99
};
class ImageProcessor
{
public:
	ImageProcessor();
	~ImageProcessor();
	public:
	string m_srcImg;//源图片
	Mat m_mSrcImage;
	FIBITMAP * m_srcImg_fibitmap;
	string m_dstImg;//目标图片
	Mat m_mDstImg;
	FIBITMAP * m_dstImg_fibitmap;
	int m_iQuality; //图片的质量因子
	vector<int> m_quality;
	int m_iWidth; // 原始图片宽
	int m_iHeight; //原始图片高
	imageType m_imageType;//原图类型
	//图像信息
	unsigned short *m_cur_luminance_tbl; //亮度量化表
	unsigned short *m_cur_chrominance_tbl; //色度量化表
	int m_icomponents;


public:
	void FI2MAT(FIBITMAP* src, Mat& dst);
	bool MAT2FI(Mat& src, FIBITMAP* * dst);
	bool readImages(const string & srcImg,  const string dstImg);
	/*
	函数功能：得到(source)图片的格式
	参数说明：
	strPath：图片的文件名（包括路径）
	返回值：如果不能打开文件返回0，
	如果图片格式为JPG则返回1，
	如果为其他格式则返回2
	*/
	imageType getImageFormat();
	/*
	函数功能：计算源图片和目的图片的相似性分数。
	参数说明：
	srcImg：源图片
	dstImg：目标图片
	返回值：返回两幅图片比较之后的相似值。
	*/
	float ComputeSimilarScore2(const Mat& srcImg, const Mat& dstImg);
	int getOptQuality(Mat& src, float scoreThreshold, int bottomQuality, int initQuality);
	Mat Gradient(const Mat &img);
	void Gradient(const Mat &gray, Mat &dst);
	bool InitImageQuality();	
	bool BMPCompress(double dScoreThresHold, double nBottomQuality, double nInitQuality);
	bool JPEGCompress(double dScoreThresHold, double nBottomQuality);
	bool PNGCompress(double dScoreThresHold, double nBottomQuality);
	bool GIFCompress(double dScoreThresHold, double nBottomQuality);
	bool writeImage(const string & dstImg);
	/*
	函数功能：得到图片的亮度和色度量化表
	参数说明：
	src:源图片的文件名。
	lumi_quant[] :保存得到的亮度量化表。
	chro_quant[] :保存得到的色度量化表。
	返回值：
	返回图片的颜色通道数。
	*/
	bool GetDecompressInfo();//获得src图像的压缩信息，存入m_cur_luminance_tbl和m_cur_luminance_tbl中
	/*
	函数功能：根据输入的亮度量化表和标准亮度量化表得到最接近的质量因子。
	参数说明：
	lumi_quant[] : 输入的亮度量化表。
	basic_table[] :标准的量化表。
	返回值：
	返回最接近的图片的质量因子。
	*/
	int getNearestQuality(unsigned short lumi_quant[], const unsigned short basic_table[]);
	/*
	函数功能：根据质量因子得到量化表。
	参数说明：
	quality:输入的质量因子。
	qua_table:保存得到的量化表。
	basic_table:输入的标准量化表。
	返回值：
	无。
	*/
	void get_q_table_by_quality(int quality, unsigned short qua_table[], const unsigned short basic_table[]);
	/*
	函数功能：得到两个量化表的方差。
	参数说明：
	lumi_quant[] ：输入的量化表。
	q_table[] :输入的量化表。
	n :数组的长度。
	isAbs :是否取绝对值。如果为TRUE则计算的时候取绝对值；如果为FALSE则不取绝对值。
	返回值：
	返回两个量化表的方差。
	*/
	double getVariance(unsigned short lumi_quant[], const unsigned short q_table[], int n, bool isAbs);/*
/*
	函数功能：根据质量因子计算出量化表，然后比较其与luminance_quant的方差。
	参数说明：
		q_closet:质量因子。
		luminance_quant[]:要比较的量化表。
	返回值：
		两个量化表的方差。
*/
	double getVar(int q_closet, unsigned short luminance_quant[]);
	/*
	函数功能：计算文件的大小。
	参数说明：
	src:源文件名。
	返回值：
	文件的大小（byte表示）。
	*/
	unsigned long get_file_size(string src);
	/*
	函数功能：按照量化表保存图片。
	参数说明：
	srcFile :源图片文件名。
	dstFile :目的图片文件名。
	q_closet:质量因子。
	返回值：
	无。
	*/
	bool saveJpegUseQuaTable(const std::string &srcFile, const std::string&dstFile, int quality);
	/*
	函数功能：复制文件
	参数说明：
	srcFile：源文件
	dstFile：目的文件
	返回值：
	如果文件复制成功返回true;
	如果文件赋值失败则返回false。
	*/
	bool copyFile(const std::string & srcFile, const std::string & dstFile);
};

