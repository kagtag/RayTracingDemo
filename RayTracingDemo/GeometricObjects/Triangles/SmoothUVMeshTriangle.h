#pragma once
#include "SmoothMeshTriangle.h"

class SmoothUVMeshTriangle : public SmoothMeshTriangle
{
public:
	SmoothUVMeshTriangle();

	SmoothUVMeshTriangle(Mesh* mesh, int v0, int v1, int v2);

	virtual	bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

};