#include "Particle.h"


Particle::Particle()
{
	pose = MatrixXd::Zero(1, 3);
}


Particle::~Particle()
{
}

void Particle::updatalandmark(cv::Point3d)
{

}