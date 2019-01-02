#pragma once


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// An open cylinder is defined by its extent in the y direction and its radius.
// It is centered on the y axis.
// The classes ConcaveOpenCylinder and ConvexOpenCylinder can inherit from PartCylinder.
// The classes ConcavePartCylinder and ConvexPartCylinder can in turn inherit from these.

#include "GeometricObject.h"

class PartCylinder : public GeometricObject {

public:

	PartCylinder(void);

	PartCylinder(const double bottom, const double top, const double radius,
		const double azimuth_min,
		const double azimuth_max);

	PartCylinder(const PartCylinder& c);

	virtual PartCylinder*
		clone(void) const;

	PartCylinder&
		operator= (const PartCylinder& rhs);

	virtual
		~PartCylinder(void);

	virtual bool
		hit(const Ray& ray, double& t, ShadeRec& sr) const;

	virtual bool
		shadow_hit(const Ray& ray, double& tmin)const;

protected:

	double		y0;				// bottom y value
	double		y1;				// top y value

	double		phi_min;
	double		phi_max;

	double		radius;			// radius
	double		inv_radius;  	// one over the radius	
};

