#include "Material.h"

Material::Material(std::string _materialName)
{
	materialName = _materialName;

	if (_materialName == "Cobalt-60" || _materialName == "Co-60")
	{
		quantumEnergy = 1.3 * phys::MeV();
	}
	if (_materialName == "Aluminium" || _materialName == "Al")
	{
		atomicMass = 27.0 * phys::Da();
		atomicNumber = 13;
		density = 2.7 * phys::g() / pow(phys::cm(), 3.0);
		concentration = density / atomicMass;
		particleMinimumEnergy = 0.1 * phys::MeV();
	}
}

double Material::getQuantumEnergy()
{
	return quantumEnergy;
}
double Material::getAtomicMass()
{
	return atomicMass;
}
int Material::getAtomicNumber()
{
	return atomicNumber;
}
double Material::getDensity()
{
	return density;
}
double Material::getConcentration()
{
	return concentration;
}
double Material::getParticleMinimumEnergy()
{
	return particleMinimumEnergy;
}

void Material::computeCrossSections(double energy)
{
	energy /= phys::MeV();
	double scatterMicroCrossSection;
	double photoelAbsorbMicroCrossSection;
	double pairProdMicroCrossSection;

	if (materialName == "Aluminium" || materialName == "Al")
	{
		if (energy <= 0.008)
		{
			scatterMicroCrossSection = 0.187;
			photoelAbsorbMicroCrossSection = 49.1;
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.008 < energy <= 0.01)
		{
			scatterMicroCrossSection = 0.187 + (energy - 0.008) * (0.186 - 0.187) / (0.01 - 0.008);
			photoelAbsorbMicroCrossSection = 49.1 + (energy - 0.008) * (25.7 - 49.1) / (0.01 - 0.008);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.01 < energy <= 0.015)
		{
			scatterMicroCrossSection = 0.186 + (energy - 0.01) * (0.183 - 0.186) / (0.015 - 0.01);
			photoelAbsorbMicroCrossSection = 25.7 + (energy - 0.01) * (7.52 - 25.7) / (0.015 - 0.01);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.015 < energy <= 0.02)
		{
			scatterMicroCrossSection = 0.183 + (energy - 0.015) * (0.179 - 0.183) / (0.02 - 0.015);
			photoelAbsorbMicroCrossSection = 7.52 + (energy - 0.015) * (3.06 - 7.52) / (0.02 - 0.015);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.02 < energy <= 0.03)
		{
			scatterMicroCrossSection = 0.179 + (energy - 0.02) * (0.173 - 0.179) / (0.03 - 0.02);
			photoelAbsorbMicroCrossSection = 3.06 + (energy - 0.02) * (0.826 - 3.06) / (0.03 - 0.02);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.03 < energy <= 0.04)
		{
			scatterMicroCrossSection = 0.173 + (energy - 0.03) * (0.168 - 0.173) / (0.04 - 0.03);
			photoelAbsorbMicroCrossSection = 0.826 + (energy - 0.03) * (0.324 - 0.826) / (0.04 - 0.03);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.04 < energy <= 0.05)
		{
			scatterMicroCrossSection = 0.168 + (energy - 0.04) * (0.163 - 0.168) / (0.05 - 0.04);
			photoelAbsorbMicroCrossSection = 0.324 + (energy - 0.04) * (0.157 - 0.324) / (0.05 - 0.04);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.05 < energy <= 0.06)
		{
			scatterMicroCrossSection = 0.163 + (energy - 0.05) * (0.158 - 0.163) / (0.06 - 0.05);
			photoelAbsorbMicroCrossSection = 0.157 + (energy - 0.05) * (0.0875 - 0.157) / (0.06 - 0.05);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.06 < energy <= 0.08)
		{
			scatterMicroCrossSection = 0.158 + (energy - 0.06) * (0.150 - 0.158) / (0.08 - 0.06);
			photoelAbsorbMicroCrossSection = 0.0875 + (energy - 0.06) * (0.0348 - 0.0875) / (0.08 - 0.06);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.08 < energy <= 0.1)
		{
			scatterMicroCrossSection = 0.150 + (energy - 0.08) * (0.143 - 0.150) / (0.1 - 0.08);
			photoelAbsorbMicroCrossSection = 0.0348 + (energy - 0.08) * (0.0170 - 0.0348) / (0.1 - 0.08);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.1 < energy <= 0.15)
		{
			scatterMicroCrossSection = 0.143 + (energy - 0.1) * (0.129 - 0.143) / (0.15 - 0.1);
			photoelAbsorbMicroCrossSection = 0.0170 + (energy - 0.1) * (0.00469 - 0.0170) / (0.15 - 0.1);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.15 < energy <= 0.2)
		{
			scatterMicroCrossSection = 0.129 + energy * (0.118 - 0.129) / (0.2 - 0.15);
			photoelAbsorbMicroCrossSection = 0.00469 + energy * (0.00193 - 0.00469) / (0.2 - 0.15);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.2 < energy <= 0.3)
		{
			scatterMicroCrossSection = 0.118 + (energy - 0.2) * (0.102 - 0.118) / (0.3 - 0.2);
			photoelAbsorbMicroCrossSection = 0.00193 + (energy - 0.2) * (0.000551 - 0.00193) / (0.3 - 0.2);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.3 < energy <= 0.4)
		{
			scatterMicroCrossSection = 0.102 + (energy - 0.3) * (0.092 - 0.102) / (0.4 - 0.3);
			photoelAbsorbMicroCrossSection = 0.000551 + (energy - 0.3) * (0.000228 - 0.000551) / (0.4 - 0.3);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.4 < energy <= 0.5)
		{
			scatterMicroCrossSection = 0.092 + (energy - 0.4) * (0.0893 - 0.092) / (0.5 - 0.4);
			photoelAbsorbMicroCrossSection = 0.000228 + (energy - 0.4) * (0.000114 - 0.000228) / (0.5 - 0.4);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.5 < energy <= 0.6)
		{
			scatterMicroCrossSection = 0.0893 + (energy - 0.5) * (0.0777 - 0.0893) / (0.6 - 0.5);
			photoelAbsorbMicroCrossSection = 0.000114 + (energy - 0.5) * (0.0000672 - 0.000114) / (0.6 - 0.5);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.6 < energy <= 0.8)
		{
			scatterMicroCrossSection = 0.0777 + (energy - 0.6) * (0.0681 - 0.0777) / (0.8 - 0.6);
			photoelAbsorbMicroCrossSection = 0.0000672 + (energy - 0.6) * (0.0000312 - 0.0000672) / (0.8 - 0.6);
			pairProdMicroCrossSection = 0.0;
		}
		else if (0.8 < energy <= 1.0)
		{
			scatterMicroCrossSection = 0.0681 + (energy - 0.8) * (0.0614 - 0.0681) / (1.0 - 0.8);
			photoelAbsorbMicroCrossSection = 0.0000312 + (energy - 0.8) * (0.0000109 - 0.0000312) / (1.0 - 0.8);
			pairProdMicroCrossSection = 0.0;
		}
		else if (1.0 < energy <= 1.5)
		{
			scatterMicroCrossSection = 0.0614 + (energy - 1.0) * (0.0498 - 0.0614) / (1.5 - 1.0);
			photoelAbsorbMicroCrossSection = 0.0000109 + (energy - 1.0) * (0.000004 - 0.0000109) / (1.5 - 1.0);
			pairProdMicroCrossSection = 0.0 + (energy - 1.0) * (0.000167 - 0.0) / (1.5 - 1.0);
		}
		else
		{
			scatterMicroCrossSection = 0.0498;
			photoelAbsorbMicroCrossSection = 0.000004;
			pairProdMicroCrossSection = 0.000167;
		}
		scatterMicroCrossSection *= pow(phys::cm(), 2.0) / phys::g();
		photoelAbsorbMicroCrossSection *= pow(phys::cm(), 2.0) / phys::g();
		pairProdMicroCrossSection *= pow(phys::cm(), 2.0) / phys::g();
	}
	else
	{
		scatterMicroCrossSection = 1.0 * pow(phys::cm(), 2.0) / phys::g();
		photoelAbsorbMicroCrossSection = 1.0 * pow(phys::cm(), 2.0) / phys::g();
		pairProdMicroCrossSection = 1.0 * pow(phys::cm(), 2.0) / phys::g();
	}
	scatterMacroCrossSection = scatterMicroCrossSection * density;
	photoelAbsorbMacroCrossSection = photoelAbsorbMicroCrossSection * density;
	pairProdMacroCrossSection = pairProdMicroCrossSection * density;
	linearMacroCrossSection = scatterMacroCrossSection + photoelAbsorbMacroCrossSection + pairProdMacroCrossSection;
}

double Material::getScatterMacroCrossSection()
{
	return scatterMacroCrossSection;
}

double Material::getPhotoelAbsorbMacroCrossSection()
{
	return photoelAbsorbMacroCrossSection;
}

double Material::getPairProdMacroCrossSection()
{
	return pairProdMacroCrossSection;
}

double Material::getLinearMacroCrossSection()
{
	return linearMacroCrossSection;
}