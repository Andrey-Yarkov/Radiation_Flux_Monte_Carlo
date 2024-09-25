#include "ParticleSource.h"

ParticleSource::ParticleSource(Eigen::Vector3d _sourceCenterLocation, Shape* _sourceShape, Material* _sourceMaterial)
{
	sourceCenterLocation = _sourceCenterLocation;
	sourceShape = _sourceShape;
	sourceMaterial = _sourceMaterial;
	numProducedParticles = 0;
	ansemble = new ParticleAnsemble();
}

void ParticleSource::produceParticle()
{
	Eigen::Vector3d departurePoint = sourceCenterLocation + sourceShape->getRandInternalPoint();

	ansemble->addParticle(departurePoint, sourceMaterial->getQuantumEnergy());
	numProducedParticles++;
	departurePoints.push_back(departurePoint);

	ansemble->getParticles().back()->setDirection(getRandDirection());
}

int ParticleSource::getNumProducedParticles()
{
	return numProducedParticles;
}

Eigen::Vector3d ParticleSource::getRandDirection()
{
	double phi0 = 2.0 * M_PI * (double(std::rand()) / double(RAND_MAX));
	double cosTheta0 = double(std::rand()) / double(RAND_MAX);
	double theta0 = acos(cosTheta0);

	Eigen::Vector3d randDirection = Eigen::Vector3d(sin(theta0) * cos(phi0), sin(theta0) * sin(phi0), cos(theta0));

	return randDirection;
}

void ParticleSource::recordDeparturePoints(std::string filePath)
{
	std::ofstream outFile;
	outFile.open(filePath);

	Eigen::Vector3d departurePoint;
	for (int i = 0; i < getNumProducedParticles(); i++)
	{
		departurePoint = departurePoints.at(i);
		outFile << departurePoint.x() << " " << departurePoint.y() << " " << departurePoint.z() << "\n";
	}
	outFile.close();

	std::cout << "Файл " + filePath + " успешно создан" << std::endl;
}

ParticleAnsemble* ParticleSource::getParticleAnsemble()
{
	return ansemble;
}