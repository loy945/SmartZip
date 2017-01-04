#pragma once
#include <vector>
#include "imageNames.h"
#include <string>
class MultiRunning
{
public:
	MultiRunning();
	~MultiRunning();
	bool running(const std::string& src, const std::string& dst, int score);
	void consumer(int score);
	void producer(const string& src, const string& dst);
	static bool  isRunning;
	vector<imageNames>  qImages;
	vector<imageNames>  qImagesProcessed;
	virtual void progress(int rate);

};

