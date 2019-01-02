#pragma once

#include "CompoundObjects\Compound.h"

class BeveledCylinder : public Compound {
public:

	BeveledCylinder(void);

	BeveledCylinder(const float bottom,
		const float top,
		const float radius,
		const float bevel_radius);

	BeveledCylinder(const BeveledCylinder& bb);

	virtual BeveledCylinder*
		clone(void) const;

	virtual BeveledCylinder&
		operator= (const BeveledCylinder& rhs);

	virtual
		~BeveledCylinder(void);

	virtual BBox
		get_bounding_box(void);

	virtual bool
		shadow_hit(const Ray& ray, double& tmin) const;

	virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

private:
	float bottom;
	float top;
	float radius;
	float bevel_radius;
	
	BBox		bbox;	// bounding box
};