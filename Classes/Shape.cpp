#include "Shape.h"

Shape::Shape()
{
}


Ellipse::Ellipse(double _a, double _b, double _z)
{
	dimensions = 2;
	a = _a;
	b = _b;
	p = a / b;
	z = _z;
}

Eigen::Vector3d Ellipse::getRandInternalPoint()
{
	double a0 = a * pow((double(std::rand()) / double(RAND_MAX)), 0.5);
	double b0 = a0 / p;
	double phi0 = 2 * M_PI * (double(std::rand()) / double(RAND_MAX));

	Eigen::Vector3d randPoint = Eigen::Vector3d(a0 * cos(phi0), b0 * sin(phi0), z);

	return randPoint;
}

bool Ellipse::inside(Eigen::Vector3d point)
{
	return true;
}


Parallelepiped::Parallelepiped(double _a, double _b, double _c)
{
	dimensions = 3;
	a = _a;
	b = _b;
	c = _c;
}

Eigen::Vector3d Parallelepiped::getRandInternalPoint()
{
	return Eigen::Vector3d(0.0, 0.0, 0.0);
}

bool Parallelepiped::inside(Eigen::Vector3d point)
{
	if (point.x() < -a / 2.0 || point.x() > a / 2.0 || point.y() < -b / 2.0 || point.y() > b / 2.0 || point.z() < -c / 2.0 || point.z() > c / 2.0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
