#pragma once
#include "FlatMeshTriangle.h"

class FlatUVMeshTriangle : public FlatMeshTriangle
{
public:
	FlatUVMeshTriangle(void);

	FlatUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);

	virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

};