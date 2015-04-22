#include "Features.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/nonfree/features2d.hpp"
#include <opencv2/nonfree/nonfree.hpp> 
#include <iostream>


using namespace cv;

Features::Features():ReadRGBD("/home/ial/workspace/rgbd_dataset_freiburg2_large_with_loop")
{
	/*The following detector types are supported:

	"FAST" �C FastFeatureDetector
	"STAR" �C StarFeatureDetector
	"SIFT" �C SIFT (nonfree module)
	"SURF" �C SURF (nonfree module)
	"ORB" �C ORB
	"BRISK" �C BRISK
	"MSER" �C MSER
	*/

	cv::initModule_nonfree();   // only needed when using surf or sift

	detector = FeatureDetector::create("ORB");
	extractor = DescriptorExtractor::create("SURF");

	//detector->set("someParam", someValue)   // use this to set parameter of detector and the same way to set extractor



	
}


Features::~Features()
{
	//delete detector;
	//delete extractor;
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
	while (!capture(rgb, d, timestamp))
	{
		std::cout << "no data!! wait for one second " << std::endl;
		waitKey(1000);
	}
	detector->detect(rgb, keypoints);
	extractor->compute(rgb, keypoints, descriptors);
}




bool Features::features_test()
{
	if (!updataframe_old())
	{
		return false;
	}

	Mat img_keypoints;
	drawKeypoints(rgb, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("Keypoints", img_keypoints);

	return true;
}

