#pragma once
#include "Features.h"



class MainLoop :
	private Features
{
public:
	MainLoop();
	~MainLoop();
	void ini();
	void run();

	

private:


	cv::Mat pr_rgb;
	cv::Mat pr_d;
	double pr_timestamp;


	void copy_old_frame();       


	cv::Ptr<cv::DescriptorMatcher> matcher;
	
	

};

