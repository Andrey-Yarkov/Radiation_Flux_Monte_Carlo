#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <fstream>

#include "Eigen/Eigen"
#include "Shape.h"
#include "Material.h"
#include "Particle.h"
#include "ParticleAnsemble.h"

class ParticleSource
{
public:
	ParticleSource(Eigen::Vector3d _sourceCenterLocation, Shape* _sourceShape, Material* _sourceMaterial);

	void produceParticle();
	int getNumProducedParticles();
	Eigen::Vector3d getRandDirection();
	void recordDeparturePoints(std::string filePath);
	ParticleAnsemble* getParticleAnsemble();

private:
	Eigen::Vector3d sourceCenterLocation;
	Shape* sourceShape;
	Material* sourceMaterial;
	int numProducedParticles;
	std::vector<Eigen::Vector3d> departurePoints;
	ParticleAnsemble* ansemble;
};