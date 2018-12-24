#pragma once

#include "World.h"

class FishEye : public Camera {
public:

	// constructors, etc

	Vector3D
		ray_direction(const Point2D& pp,
			const int 	hres,
			const int 	vres,
			const float s,
			float& 		r_squared) const;

	virtual void
		render_scene(World& w);

private:

	float	psi_max;	// in degrees
};