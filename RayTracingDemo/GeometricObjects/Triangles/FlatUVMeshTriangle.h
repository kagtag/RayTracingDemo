#pragma once
#include "FlatMeshTriangle.h"

class FlatUVMeshTriangle : public FlatMeshTriangle
{

	virtual	bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

};