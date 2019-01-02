#pragma once

#include "GeometricObject.h"

class PartTorus : public GeometricObject {
public:

	PartTorus(void);

	PartTorus(const double _a, const double _b,
		const double 	azimuth_min,	// in degrees
		const double 	azimuth_max,	// in degrees
		const double 	polar_min,		// in degrees measured from top
		const double 	polar_max);

	virtual PartTorus*
		clone(void) const;

	PartTorus(const PartTorus& torus);

	virtual
		~PartTorus(void);

	PartTorus&
		operator= (PartTorus& rhs);

	Normal
		compute_normal(const Point3D& p) const;

	virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	bool
		checkRange(const Point3D& hit)const;

protected:

	double 		a;	 	// swept radius 
	double		b;	 	// tube radius
	//BBox		bbox;	// the bounding box

	double 		phi_min;			// minimum azimiuth angle in radians measured counter clockwise from the +ve z axis
	double 		phi_max;			// maximum azimiuth angle in radians measured counter clockwise from the +ve z axis
	double 		theta_min;			// minimum polar angle in radians measured down from the +ve y axis
	double 		theta_max;			// maximum polar angle in radians measured down from the +ve y axis

	double		cos_theta_min;		// stored to avoid repeated calculations
	double		cos_theta_max;		// stored to avoid repeated calculations

};