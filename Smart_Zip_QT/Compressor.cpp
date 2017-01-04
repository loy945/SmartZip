#pragma once
#include "Compressor.h"
#include <iostream>
using namespace std;

Compressor::Compressor()
{
	m_dScoreThresHold = 0.85f;
	m_dPWDThresHold = 53.0f;
	m_nBottomQuality = 60;
	m_nInitQuality = 90;
}

bool Compressor::Compress(int compressorNums, const string & srcImg, const string &dstImg, int score)
{
	m_dScoreThresHold = (double)score/100.0;
	m_dPWDThresHold = 53.0f;
	m_nBottomQuality = 60;
	m_nInitQuality = 90;
	bool res = false;
	Compressor();
	index = compressorNums;
	init(srcImg, dstImg);
	res=CompressImage();
	return res;

}
Compressor::~Compressor()
{
}
bool Compressor::init(const string & srcImg, const string &dstImg)
{
	m_dp = nullptr;
	try
	{
		m_dp = new DirectorProcessor();

		if (!m_dp)
		{
			throw 1;
		}
	}
	catch (int i)
	{

	}
	m_srcImg = srcImg;
 	m_dstImg = dstImg;
	return true;
}


bool Compressor::CompressImage()
{
	frontImage = new ImageProcessor();
	if (frontImage)
	{
		 return CompressSingleImage(m_srcImg, m_dstImg);
		 
	}
	return false;
}
bool Compressor::CompressSingleImage(const string & srcImg, const string &dstImg)
{
	//read-compress-write
	//设置文件路径
	this->m_srcImg = srcImg;
	this->m_dstImg = dstImg;
	if (frontImage == NULL)
	{
		return false;
	}
	if (!frontImage->readImages(srcImg,dstImg))
	{
		return false;
	}

	if (Compress())
	{
		imageType type = frontImage->getImageFormat();
		
		return frontImage->writeImage(m_dstImg);
	}
	else
	{
		return false;
	}

}

bool Compressor::Compress()
{
	int src = 1;
	imageType srcImgType;
	srcImgType = frontImage->getImageFormat();
	bool res = false;
	
	switch (srcImgType)
	{
	case BMP:
	{
				res = frontImage->BMPCompress(m_dScoreThresHold, m_nBottomQuality, m_nInitQuality);

	}
		break;
	case JPEG:
	{
				 res = frontImage->JPEGCompress(m_dScoreThresHold, m_nBottomQuality);
	}
				 break;
	case PNG:
	{
				 res = frontImage->PNGCompress(m_dScoreThresHold, m_nBottomQuality);
	}
		break;
	case GIF:
	{
				 res = frontImage->GIFCompress(m_dScoreThresHold, m_nBottomQuality);
	}
		break;
	case NotAccept:
	{
				 res = false;
	}
		break;
	default:

		break;
	}
	return res;
}
