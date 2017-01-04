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
	string  m_srcImg;//Դͼ��·��
	string  m_dstImg;//Ŀ��ͼ��·��
	DirectorProcessor * m_dp;//����·����Ϣ
	ImageProcessor * frontImage;//��ǰ����ͼƬ
	double m_dScoreThresHold; //������ֵ
	double m_dPWDThresHold; //PWD��ֵ
	int m_nBottomQuality;//=60?
	int m_nInitQuality;
	int index;//Compressor��index
public:
	bool init(const string & srcImg, const string &dstImg);
	/*
		�������ܣ����������������е���ͼƬѹ����
		����˵����
		srcImg��		ԭͼƬ·����
		dstImg��		Ŀ��ͼƬ·����
		����ֵ��
		�ɹ�����true�����򷵻�false
	*/

	bool CompressSingleImage(const string & srcImg, const string &dstImg);
	bool CompressImage();
	bool  Compress();
	/*
	�������ܣ�����ԴͼƬ��Ŀ��ͼƬ�������Է�����
	����˵����
	srcImg��ԴͼƬ
	dstImg��Ŀ��ͼƬ
	����ֵ����������ͼƬ�Ƚ�֮�������ֵ��
	*/
};
