#pragma once
#include <Eigen/Dense>
#include <opencv2/core/core.hpp>
using namespace Eigen;
class LandmarkEKF
{
public:

	LandmarkEKF(cv::Point3d observation);

	~LandmarkEKF();

	void updata(cv::Point3d observation);


	MatrixXd pose;



private:
	MatrixXd P;   //covariance 




};

