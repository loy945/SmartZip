#pragma once
#include <string>
#include "imageNames.h"
#include "DirectorProcessor.h"
#include "ImageProcessor.h"

using namespace std;
class Compressor
{
public:
	Compressor();
	bool Compress(int compressorNum, const string & srcImg, const string &dstImg, int score);
	~Compressor();
private:
	string  m_srcImg;//源图像路径
	string  m_dstImg;//目标图像路径
	DirectorProcessor * m_dp;//输入路径信息
	ImageProcessor * frontImage;//当前处理图片
	double m_dScoreThresHold; //分数阈值
	double m_dPWDThresHold; //PWD阈值
	int m_nBottomQuality;//=60?
	int m_nInitQuality;
	int index;//Compressor的index
public:
	bool init(const string & srcImg, const string &dstImg);
	/*
		函数功能：根据输入的命令进行单个图片压缩。
		参数说明：
		srcImg：		原图片路径。
		dstImg：		目的图片路径。
		返回值：
		成功返回true，否则返回false
	*/

	bool CompressSingleImage(const string & srcImg, const string &dstImg);
	bool CompressImage();
	bool  Compress();
	/*
	函数功能：计算源图片和目的图片的相似性分数。
	参数说明：
	srcImg：源图片
	dstImg：目标图片
	返回值：返回两幅图片比较之后的相似值。
	*/
};
