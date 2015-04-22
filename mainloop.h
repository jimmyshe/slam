#pragma once
#include "Features.h"



class mainloop :
	private Features
{
public:
	mainloop();
	~mainloop();
	void ini();
	void run();
	void debug_features();
	void debug_features_mataching();
	void find_homography();

private:


	cv::Mat pr_rgb;
	cv::Mat pr_d;
	double pr_timestamp;
	std::vector<cv::KeyPoint> pr_keypoints;
	cv::Mat pr_descriptors;

	std::vector<cv::DMatch > matches;
	std::vector<cv::DMatch > good_matches;
	cv::Mat H;


	void copy_old_frame();       
	void maching();
	void showmatches();

	cv::Ptr<cv::DescriptorMatcher> matcher;
	


};

