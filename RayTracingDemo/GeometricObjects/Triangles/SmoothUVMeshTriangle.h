#pragma once
#include "SmoothMeshTriangle.h"

class SmoothUVMeshTriangle : public SmoothMeshTriangle
{

	virtual	bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

};