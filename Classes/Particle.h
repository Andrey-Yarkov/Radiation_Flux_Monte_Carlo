#pragma once
#include "Eigen/Eigen"

class Particle
{
public:
	Particle(Eigen::Vector3d _location, double _energy);

	void setLocation(Eigen::Vector3d _location);
	Eigen::Vector3d getLocation();

	void setDirection(Eigen::Vector3d _direction);
	Eigen::Vector3d getDirection();

	void setEnergy(double _energy);
	double getEnergy();

	void setScatteringCosine(double _scatteringCosine);
	double getScatteringCosine();

	void setVitality(double _vitality);
	double getVitality();

	void free();
	void encage();
	bool isMovable();

	void absorb();
	bool isAbsorbed();

	void moveParticle(double length);

private:
	Eigen::Vector3d location;
	Eigen::Vector3d direction;
	double energy;
	double scatteringCosine;
	double vitality;
	bool movable;
	bool absorbed;
};

