



//#include "ReadRGBD.h"
//#include "Features.h"
#include "MainLoop.h"



using namespace std;
using namespace cv;




int main(int argc, char *argv[])
{	

	MainLoop slam;
	slam.run();
	//slam.debug_features();
	return 0;
}


/*

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <iostream>
#include <ctime>

using namespace cv;
using namespace std;





int main(int argc, char** argv)
{
	float vals[] = { 525., 0., 3.1950000000000000e+02,
		0., 525., 2.3950000000000000e+02,
		0., 0., 1. };

	const Mat cameraMatrix = Mat(3, 3, CV_32FC1, vals);
	const Mat distCoeff(1, 5, CV_32FC1, Scalar(0));



	Mat colorImage0 = imread("C:/Users/cq2essz/Documents/Visual Studio 2013/Projects/slam/rgbd_dataset/rgb/1311875572.406161.png");
	Mat depth0 = imread("C:/Users/cq2essz/Documents/Visual Studio 2013/Projects/slam/rgbd_dataset/depth/1311875572.382063.png");

	Mat colorImage1 = imread("C:/Users/cq2essz/Documents/Visual Studio 2013/Projects/slam/rgbd_dataset/rgb/1311875572.438063.png");
	Mat depth1 = imread("C:/Users/cq2essz/Documents/Visual Studio 2013/Projects/slam/rgbd_dataset/depth/1311875572.417883.png");

	if (colorImage0.empty() || depth0.empty() || colorImage1.empty() || depth1.empty())
	{
		cout << "Data (rgb or depth images) is empty.";
		return -1;
	}


	int transformationType = RIGID_BODY_MOTION;


	Mat grayImage0, grayImage1, depthFlt0, depthFlt1;
	cvtColor(colorImage0, grayImage0, COLOR_BGR2GRAY);
	cvtColor(colorImage1, grayImage1, COLOR_BGR2GRAY);
	depth0.convertTo(depthFlt0, CV_32FC1, 1. / 1000);
	depth1.convertTo(depthFlt1, CV_32FC1, 1. / 1000);

	TickMeter tm;
	Mat Rt;

	vector<int> iterCounts(4);
	iterCounts[0] = 7;
	iterCounts[1] = 7;
	iterCounts[2] = 7;
	iterCounts[3] = 10;

	vector<float> minGradMagnitudes(4);
	minGradMagnitudes[0] = 12;
	minGradMagnitudes[1] = 5;
	minGradMagnitudes[2] = 3;
	minGradMagnitudes[3] = 1;

	const float minDepth = 0.f; //in meters
	const float maxDepth = 4.f; //in meters
	const float maxDepthDiff = 0.07f; //in meters

	tm.start();
	bool isFound = cv::RGBDOdometry(Rt, Mat(),
		grayImage0, depthFlt0, Mat(),
		grayImage1, depthFlt1, Mat(),
		cameraMatrix, minDepth, maxDepth, maxDepthDiff,
		iterCounts, minGradMagnitudes, transformationType);
	tm.stop();

	cout << "Rt = " << Rt << endl;
	cout << "Time = " << tm.getTimeSec() << " sec." << endl;

	if (!isFound)
	{
		cout << "Rigid body motion cann't be estimated for given RGBD data." << endl;
		return -1;
	}

	
	waitKey();

	return 0;
}



*/