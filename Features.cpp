#include "Features.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/nonfree/features2d.hpp"
#include <opencv2/nonfree/nonfree.hpp> 
#include <iostream>
#include "camera_config.h"


using namespace cv;

Features::Features():ReadRGBD("C:/Users/cq2essz/Documents/Visual Studio 2013/Projects/slam/rgbd_dataset")
{
	/*The following detector types are supported:

	"FAST" 每 FastFeatureDetector
	"STAR" 每 StarFeatureDetector
	"SIFT" 每 SIFT (nonfree module)
	"SURF" 每 SURF (nonfree module)
	"ORB" 每 ORB
	"BRISK" 每 BRISK
	"MSER" 每 MSER
	*/

	cv::initModule_nonfree();   // only needed when using surf or sift

	detector = FeatureDetector::create("ORB");
	extractor = DescriptorExtractor::create("SURF");

	//detector->set("someParam", someValue)   // use this to set parameter of detector and the same way to set extractor



	
}


Features::~Features()
{

}



bool Features::updataframe_old()
{
	
	if (capture(rgb, d, timestamp))
	{
		detector->detect(rgb, keypoints);
		extractor->compute(rgb, keypoints,descriptors);
		return true;
	}
	else
	{
		return false;   //no frame in the data set
	}
}


void Features::updataframe()
{
	while (capture(rgb, d, timestamp)==false)
	{
		std::cout << "no data!! wait for one second " << std::endl;
		waitKey(1000);
	}
	keypoints.clear();
	detector->detect(rgb, keypoints);
	//extractor->compute(rgb, keypoints, descriptors);    //婃奀祥蚚
	project_points();
}




bool Features::features_test()
{
	if (updataframe_old() == false)
	{
		return false;
	}

	Mat img_keypoints;
	drawKeypoints(rgb, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("Keypoints", img_keypoints);

	return true;
}

void Features::project_points()
{

	feature_point3_cloud.clear();
	for (int i = 0; i < keypoints.size(); i++)
	{
		auto d_val = d.at<unsigned short>(keypoints.at(i).pt.y, keypoints.at(i).pt.x);
		if (min_dis < d_val && d_val < max_dis)       
		{                 
			double z = d_val / 10000.0;   //convert to m
			double x = (keypoints.at(i).pt.x - cx) * z / fx;
			double y = (keypoints.at(i).pt.y - cy) * z / fy;
			feature_point3_cloud.push_back(Point3d(x, y, z));
		}
	}
}
