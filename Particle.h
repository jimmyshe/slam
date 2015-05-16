#pragma once
#include <opencv2/core/core.hpp>     

#include <eigen/Dense>
#include "LandmarkEKF.h"
using namespace Eigen;
class Particle
{
public:
	Particle();
	Particle(const Particle& C);
	Particle& operator=(const Particle & C);

	~Particle();

	//data 

	MatrixXd pose;    // pose of particle 
	double weight;	  // weight of particle
	
	//kd tree here  

	struct kdnood
	{
		kdnood *left;
		kdnood *right;
		LandmarkEKF *ekf;
	};


	//function

	void updatalandmark(cv::Point3d);
	///void updatapose();
	

};

