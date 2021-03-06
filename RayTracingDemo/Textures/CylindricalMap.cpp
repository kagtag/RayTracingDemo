#include "CylindricalMap.h"

// ---------------------------------------------------------------- default constructor

CylindricalMap::CylindricalMap(void) {}


// ---------------------------------------------------------------- copy constructor

CylindricalMap::CylindricalMap(const CylindricalMap& sm) {}


// ---------------------------------------------------------------- assignment operator

CylindricalMap&
CylindricalMap::operator= (const CylindricalMap& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------- destructor

CylindricalMap::~CylindricalMap(void) {}


// ---------------------------------------------------------------- clone

CylindricalMap*
CylindricalMap::clone(void) const {
	return (new CylindricalMap(*this));
}


// ---------------------------------------------------------------- get_texel_coordinates

// Given a hit point on a generic sphere, and the image resolution, this function 
// returns the texel coordinates in the image

void
CylindricalMap::get_texel_coordinates(const 	Point3D& 	local_hit_point,
	const 	int 		xres,
	const 	int 		yres,
	int& 		row,
	int& 		column) const {


	float phi = atan2(local_hit_point.x, local_hit_point.z);
	if (phi < 0.0)
		phi += TWO_PI;

	// according to section 29.3.3
	float u = phi * invTWO_PI;
	float v = (local_hit_point.y + 1) / 2;

	// finally, map u and v to the texel coordinates

	column = (int)((xres - 1) * u);   	// column is across
	row = (int)((yres - 1) * v);    	// row is up
}