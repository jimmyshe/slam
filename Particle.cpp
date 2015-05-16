#include "Particle.h"


Particle::Particle()
{
	pose = MatrixXd::Zero(3, 1);
	weight = 0;
}

Particle::Particle(const Particle& C)
{
	pose = C.pose;
	weight = C.weight;

	// need copy the whole kdtree there
}

Particle& Particle::operator=(const Particle& C)
{
	this->pose = C.pose;
	this->weight = C.weight;

	return *this;
}

Particle::~Particle()
{
}

void Particle::updatalandmark(cv::Point3d)
{

}