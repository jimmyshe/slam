#include "MainLoop.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <iostream>

using namespace cv;
using namespace std;
MainLoop::MainLoop()
{



}


MainLoop::~MainLoop()
{
}


void MainLoop::ini()
{
	updataframe(); // initialize first frame 
						// rgb,d, keypoints,timestamp will be the first frame in dataset 
}



void MainLoop::run()
{
	ini();
	while (true)
	{
		copy_old_frame();
		updataframe();
		rgbdOdometry();

	}


	return;
}





void MainLoop::copy_old_frame()
{
	pr_rgb = rgb.clone();
	pr_d = d.clone();
	pr_timestamp = timestamp;
	return;
}



void MainLoop::cvtDepth2Cloud(const Mat& depth, Mat& cloud, const Mat& cameraMatrix)
{
	const float inv_fx = 1.f / cameraMatrix.at<float>(0, 0);
	const float inv_fy = 1.f / cameraMatrix.at<float>(1, 1);
	const float ox = cameraMatrix.at<float>(0, 2);
	const float oy = cameraMatrix.at<float>(1, 2);
	cloud.create(depth.size(), CV_32FC3);
	for (int y = 0; y < cloud.rows; y++)
	{
		Point3f* cloud_ptr = (Point3f*)cloud.ptr(y);
		const float* depth_prt = (const float*)depth.ptr(y);
		for (int x = 0; x < cloud.cols; x++)
		{
			float z = depth_prt[x];
			cloud_ptr[x].x = (x - ox) * z * inv_fx;
			cloud_ptr[x].y = (y - oy) * z * inv_fy;
			cloud_ptr[x].z = z;
		}
	}
}

void MainLoop::rgbdOdometry()
{
	float vals[] = { 525., 0., 3.1950000000000000e+02,
		0., 525., 2.3950000000000000e+02,
		0., 0., 1. };

	const Mat cameraMatrix = Mat(3, 3, CV_32FC1, vals);
	const Mat distCoeff(1, 5, CV_32FC1, Scalar(0));




	Mat grayImage0, grayImage1, depthFlt0, depthFlt1;

	cvtColor(pr_rgb, grayImage0, CV_BGR2GRAY);
	cvtColor(rgb, grayImage1, CV_BGR2GRAY);
	pr_d.convertTo(depthFlt0, CV_32FC1, 1./10000);
	d.convertTo(depthFlt1, CV_32FC1, 1./10000);
	TickMeter tm;

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

	const float minDepth = 0.8f; //in meters
	const float maxDepth = 3.5f; //in meters
	const float maxDepthDiff = 0.07f; //in meters
	Mat Rt;
	tm.start();
	RGBDOdometry(Rt, Mat(),
		grayImage0, depthFlt0, Mat(),
		grayImage1, depthFlt1, Mat(),
		cameraMatrix, minDepth, maxDepth, maxDepthDiff,
		iterCounts, minGradMagnitudes,RIGID_BODY_MOTION);
	tm.stop();

	cout << "Rt = " << Rt << endl;
	cout << "Time = " << tm.getTimeSec() << " sec." << endl;


	return;
}

