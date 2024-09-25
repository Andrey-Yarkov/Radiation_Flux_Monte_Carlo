#include "Medium.h"

Medium::Medium(Eigen::Vector3d _mediumCenterLocation, Shape* _mediumShape, Material* _meduimMaterial)
{
	mediumCenterLocation = _mediumCenterLocation;
	mediumShape = _mediumShape;
	meduimMaterial = _meduimMaterial;
}

Material* Medium::getMediumMaterial()
{
	return meduimMaterial;
}

double Medium::getMeanFreePath(double energy)
{
	meduimMaterial->computeCrossSections(energy);
	double meanFreePath = -log((double(std::rand()) / double(RAND_MAX))) / meduimMaterial->getLinearMacroCrossSection();
	
	return meanFreePath;
}

void Medium::checkOutOfBounds(Particle* particle)
{
	if (!(mediumShape->inside(particle->getLocation() - mediumCenterLocation)))
	{
		particle->absorb();
	}
}

void Medium::checkParticleEnergy(Particle* particle)
{
	if (particle->getEnergy() < meduimMaterial->getParticleMinimumEnergy())
	{
		particle->absorb();
	}
}

void Medium::particleInteraction(Particle* particle)
{
	if (!particle->isAbsorbed())
	{
		meduimMaterial->computeCrossSections(particle->getEnergy());

		double interactionRandomValue = double(std::rand()) / double(RAND_MAX);
		if (meduimMaterial->getScatterMacroCrossSection() / meduimMaterial->getLinearMacroCrossSection() < interactionRandomValue)
		{
			particle->absorb();
		}
		else
		{
			double alphaPrev = particle->getEnergy() / (phys::electronMass() * phys::lightSpeed() * phys::lightSpeed());
			
			double firstRandomValue;
			double secondRandomValue;
			double x;
			double p;
			do
			{
				firstRandomValue = double(std::rand()) / double(RAND_MAX);
				secondRandomValue = double(std::rand()) / double(RAND_MAX);

				x = alphaPrev * (1.0 + 2.0 * alphaPrev * firstRandomValue) / (1.0 + 2.0 * alphaPrev);
				p = x / alphaPrev + alphaPrev / x + (1.0 / alphaPrev - 1.0 / x) * (2.0 + 1.0 / alphaPrev - 1.0 / x);

			} while (secondRandomValue * (1.0 + 2.0 * alphaPrev + 1.0 / (1.0 + 2.0 * alphaPrev)) > p);
			
			double alpha = x;
			double cosThetaS = 1.0 - 1.0 / alpha + 1.0 / alphaPrev;
			particle->setScatteringCosine(cosThetaS);

			double phiS = 2 * M_PI * double(std::rand()) / double(RAND_MAX);

			Eigen::Vector3d directionPrev = particle->getDirection();
			Eigen::Vector3d direction;

			direction.z() = directionPrev.z() * cosThetaS + cos(phiS) *
				pow(abs((1.0 - cosThetaS * cosThetaS) * (1.0 - directionPrev.z() * directionPrev.z())), 0.5);
			direction.y() = (directionPrev.y() * (cosThetaS - directionPrev.z() * direction.z()) + directionPrev.x() * sin(phiS) *
				pow(abs((1.0 - cosThetaS * cosThetaS) * (1.0 - directionPrev.z() * directionPrev.z())), 0.5)) / 
				(1.0 - directionPrev.z() * directionPrev.z() + 1e-6);
			direction.x() = (directionPrev.x() * (cosThetaS - directionPrev.z() * direction.z()) - directionPrev.y() * sin(phiS)*
				pow(abs((1.0 - cosThetaS * cosThetaS) * (1.0 - directionPrev.z() * directionPrev.z())), 0.5)) /
				(1.0 - directionPrev.z() * directionPrev.z() + 1e-6);

			particle->setEnergy(alpha * phys::electronMass() * phys::lightSpeed() * phys::lightSpeed());
			particle->setDirection(direction);
		}
	}
}