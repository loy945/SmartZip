#pragma once
#include<string>

using namespace std;



static enum imageType{
	JPEG,
	BMP,
	PNG,
	GIF,
	NotAccept
};


class imageNames
{
public:
	imageNames();
	~imageNames();
public:
	string src;
	string dst;
	imageType type;
};

