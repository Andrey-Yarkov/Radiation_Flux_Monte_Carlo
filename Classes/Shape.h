#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "Eigen/Eigen"

class Shape
{
public:
	Shape();
	
	virtual Eigen::Vector3d getRandInternalPoint() = 0;
	virtual bool inside(Eigen::Vector3d point) = 0;

protected:
	int dimensions;
};

class Ellipse : public Shape
{
public:
	Ellipse(double _a, double _b, double _z);

	Eigen::Vector3d getRandInternalPoint();
	bool inside(Eigen::Vector3d point);

private:
	double a, b;
	double p;
	double z;
};


class Parallelepiped : public Shape
{
public:
	Parallelepiped(double _a, double _b, double _c);

	Eigen::Vector3d getRandInternalPoint();
	bool inside(Eigen::Vector3d point);

private:
	double a, b, c;
};