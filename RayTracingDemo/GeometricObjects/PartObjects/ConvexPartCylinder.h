#pragma once

#include "PartCylinder.h"

class ConvexPartCylinder : public PartCylinder
{

public:

	ConvexPartCylinder(const double bottom, const double top, const double radius,
		const double azimuth_min,
		const double azimuth_max);

	virtual bool
		hit(const Ray& ray, double& t, ShadeRec& sr) const;
};