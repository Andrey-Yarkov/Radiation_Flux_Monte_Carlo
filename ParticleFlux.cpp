#include <iostream>
#include <string>
#include <direct.h>

#include "Eigen/Eigen"
#include "Namespaces\Phys.h"
#include "Classes\Shape.h"
#include "Classes\Material.h"
#include "Classes\ParticleSource.h"
#include "Classes\Medium.h"
#include "Classes\ParticleDetector.h"

void particleInteractions();
void particleDetection();


int main()
{
	setlocale(LC_ALL, "Russian"); // Отображение кириллицы в консоли
	std::cout.precision(6); // Точность вывода десятичных чисел
	std::srand(time(0)); // Синхронизация рандомайзера с текущем временем

	particleInteractions();
	particleDetection();
}


void particleInteractions()
{
	std::string particleInteractionsFolder = "particle_interactions/";
	std::string activeParticlesFolder = particleInteractionsFolder + "active/";
	std::string absorbedParticlesFolder = particleInteractionsFolder + "absorbed/";

	bool particleInteractionsFolderCreated = _mkdir(particleInteractionsFolder.c_str());
	bool activeParticlesFolderCreated = _mkdir(activeParticlesFolder.c_str());
	bool absorbedParticlesFolderCreated = _mkdir(absorbedParticlesFolder.c_str());

	double sourceLength = 15.0 * phys::cm();
	double sourceWidth = 30.0 * phys::cm();
	double mediumLength = 60.0 * phys::cm();
	double mediumWidth = 80.0 * phys::cm();
	double mediumHeight = 20.0 * phys::cm();

	int numInteractions = 4;

	std::vector<int> numParticles = { 100, 500, 1000 };
	for (int n : numParticles)
	{
		Eigen::Vector3d sourceCenter = Eigen::Vector3d(0.0, 0.0, 0.0);
		Shape* sourceShape = new Ellipse(sourceLength, sourceWidth, 0.0);
		Material* sourceMaterial = new Material("Cobalt-60");
		ParticleSource* source = new ParticleSource(sourceCenter, sourceShape, sourceMaterial);

		Eigen::Vector3d mediumCenter = Eigen::Vector3d(0.0, 0.0, mediumHeight / 2.0);
		Shape* mediumShape = new Parallelepiped(mediumLength, mediumWidth, mediumHeight);
		Material* mediumMaterial = new Material("Aluminium");
		Medium* medium = new Medium(mediumCenter, mediumShape, mediumMaterial);

		ParticleAnsemble* particleAnsemble = source->getParticleAnsemble();

		for (int i = 0; i < n; i++)
		{
			source->produceParticle();
			medium->checkParticleEnergy(particleAnsemble->getParticle(i));
			if (particleAnsemble->getParticle(i)->isAbsorbed())
			{
				continue;
			}
		}
		source->recordDeparturePoints(particleInteractionsFolder + "DeparturePoints_" + std::to_string(n) + ".mat");

		for (int interactionNumber = 1; interactionNumber <= numInteractions; interactionNumber++)
		{
			for (int i = 0; i < n; i++)
			{
				if (particleAnsemble->getParticle(i)->isAbsorbed())
				{
					continue;
				}
				particleAnsemble->getParticle(i)->moveParticle(medium->getMeanFreePath(particleAnsemble->getParticle(i)->getEnergy()));
				medium->checkOutOfBounds(particleAnsemble->getParticle(i));
				if (particleAnsemble->getParticle(i)->isAbsorbed())
				{
					continue;
				}
				medium->particleInteraction(particleAnsemble->getParticle(i));
				medium->checkParticleEnergy(particleAnsemble->getParticle(i));
			}
			particleAnsemble->recordActiveParticleLocations(activeParticlesFolder + "ActLocations" + std::to_string(interactionNumber) + "_" + std::to_string(n) + ".mat");
			particleAnsemble->recordAbsorbedParticleLocations(absorbedParticlesFolder + "AbsLocations" + std::to_string(interactionNumber) + "_" + std::to_string(n) + ".mat");
		}
	}
}


void particleDetection()
{
	std::string particleDetectionFolder = "particle_detection/";

	bool particleDetectionFolderCreated = _mkdir(particleDetectionFolder.c_str());

	double sourceLength = 15.0 * phys::cm();
	double sourceWidth = 30.0 * phys::cm();
	double mediumLength = 60.0 * phys::cm();
	double mediumWidth = 80.0 * phys::cm();
	double mediumHeight = 20.0 * phys::cm();

	int numInteractions = 100;

	std::vector<double> energyNodes;
	double firstNode = 0.1;
	double lastNode = 1.3;
	int numNodes = 100;
	for (int iNode = 0; iNode < numNodes; iNode++)
	{
		energyNodes.push_back(firstNode + iNode * (lastNode - firstNode) / (numNodes - 1.0));
	}
	//std::vector<double> energyNodes = { 0.005, 0.008, 0.01, 0.015, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.1, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 1.0 };
	double distanceError = 1.0 * phys::cm();

	std::vector<int> numParticles = {100000};

	for (int n : numParticles)
	{
		Eigen::Vector3d sourceCenter = Eigen::Vector3d(0.0, 0.0, 0.0);
		Shape* sourceShape = new Ellipse(sourceLength, sourceWidth, 0.0);
		Material* sourceMaterial = new Material("Cobalt-60");
		ParticleSource* source = new ParticleSource(sourceCenter, sourceShape, sourceMaterial);

		Eigen::Vector3d mediumCenter = Eigen::Vector3d(0.0, 0.0, mediumHeight / 2.0);
		Shape* mediumShape = new Parallelepiped(mediumLength, mediumWidth, mediumHeight);
		Material* mediumMaterial = new Material("Aluminium");
		Medium* medium = new Medium(mediumCenter, mediumShape, mediumMaterial);

		Eigen::Vector3d detector1Location = Eigen::Vector3d(0.0, 0.0, mediumCenter(3) + mediumHeight / 2.0);
		ParticleDetector* detector1 = new ParticleDetector(detector1Location, energyNodes, distanceError);
		Eigen::Vector3d detector2Location = Eigen::Vector3d(0.0, 0.0, 3.0 * mediumCenter(3) / 2.0);
		ParticleDetector* detector2 = new ParticleDetector(detector2Location, energyNodes, distanceError);
		Eigen::Vector3d detector3Location = Eigen::Vector3d(0.0, 0.0, mediumCenter(3) / 2.0);
		ParticleDetector* detector3 = new ParticleDetector(detector3Location, energyNodes, distanceError);

		Eigen::Vector3d detector4Location = Eigen::Vector3d(mediumLength / 2.0, 0.0, mediumCenter(3));
		ParticleDetector* detector4 = new ParticleDetector(detector4Location, energyNodes, distanceError);
		Eigen::Vector3d detector5Location = Eigen::Vector3d(0.0, mediumWidth / 2.0, mediumCenter(3));
		ParticleDetector* detector5 = new ParticleDetector(detector5Location, energyNodes, distanceError);
		Eigen::Vector3d detector6Location = Eigen::Vector3d(-mediumLength / 2.0, 0.0, mediumCenter(3));
		ParticleDetector* detector6 = new ParticleDetector(detector6Location, energyNodes, distanceError);
		Eigen::Vector3d detector7Location = Eigen::Vector3d(0.0, -mediumWidth / 2.0, mediumCenter(3));
		ParticleDetector* detector7 = new ParticleDetector(detector7Location, energyNodes, distanceError);

		ParticleAnsemble* particleAnsemble = source->getParticleAnsemble();

		for (int i = 0; i < n; i++)
		{
			source->produceParticle();
			medium->checkParticleEnergy(particleAnsemble->getParticle(i));
			if (particleAnsemble->getParticle(i)->isAbsorbed())
			{
				continue;
			}

			for (int interactionNumber = 1; interactionNumber <= numInteractions; interactionNumber++)
			{
				particleAnsemble->getParticle(i)->moveParticle(medium->getMeanFreePath(particleAnsemble->getParticle(i)->getEnergy()));
				medium->checkOutOfBounds(particleAnsemble->getParticle(i));
				if (particleAnsemble->getParticle(i)->isAbsorbed())
				{
					break;
				}
				medium->particleInteraction(particleAnsemble->getParticle(i));
				medium->checkParticleEnergy(particleAnsemble->getParticle(i));
				if (particleAnsemble->getParticle(i)->isAbsorbed())
				{
					break;
				}
				medium->getMediumMaterial()->computeCrossSections(particleAnsemble->getParticle(i)->getEnergy());
				particleAnsemble->getParticle(i)->setVitality(particleAnsemble->getParticle(i)->getVitality() *
					medium->getMediumMaterial()->getScatterMacroCrossSection() / medium->getMediumMaterial()->getLinearMacroCrossSection());
				detector1->computeVirtualContribution(particleAnsemble->getParticle(i), n, medium);
				detector2->computeVirtualContribution(particleAnsemble->getParticle(i), n, medium);
				detector3->computeVirtualContribution(particleAnsemble->getParticle(i), n, medium);
				detector4->computeVirtualContribution(particleAnsemble->getParticle(i), n, medium);
				detector5->computeVirtualContribution(particleAnsemble->getParticle(i), n, medium);
				detector6->computeVirtualContribution(particleAnsemble->getParticle(i), n, medium);
				detector7->computeVirtualContribution(particleAnsemble->getParticle(i), n, medium);
			}
		}
		detector1->recordVirtualContributions(particleDetectionFolder + "VirtualContributions1_" + std::to_string(n) + ".mat");
		detector2->recordVirtualContributions(particleDetectionFolder + "VirtualContributions2_" + std::to_string(n) + ".mat");
		detector3->recordVirtualContributions(particleDetectionFolder + "VirtualContributions3_" + std::to_string(n) + ".mat");
		detector4->recordVirtualContributions(particleDetectionFolder + "VirtualContributions4_" + std::to_string(n) + ".mat");
		detector5->recordVirtualContributions(particleDetectionFolder + "VirtualContributions5_" + std::to_string(n) + ".mat");
		detector6->recordVirtualContributions(particleDetectionFolder + "VirtualContributions6_" + std::to_string(n) + ".mat");
		detector7->recordVirtualContributions(particleDetectionFolder + "VirtualContributions7_" + std::to_string(n) + ".mat");
	}
}