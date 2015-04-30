#pragma once
#include "ReadRGBD.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"

class Features :
	private ReadRGBD
{
public:
	Features();
	~Features();
	bool updataframe_old(); // compute new fram's features
	void updataframe();   //newer version (using when readRGBD has a buffer, will wait data)

	// public data (data of current frame)
	cv::Mat rgb;
	cv::Mat d;
	double timestamp;
	std::vector<cv::KeyPoint> keypoints;
	cv::Mat descriptors;
	std::vector<cv::Point3d> feature_point3_cloud;


	//debug

	bool features_test();

private:
	std::string features_type;
	cv::Ptr<cv::DescriptorExtractor> extractor;
	cv::Ptr<cv::FeatureDetector> detector;

	void project_points();   

	//camera parameters
	double fx = 525.0;
	double fy = 525.0; //  focal length
	double cx = 319.5;
	double cy = 239.5; //  optical center
	unsigned short min_dis = 800;         //
	unsigned short max_dis = 35000;       //


};

