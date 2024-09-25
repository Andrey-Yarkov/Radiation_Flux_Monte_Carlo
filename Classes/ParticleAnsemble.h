#pragma once
#include <fstream>

#include "Particle.h"
#include "Medium.h"

class ParticleAnsemble
{
public:
	ParticleAnsemble();

	std::vector<Particle*> getParticles();
	void addParticle(Eigen::Vector3d location, double energy);
	Particle* getParticle(int i);
	void recordActiveParticleLocations(std::string filePath);
	void recordAbsorbedParticleLocations(std::string filePath);

private:
	std::vector<Particle*> particles;
};

