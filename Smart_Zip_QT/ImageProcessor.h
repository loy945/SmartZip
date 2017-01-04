#pragma once

#include<string>
#include "imageNames.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "FreeImage.h"
#include "testShrinkGif.h"
using namespace std;
using namespace cv;

/*��׼������������*/
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

/*��׼��ɫ��������*/
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
	string m_srcImg;//ԴͼƬ
	Mat m_mSrcImage;
	FIBITMAP * m_srcImg_fibitmap;
	string m_dstImg;//Ŀ��ͼƬ
	Mat m_mDstImg;
	FIBITMAP * m_dstImg_fibitmap;
	int m_iQuality; //ͼƬ����������
	vector<int> m_quality;
	int m_iWidth; // ԭʼͼƬ��
	int m_iHeight; //ԭʼͼƬ��
	imageType m_imageType;//ԭͼ����
	//ͼ����Ϣ
	unsigned short *m_cur_luminance_tbl; //����������
	unsigned short *m_cur_chrominance_tbl; //ɫ��������
	int m_icomponents;


public:
	void FI2MAT(FIBITMAP* src, Mat& dst);
	bool MAT2FI(Mat& src, FIBITMAP* * dst);
	bool readImages(const string & srcImg,  const string dstImg);
	/*
	�������ܣ��õ�(source)ͼƬ�ĸ�ʽ
	����˵����
	strPath��ͼƬ���ļ���������·����
	����ֵ��������ܴ��ļ�����0��
	���ͼƬ��ʽΪJPG�򷵻�1��
	���Ϊ������ʽ�򷵻�2
	*/
	imageType getImageFormat();
	/*
	�������ܣ�����ԴͼƬ��Ŀ��ͼƬ�������Է�����
	����˵����
	srcImg��ԴͼƬ
	dstImg��Ŀ��ͼƬ
	����ֵ����������ͼƬ�Ƚ�֮�������ֵ��
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
	�������ܣ��õ�ͼƬ�����Ⱥ�ɫ��������
	����˵����
	src:ԴͼƬ���ļ�����
	lumi_quant[] :����õ�������������
	chro_quant[] :����õ���ɫ��������
	����ֵ��
	����ͼƬ����ɫͨ������
	*/
	bool GetDecompressInfo();//���srcͼ���ѹ����Ϣ������m_cur_luminance_tbl��m_cur_luminance_tbl��
	/*
	�������ܣ��������������������ͱ�׼����������õ���ӽ����������ӡ�
	����˵����
	lumi_quant[] : ���������������
	basic_table[] :��׼��������
	����ֵ��
	������ӽ���ͼƬ���������ӡ�
	*/
	int getNearestQuality(unsigned short lumi_quant[], const unsigned short basic_table[]);
	/*
	�������ܣ������������ӵõ�������
	����˵����
	quality:������������ӡ�
	qua_table:����õ���������
	basic_table:����ı�׼������
	����ֵ��
	�ޡ�
	*/
	void get_q_table_by_quality(int quality, unsigned short qua_table[], const unsigned short basic_table[]);
	/*
	�������ܣ��õ�����������ķ��
	����˵����
	lumi_quant[] �������������
	q_table[] :�����������
	n :����ĳ��ȡ�
	isAbs :�Ƿ�ȡ����ֵ�����ΪTRUE������ʱ��ȡ����ֵ�����ΪFALSE��ȡ����ֵ��
	����ֵ��
	��������������ķ��
	*/
	double getVariance(unsigned short lumi_quant[], const unsigned short q_table[], int n, bool isAbs);/*
/*
	�������ܣ������������Ӽ����������Ȼ��Ƚ�����luminance_quant�ķ��
	����˵����
		q_closet:�������ӡ�
		luminance_quant[]:Ҫ�Ƚϵ�������
	����ֵ��
		����������ķ��
*/
	double getVar(int q_closet, unsigned short luminance_quant[]);
	/*
	�������ܣ������ļ��Ĵ�С��
	����˵����
	src:Դ�ļ�����
	����ֵ��
	�ļ��Ĵ�С��byte��ʾ����
	*/
	unsigned long get_file_size(string src);
	/*
	�������ܣ�������������ͼƬ��
	����˵����
	srcFile :ԴͼƬ�ļ�����
	dstFile :Ŀ��ͼƬ�ļ�����
	q_closet:�������ӡ�
	����ֵ��
	�ޡ�
	*/
	bool saveJpegUseQuaTable(const std::string &srcFile, const std::string&dstFile, int quality);
	/*
	�������ܣ������ļ�
	����˵����
	srcFile��Դ�ļ�
	dstFile��Ŀ���ļ�
	����ֵ��
	����ļ����Ƴɹ�����true;
	����ļ���ֵʧ���򷵻�false��
	*/
	bool copyFile(const std::string & srcFile, const std::string & dstFile);
};

