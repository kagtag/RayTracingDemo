#pragma once

#include "PartTorus.h"

class ConvexPartTorus : public PartTorus
{
public:
	ConvexPartTorus(const double _a, const double _b,
		const double 	azimuth_min,	// in degrees
		const double 	azimuth_max,	// in degrees
		const double 	polar_min,		// in degrees measured from top
		const double 	polar_max);

	virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
};