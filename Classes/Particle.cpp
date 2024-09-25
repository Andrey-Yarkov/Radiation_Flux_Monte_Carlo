#include "Particle.h"

Particle::Particle(Eigen::Vector3d _location, double _energy)
{
	location = _location;
	energy = _energy;
	vitality = 1.0;
	movable = true;
	absorbed = false;
}

void Particle::setLocation(Eigen::Vector3d _location)
{
	location = _location;
}
Eigen::Vector3d Particle::getLocation()
{
	return location;
}

void Particle::setDirection(Eigen::Vector3d _direction)
{
	direction = _direction;
}
Eigen::Vector3d Particle::getDirection()
{
	return direction;
}

void Particle::setEnergy(double _energy)
{
	energy = _energy;
}
double Particle::getEnergy()
{
	return energy;
}

void Particle::setScatteringCosine(double _scatteringCosine)
{
	scatteringCosine = _scatteringCosine;
}
double Particle::getScatteringCosine()
{
	return scatteringCosine;
}

void Particle::setVitality(double _vitality)
{
	if (_vitality < 1.0)
	{
		vitality = _vitality;
	}
	else
	{
		vitality = 1.0;
	}
}
double Particle::getVitality()
{
	return vitality;
}

void Particle::free()
{
	movable = true;
}
void Particle::encage()
{
	movable = false;
}
bool Particle::isMovable()
{
	return movable;
}

void Particle::absorb()
{
	absorbed = true;
	encage();
}
bool Particle::isAbsorbed()
{
	return absorbed;
}

void Particle::moveParticle(double length)
{
	if (movable)
	{
		location += length * direction / direction.norm();
	}
}