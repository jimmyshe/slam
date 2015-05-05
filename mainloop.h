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
	//constant 
	cv::Mat cameraMatrix;
	cv::Mat distCoeff;
	int transformationType;

	//data
	cv::Mat pr_rgb;
	cv::Mat pr_d;
	double pr_timestamp;


	//data for later use



	void copy_old_frame();

	void cvtDepth2Cloud(const cv::Mat& depth, cv::Mat& cloud, const cv::Mat& cameraMatrix);

	void rgbdOdometry();

};


