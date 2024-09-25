#pragma once
#include <string>
#include <math.h>
#include <vector>

#include "Phys.h"

class Material
{
public:
	Material(std::string _materialName);

	double getQuantumEnergy();
	double getAtomicMass();
	int getAtomicNumber();
	double getDensity();
	double getConcentration();
	double getParticleMinimumEnergy();
	
	void computeCrossSections(double energy);
	double getScatterMacroCrossSection();
	double getPhotoelAbsorbMacroCrossSection();
	double getPairProdMacroCrossSection();
	double getLinearMacroCrossSection();

private:
	std::string materialName;
	double quantumEnergy;
	double atomicMass;
	int atomicNumber;
	double density;
	double concentration;
	double particleMinimumEnergy;

	double scatterMacroCrossSection;
	double photoelAbsorbMacroCrossSection;
	double pairProdMacroCrossSection;
	double linearMacroCrossSection;
};

