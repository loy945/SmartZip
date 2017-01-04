#include <QDebug>
#include "MultiRunning.h"
#include "Compressor.h"

#include<iostream>
#include "direct.h"
#include <iostream>           
#include <queue>

#include <mutex>             
#include <condition_variable> 
#include <stdio.h>
#include <stdlib.h>
#include <thread>
using namespace std;

mutex mtx;
condition_variable produce, consume;
bool  MultiRunning::isRunning = true;
static int compressorNums = 0;
queue<int> q;     // shared value by producers and consumers, which is the critical section

DirectorProcessor * dp;
Compressor * cp1 = nullptr;
int maxSize = 20;
bool compressionStart = false;
void MultiRunning::consumer(int score)
{
	while (MultiRunning::isRunning == true)
	{
		unique_lock<mutex> lck(mtx);
		consume.wait(lck, [&] {
			return qImages.size() != 0;

		});     // wait(block) consumer when q.size() == 0

		//cout << "consumer " << this_thread::get_id() << ": ";
		imageNames im;
		if (qImages.size() > 0)
		{
			im = qImages.at(0);
			qImagesProcessed.push_back(im);
			qImages.erase(qImages.begin());
			if (cp1)
			{
				delete cp1;
				cp1 = nullptr;
			}
			compressorNums++;
			fstream logFile("Compress.log", ios::app);
			logFile << im.src << " start£¡" << endl;
			logFile.close();
			cp1 = new Compressor();
			cp1->Compress(compressorNums, im.src, im.dst,score);
			fstream logFile2("Compress.log", ios::app);
			logFile2 << im.src << " success£¡" << endl;
			logFile2.close();
			int num = qImagesProcessed.size();
			int sunmNum = qImagesProcessed.size() + qImages.size();
			int rate = (int )(float(num) / float(sunmNum) * 100.0);
			progress(rate);

		}
		if (qImages.size() == 0)
		{
			cout << "end" << endl;
			MultiRunning::isRunning = false;
			break;
		}
		else
		{
			cout << "imageNums remain:" << qImages.size() << '\n';
			qDebug() << "imageNums remain:" << qImages.size() << '\n';
		}


		produce.notify_all();                             // nodity(wake up) producer when q.size() != maxSize
	}
}

void MultiRunning::producer(const string& src, const string& dst)
{
	//while (true)
	{
		//this_thread::sleep_for(chrono::milliseconds(900));      // producer is a little faster than consumer  

		unique_lock<mutex> lck(mtx);
		produce.wait(lck, [&] {return qImages.size() != maxSize; });   // wait(block) producer when q.size() == maxSize 

		//cout << "-> producer " << this_thread::get_id() << ": ";
		cout << "\n------Seletecing Images:-----";
		dp->processDirector(src, dst, &qImages);
		cout << "\n------------end------------\n";
		//q.push(id);
		qDebug() << "total imageNums:" << qImages.size() << '\n';
		cout << "total imageNums:" << qImages.size() << '\n';
		compressionStart = true;
		consume.notify_all();                                    // notify(wake up) consumer when q.size() != 0    
	}
}

MultiRunning::MultiRunning()
{
	
}

void MultiRunning::progress(int rate)
{

}
MultiRunning::~MultiRunning()
{
}

bool MultiRunning::running(const string& src, const string& dst, int score)
{
// 	string imageSrcPath = "D:\\images";
// 	string imageDstPath = imageSrcPath + string("_compressed");
	MultiRunning::isRunning = true;
	string imageSrcPath = src;
	string imageDstPath = dst;
	//qImages.clear();
//	qImagesProcessed.clear();
	while (qImages.size() > 0)
	{
// 		imageNames * im = &qImages.at(0);
// 		delete im;
		qImages.pop_back();
	}
	//qImages.clear();
	while (qImagesProcessed.size() > 0)
	{
// 		imageNames * im = &qImagesProcessed.at(0);
// 		delete im;
		qImagesProcessed.pop_back();
	}
	//qImagesProcessed.clear();

	qDebug() << "R: " << imageSrcPath.c_str();
	qDebug() << "R: " << imageDstPath.c_str();
	for (int i = 0; i < imageSrcPath.size();i++)
	{
		if (imageSrcPath[i]=='/')
		{
			imageSrcPath[i] = '\\';
		}
	}
	for (int i = 0; i < imageDstPath.size(); i++)
	{
		if (imageDstPath[i] == '/')
		{
			imageDstPath[i] = '\\';
		}
	}
	qDebug() << "edit: " << imageSrcPath.c_str();
	qDebug() << "edit: " << imageDstPath.c_str();
	_mkdir(imageDstPath.c_str());
	dp = new DirectorProcessor();

	int compressorNums = 1;
	producer(imageSrcPath, imageDstPath);
	consumer(score);

	thread *consumers, producers;
	consumers = new thread[compressorNums];
	producers = thread(&MultiRunning::producer, this, imageSrcPath, imageDstPath);
	for (int i = 0; i < compressorNums; ++i)
	{
		consumers[i] = thread(&MultiRunning::consumer, this, score);
	}

	producers.join();
	for (int i = 0; i < compressorNums; ++i)
	{
		consumers[i].join();
	}
	return true;
}
