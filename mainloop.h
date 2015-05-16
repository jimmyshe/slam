#pragma once
#include "Features.h"
#include "Particle.h"


class MainLoop :
	private Features
{
public:
	MainLoop();
	~MainLoop();
	void ini();
	void run();

	

private:
	//constant 

	static const int number_particles = 100;

	//data
	cv::Mat pr_rgb;
	cv::Mat pr_d;
	double pr_timestamp;

	std::vector<Particle> particles;

	//Particle *particles[number_particles];



	//data for later use
	Eigen::MatrixXd R;                      // rotation matrix and transformation matrix 
	Eigen::MatrixXd T;

	//Inner functions 
	void copy_old_frame();
	void rgbdOdometry();
	void sampling();
};


