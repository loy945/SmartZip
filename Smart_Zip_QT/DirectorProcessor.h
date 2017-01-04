#pragma once
#include <string>
#include "imageNames.h"
#include <vector>
using namespace std;

//处理路径相关功能
class DirectorProcessor
{
public:
	DirectorProcessor();
	~DirectorProcessor();
public:
	/*将用于存放待处理的图片信息，比如源图片地址、目的图片地址、图片类型放入队列*/
	int processDirector(const string  &src, const  string & dst, vector<imageNames> *qImages);
	/*
	函数功能：得到图片的格式
	参数说明：
	strPath：图片的文件名（包括路径）
	返回值：如果不能打开文件返回0，
	如果图片格式为JPG则返回1，
	如果为其他格式则返回2
	*/
	imageType getImageFormat(const string & srcPath);
	/*
	函数功能：复制文件
	参数说明：
	srcFile：源文件
	dstFile：目的文件
	返回值：
	如果文件复制成功返回true;
	如果文件赋值失败则返回false。
	*/

public:

	//全部图片的数量
	int m_iTotalImages;
	string m_srcPath;//源图片
	string m_dstPath;//目标图片
};

