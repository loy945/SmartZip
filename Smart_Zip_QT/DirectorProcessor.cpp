#pragma once
#include "DirectorProcessor.h"
#include "io.h"
#include <fstream>
#include <iostream>
#include <QDir>
#include <QDebug>
using namespace std;
DirectorProcessor::DirectorProcessor()
{
	m_iTotalImages = 0;
}


DirectorProcessor::~DirectorProcessor()
{
}


imageType DirectorProcessor::getImageFormat(const string & srcPath)
{

	FILE *input_file = NULL;
	unsigned char signature;
	if ((input_file = fopen(srcPath.c_str(), "rb")) == NULL)//打开文件
		return NotAccept;
	fread(&signature, 1, 1, input_file);
	fclose(input_file);
	if (signature == 0xff)
		return JPEG;
	else if (signature == 0x42)
		return BMP;
	else if (signature == 0x89)
		return PNG;
	else if (signature == 0x47)
		return GIF;
	return NotAccept; 
}

int DirectorProcessor::processDirector(const string& srcPath, const string& dstPath, vector<imageNames> *qImages)
{
	struct _finddata_t filefind;
	m_srcPath = srcPath;
	m_dstPath = dstPath;
	
	QDir dir(QString::fromLocal8Bit(srcPath.c_str()));
	const char*  sss= srcPath.c_str();
	//dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QStringList filter;
	filter << "*.jpg" << "*.JPG" << "*.jpeg" << "*.JPEG" << "*.bmp" << "*.BMP"<< "*.png" << "*.PNG" << "*.gif" << "*.GIF" ;
	dir.setNameFilters(filter);
	dir.setSorting(QDir::Size | QDir::Reversed);
	qDebug() << "dir:"<<dir;
	QFileInfoList list = dir.entryInfoList();
	qDebug() << "     Bytes Filename";
	qDebug() << "QFileInfoList list size: " << list.size();
	for (int i = 0; i < list.size(); ++i) {
		QFileInfo fileInfo = list.at(i);
		qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
		qDebug() << "\n";
		imageNames imgN;

		QByteArray cpath = fileInfo.fileName().toLocal8Bit();
		char *str1 = cpath.data();
		imgN.src = srcPath + "\\" + string(str1);
		//imgN.dst = dstPath + "\\" + fileName + "_opti.jpg";
		QByteArray cpath2 = fileInfo.fileName().toLocal8Bit();
		char *str2 = cpath2.data();
		imgN.dst = dstPath + "\\" + string(str2);
		char drive[10], dir[500], fname[100], ext[10];
		_splitpath(imgN.dst.c_str(), drive, dir, fname, ext);
		string extString=string(ext);
		if (extString == ".bmp")
		{
			extString = ".jpg";
		}
		imgN.dst = string(drive) + string(dir) + string(fname) + extString;
		imgN.type = getImageFormat(imgN.src);
		if (getImageFormat(imgN.src) == NotAccept)
		{
			//跳过
		}
		else
		{
			qImages->push_back(imgN);
			m_iTotalImages++;
		}
		qDebug() << "img.src: " << QString::fromLocal8Bit(imgN.src.c_str()) << " \n";
		qDebug() << "dst.src: " << QString::fromLocal8Bit(imgN.dst.c_str()) << " \n";
	}
	/*string curPath = srcPath + "\\*.*";
	int handle;
	if ((handle = _findfirst(curPath.c_str(), &filefind)) == -1)//打开文件夹失败
	{
		return -1;
	}
	int curFile;

	do
	{
		string fileName = (string)filefind.name;
		int idx = fileName.rfind(".");
		string fileNewName;

		string srcfile;
		string dstfile;
		if (idx != string::npos)
		{
			string ext = fileName.substr(idx);//得到文件的后缀名
			if (ext == ".jpg" || ext == ".JPG" || ext == ".jpeg" || ext == ".JPEG" || ext == ".bmp" || ext == ".BMP")
			{
				imageNames imgN;
				imgN.src = srcPath + "\\" + fileName;
				//imgN.dst = dstPath + "\\" + fileName + "_opti.jpg";
				imgN.dst = dstPath + "\\" + fileName;
				imgN.type = getImageFormat(imgN.src);
				if (getImageFormat(imgN.src) == NotAccept)
				{
					//跳过
				}
				else
				{
					qImages->push_back(imgN);
					m_iTotalImages++;
				}				
			}
		}

	} while ((curFile = _findnext(handle, &filefind)) != -1);//对图片中的每一个文件进行遍历。
	_findclose(handle);*/
	return true;

}
