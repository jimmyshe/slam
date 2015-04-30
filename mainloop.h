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
	void debug_features();
	void debug_features_matching();
	

private:


	cv::Mat pr_rgb;
	cv::Mat pr_d;
	double pr_timestamp;
	std::vector<cv::KeyPoint> pr_keypoints;
	cv::Mat pr_descriptors;

	std::vector<cv::DMatch > matches;
	std::vector<cv::DMatch > good_matches;
	cv::Mat H;

	void find_homograph();
	void copy_old_frame();       
	void matching();
	void showmatches();

	cv::Ptr<cv::DescriptorMatcher> matcher;
	
	

};

