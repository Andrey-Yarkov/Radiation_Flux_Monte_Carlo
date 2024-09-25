#pragma once
#include "Shape.h"
#include "Material.h"
#include "Particle.h"

class Medium
{
public:
	Medium(Eigen::Vector3d _mediumCenterLocation, Shape* _mediumShape, Material* _meduimMaterial);

	Material* getMediumMaterial();

	double getMeanFreePath(double energy);
	void checkOutOfBounds(Particle* particle);
	void checkParticleEnergy(Particle* particle);
	void particleInteraction(Particle* particle);

private:
	Eigen::Vector3d mediumCenterLocation;
	Shape* mediumShape;
	Material* meduimMaterial;
};

