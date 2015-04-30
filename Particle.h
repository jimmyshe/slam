#pragma once
#include <opencv2/core/core.hpp>     

#include <eigen/Dense>

using namespace Eigen;
class Particle
{
public:
	Particle();
	~Particle();
	//data 

	MatrixXd pose;    // pose of particle 
	double weight;	  // weight of particle
	
	//kd tree here  

	//function

	void updatalandmark(cv::Point3d);
	///void updatapose();
	

};

