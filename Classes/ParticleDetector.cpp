#include "ParticleDetector.h"

ParticleDetector::ParticleDetector(Eigen::Vector3d _detectorLocation, std::vector<double> _energyNodes, double _distanceError)
{
	detectorLocation = _detectorLocation;
	energyNodes = _energyNodes;
	distanceError = _distanceError;
	virtualContributions.resize(energyNodes.size());
	std::fill(virtualContributions.begin(), virtualContributions.end(), 0.0);
}

Eigen::Vector3d ParticleDetector::getDetectorLocation()
{
	return detectorLocation;
}

void ParticleDetector::computeVirtualContribution(Particle* particle, int numParticles, Medium* medium)
{
	if (!particle->isAbsorbed())
	{
		int energyGroup = -1;
		for (double energyNode : energyNodes)
		{
			if (particle->getEnergy() / phys::MeV() > energyNode)
			{
				energyGroup++;
				continue;
			}
			else
			{
				break;
			}
		}

		double nodalStep = energyNodes.at(energyGroup + 1) - energyNodes.at(energyGroup);

		double angularDifferentialCrossSection = medium->getMediumMaterial()->getAtomicNumber() * pow(phys::classicalElectronRadius(), 2.0) / 2.0;
		double differentialCrossSection = 2 * M_PI * medium->getMediumMaterial()->getAtomicNumber() * pow(phys::classicalElectronRadius(), 2.0);

		double alpha = particle->getEnergy() / (phys::electronMass() * phys::lightSpeed() * phys::lightSpeed());
		double distance = (detectorLocation - particle->getLocation()).norm();
		double mu = particle->getScatteringCosine();

		angularDifferentialCrossSection *= pow(1.0 + alpha * (1.0 - mu), -2.0) * (1.0 + mu * mu + pow(alpha * (1.0 - mu), 2.0) / (1.0 + alpha * (1.0 - mu)));
		differentialCrossSection *= (1.0 + alpha) / (alpha * alpha) * (2.0 * (1.0 + alpha) / (1.0 + 2.0 * alpha) - log(1.0 + 2.0 * alpha) / alpha) +
			log(1.0 + 2.0 * alpha) / (2.0 * alpha) - (1.0 + 3.0 * alpha) / pow(1 + 2.0 * alpha, 2.0);

		medium->getMediumMaterial()->computeCrossSections(particle->getEnergy());

		virtualContributions.at(energyGroup) += particle->getVitality() * angularDifferentialCrossSection / differentialCrossSection *
			exp(-medium->getMediumMaterial()->getLinearMacroCrossSection() * (distance + distanceError)) / pow(distance + distanceError, 2.0) / numParticles;
	}
}

void ParticleDetector::recordVirtualContributions(std::string filePath)
{
	std::ofstream outFile;
	outFile.open(filePath);

	for (int i = 0; i < energyNodes.size(); i++)
	{
		outFile << energyNodes.at(i) << " " << virtualContributions.at(i) << "\n";
	}
	outFile.close();

	std::cout << "Файл " + filePath + " успешно создан" << std::endl;
}