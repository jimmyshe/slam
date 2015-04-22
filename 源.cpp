#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur

#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O


//#include "ReadRGBD.h"
//#include "Features.h"
#include "mainloop.h"



using namespace std;
using namespace cv;

void debug_readrgbd();
void debug_features();


int main(int argc, char *argv[])
{	

	mainloop slam;
	slam.debug_features_mataching();
	//slam.debug_features();
	return 0;
}



/*
void debug_readrgbd()
{
	ReadRGBD data("C:/Users/cq2essz/Documents/Visual Studio 2013/Projects/slam/rgbd_dataset");
	double timestamp;
	cv::Mat rgb_frame;
	cv::Mat d_frame;

	namedWindow("rgb window", WINDOW_AUTOSIZE); // Create a window for display.
	namedWindow("depth window", WINDOW_AUTOSIZE);
	moveWindow("depth window", 700, 0);


	while (data.capture(rgb_frame, d_frame, timestamp))
	{
		imshow("rgb window", rgb_frame);
		imshow("depth window", d_frame);
		waitKey(30);

	}
	return;
}
*/
