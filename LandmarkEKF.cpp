#include "LandmarkEKF.h"
using namespace Eigen;

LandmarkEKF::LandmarkEKF(cv::Point3d observation)
{
	//EKF initialization
	//ini noise qt
	Qt = MatrixXd::Zero(3, 3);

	//ini the pose
	pose(0, 0) = observation.x;
	pose(0, 1) = observation.y;
	pose(0, 2) = observation.z;
	//ini the covariance 
	P = MatrixXd::Zero(3, 3);
	updataObservationJacobian();
	H = H.inverse();
	P = H*Qt*H.transpose();


}


LandmarkEKF::~LandmarkEKF()
{
}

void LandmarkEKF::updata(cv::Point3d observation)
{



}

void LandmarkEKF::updataObservationJacobian()
{
}