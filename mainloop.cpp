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


void MainLoop::debug_features()
{

	while (features_test())
	{
		waitKey(5);
	}


	waitKey(0);
	return;

}








void MainLoop::debug_features_matching()   
{
	ini();
	while (true)
	{
		copy_old_frame();
		updataframe();
		matching();
		find_homograph();
		showmatches();
		waitKey(10);
	}
	
	return;

}

void MainLoop::copy_old_frame()
{
	pr_rgb = rgb.clone();
	pr_d = d.clone();
	pr_timestamp = timestamp;
	pr_keypoints = keypoints;
	pr_descriptors = descriptors.clone();

	return;
}

void MainLoop::matching()
{
	
	matcher->match(pr_descriptors, descriptors, matches);

	good_matches.clear();
	//-- Quick calculation of max and min distances between keypoints
	double max_dist = 0; double min_dist = 100;

	for (int i = 0; i < pr_descriptors.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	for (int i = 0; i < pr_descriptors.rows; i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 0.1))
		{
			good_matches.push_back(matches[i]);
		}
	}
	return;
}

void MainLoop::find_homograph()
{
	int minfeatures = 5;
	std::vector<Point2f> pr;
	std::vector<Point2f> cu;
	

	

	if (good_matches.size() >= minfeatures){

		for ( int i = 0; i < good_matches.size(); i++)
		{
			//-- Get the keypoints from the good matches
			pr.push_back(pr_keypoints[good_matches[i].queryIdx].pt);
			cu.push_back(keypoints[good_matches[i].trainIdx].pt);
		}
		H = findHomography(pr, cu, CV_RANSAC).clone();
	}
	else
	{
		std::cout << "not enough valid features" << std::endl;
		for (int i = 0; i < matches.size(); i++)
		{
			//-- Get the keypoints from the all matches
			pr.push_back(pr_keypoints[matches[i].queryIdx].pt);
			cu.push_back(keypoints[matches[i].trainIdx].pt);
		}

		H = findHomography(pr, cu, CV_RANSAC).clone();


	}

	return;

}




void MainLoop::showmatches()
{
	Mat img_matches;
	drawMatches(pr_rgb, pr_keypoints, rgb, keypoints,good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);//-- Draw matches
	//drawMatches(pr_rgb, pr_keypoints, rgb, keypoints, matches, img_matches);                                                                                              //draw all the matches
	imshow("Matches", img_matches);//-- Show detected matches
}