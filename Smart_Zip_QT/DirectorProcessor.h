#pragma once
#include <string>
#include "imageNames.h"
#include <vector>
using namespace std;

//����·����ع���
class DirectorProcessor
{
public:
	DirectorProcessor();
	~DirectorProcessor();
public:
	/*�����ڴ�Ŵ������ͼƬ��Ϣ������ԴͼƬ��ַ��Ŀ��ͼƬ��ַ��ͼƬ���ͷ������*/
	int processDirector(const string  &src, const  string & dst, vector<imageNames> *qImages);
	/*
	�������ܣ��õ�ͼƬ�ĸ�ʽ
	����˵����
	strPath��ͼƬ���ļ���������·����
	����ֵ��������ܴ��ļ�����0��
	���ͼƬ��ʽΪJPG�򷵻�1��
	���Ϊ������ʽ�򷵻�2
	*/
	imageType getImageFormat(const string & srcPath);
	/*
	�������ܣ������ļ�
	����˵����
	srcFile��Դ�ļ�
	dstFile��Ŀ���ļ�
	����ֵ��
	����ļ����Ƴɹ�����true;
	����ļ���ֵʧ���򷵻�false��
	*/

public:

	//ȫ��ͼƬ������
	int m_iTotalImages;
	string m_srcPath;//ԴͼƬ
	string m_dstPath;//Ŀ��ͼƬ
};

