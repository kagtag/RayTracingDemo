#pragma once
#include "Sphere.h"

class ConcaveSphere : public Sphere
{
public:
	virtual bool
		hit(const Ray& ray, double& t, ShadeRec& s) const;

	/*virtual bool
		shadow_hit(const Ray & ray, double& tmin) const;*/
};