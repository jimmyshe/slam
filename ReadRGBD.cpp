#include "ReadRGBD.h"
#include <string>
#include <opencv2/highgui/highgui.hpp>
//#include <iostream>

using namespace std;




ReadRGBD::ReadRGBD(std::string location)
{
	dataset_dir = location + "/";
	get_filelist("rgb");
	get_filelist("depth");
	index = 0;
}

ReadRGBD::~ReadRGBD()
{
}

bool ReadRGBD::capture(cv::Mat& rgb_frame,cv::Mat& d_frame, double& timestamp)
{
	if (index == RGB_timestamp.size())
	{
		return false; // no data
	}

	timestamp = RGB_timestamp.at(index);
	rgb_frame = cv::imread(RGB_filelist.at(index), 1);
	d_frame = cv::imread(D_filelist.at(index), 1);
	index++;
	return true;
}

void ReadRGBD::get_filelist(string type)
{
	std::vector<std::string> list;
	string dir;
	dir = dataset_dir + type+".txt";
	fstream input;
	input.open(dir);

	double a;
	string b;
	if (type == "rgb")
	{
		while (input >> a)
		{
			input >> b;
			RGB_timestamp.push_back(a);
			RGB_filelist.push_back(dataset_dir + b);
		}

	}
	if (type == "depth")
	{
		while (input >> a)
		{
			input >> b;
			D_timestamp.push_back(a);
			D_filelist.push_back(dataset_dir + b);
		}

	}
	input.close();
	return ;
}

