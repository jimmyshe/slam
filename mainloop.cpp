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
using namespace Eigen;
MainLoop::MainLoop()
{
	R = MatrixXd::Zero(3, 3);
	T = MatrixXd::Zero(3, 1);

}


MainLoop::~MainLoop()
{
}


void MainLoop::ini()
{
	updataframe(); // initialize first frame 
						// rgb,d, keypoints,timestamp will be the first frame in dataset 

	for (int i = 0; i < number_particles; i++)   // initialize all the particles at origin point 0,0,0 with the weight 1/number of the particles
	{
		particles.push_back(Particle());
		particles.at(i).weight = 1 / number_particles;
	}


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
	RGBDOdometry(Rt, Mat(),
		grayImage0, depthFlt0, Mat(),
		grayImage1, depthFlt1, Mat(),
		cameraMatrix, minDepth, maxDepth, maxDepthDiff,
		iterCounts, minGradMagnitudes,RIGID_BODY_MOTION);


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			R(i, j) = Rt.at<double>(i, j);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		T(i, 0) = Rt.at<double>(i, 3);
	}

	
	cout << "R = " << R << endl;
	cout << "T = " << T << endl;
	//cout << "Rt= " << Rt << endl;


	return;
}

void MainLoop::sampling()
{

	for (int i = 1; i < number_particles; i++)
	{
	}

}
