#include "ParticleAnsemble.h"

ParticleAnsemble::ParticleAnsemble()
{

}

std::vector<Particle*> ParticleAnsemble::getParticles()
{
	return particles;
}

void ParticleAnsemble::addParticle(Eigen::Vector3d location, double energy)
{
	particles.push_back(new Particle(location, energy));
}

Particle* ParticleAnsemble::getParticle(int i)
{
	return particles.at(i);
}

void ParticleAnsemble::recordActiveParticleLocations(std::string filePath)
{
	std::ofstream outFile;
	outFile.open(filePath);

	Eigen::Vector3d particleLocation;
	for (int i = 0; i < particles.size(); i++)
	{
		if (!getParticle(i)->isAbsorbed())
		{
			particleLocation = getParticle(i)->getLocation();
			outFile << particleLocation.x() << " " << particleLocation.y() << " " << particleLocation.z() << "\n";
		}
	}
	outFile.close();

	std::cout << "Файл " + filePath + " успешно создан" << std::endl;
}

void ParticleAnsemble::recordAbsorbedParticleLocations(std::string filePath)
{
	std::ofstream outFile;
	outFile.open(filePath);

	Eigen::Vector3d particleLocation;
	for (int i = 0; i < particles.size(); i++)
	{
		if (getParticle(i)->isAbsorbed())
		{
			particleLocation = getParticle(i)->getLocation();
			outFile << particleLocation.x() << " " << particleLocation.y() << " " << particleLocation.z() << "\n";
		}
	}
	outFile.close();

	std::cout << "Файл " + filePath + " успешно создан" << std::endl;
}