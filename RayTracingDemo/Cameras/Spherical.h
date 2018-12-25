#pragma once
#pragma once

#include "World.h"

//// The aspect ratio must be lambda_max/psi_max,
//// otherwise the image will be distorted
class Spherical : public Camera {
public:

	// constructors, etc

	Vector3D
		ray_direction(const Point2D& pp,
			const int 	hres,
			const int 	vres,
			const float s) const;

	virtual void
		render_scene(World& w);

private:

	float	lambda_max;
	float	psi_max;	// in degrees
};