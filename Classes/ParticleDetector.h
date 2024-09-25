#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>
#include <fstream>

#include "Eigen/Eigen"
#include "Particle.h"
#include "Medium.h"

class ParticleDetector
{
public:
	ParticleDetector(Eigen::Vector3d _detectorLocation, std::vector<double> _energyNodes, double _distanceError);

	Eigen::Vector3d getDetectorLocation();
	void computeVirtualContribution(Particle* particle, int numParticles, Medium* medium);

	void recordVirtualContributions(std::string filePath);

private:
	Eigen::Vector3d detectorLocation;
	std::vector<double> energyNodes;
	double distanceError;
	std::vector<double> virtualContributions;
};