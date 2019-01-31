#include "LightProbe.h"

// ---------------------------------------------------------------- default constructor

LightProbe::LightProbe(void)
	:map_type(light_probe)
{}


// ---------------------------------------------------------------- copy constructor

LightProbe::LightProbe(const LightProbe& sm)
	:map_type(sm.map_type)
{}


// ---------------------------------------------------------------- assignment operator

LightProbe&
LightProbe::operator= (const LightProbe& rhs) {
	if (this == &rhs)
		return (*this);

	map_type = rhs.map_type;

	return (*this);
}


// ---------------------------------------------------------------- destructor

LightProbe::~LightProbe(void) {}


// ---------------------------------------------------------------- clone

LightProbe*
LightProbe::clone(void) const {
	return (new LightProbe(*this));
}


// ---------------------------------------------------------------- get_texel_coordinates

// Given a hit point on a generic sphere, and the image resolution, this function 
// returns the texel coordinates in the image

void
LightProbe::get_texel_coordinates(const 	Point3D& 	hit_point,
	const 	int 		xres,
	const 	int 		yres,
	int& 		row,
	int& 		column) const 
{
	float x = hit_point.x;
	float y = hit_point.y;
	float z = hit_point.z;

	float d = sqrt(x*x + y*y);
	float sin_beta = y / d;
	float cos_beta = x / d;

	float alpha;

	if (map_type == light_probe)		// the default
		alpha = acos(z);

	if (map_type == panoramic)
		alpha = acos(-z);

	float r = alpha * invPI;
	float u = (1.0 + r * cos_beta) *0.5;
	float v = (1.0 + r * sin_beta)*0.5;
	column = (int)((xres - 1)*u);
	row = (int)((yres - 1)*v);

}