
#pragma once
#include <fstream>;
#include <vector>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)



class ReadRGBD             //read frome data set
{
public:
	ReadRGBD(std::string);
	~ReadRGBD();
	bool capture(cv::Mat& rgb_frame, cv::Mat& d_frame, double& timestamp);

private:

	int index;


	std::string dataset_dir;

	std::vector<std::string> RGB_filelist;
	std::vector<double> RGB_timestamp;
	std::vector<std::string> D_filelist;
	std::vector<double> D_timestamp;

	void get_filelist(std::string);


};

