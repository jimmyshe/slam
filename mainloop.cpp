#include "MainLoop.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>

using namespace cv;

MainLoop::MainLoop()
{
	matcher = DescriptorMatcher::create("FlannBased"); 
	/*descriptorMatcherType ¨C
	Descriptor matcher type.Now the following matcher types are supported :

	BruteForce(it uses L2)
		BruteForce-L1
		BruteForce-Hamming
		BruteForce-Hamming(2)
		FlannBased
		*/
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

	return;
}





void MainLoop::copy_old_frame()
{
	pr_rgb = rgb.clone();
	pr_d = d.clone();
	pr_timestamp = timestamp;


	return;
}



