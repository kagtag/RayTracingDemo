#pragma once


#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"

#include "World.h"			// you will need this later on for shadows
#include "ShadeRec.h"


class PointLight : public Light {
public:

	PointLight(void);

	PointLight(const PointLight& dl);

	virtual Light*
		clone(void) const;

	PointLight&
		operator= (const PointLight& rhs);

	virtual
		~PointLight(void);

	void
		scale_radiance(const float b);

	void
		set_color(const float c);

	void
		set_color(const RGBColor& c);

	void
		set_color(const float r, const float g, const float b);

	void
		set_location(Vector3D loc);

	void
		set_location(float x, float y, float z);

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual RGBColor
		L(ShadeRec& sr);

private:

	float		ls;
	RGBColor	color;
	Vector3D	location;		// location of the point light
};


// inlined access functions


// ------------------------------------------------------------------------------- scale_radiance

inline void
PointLight::scale_radiance(const float b) {
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}


// ---------------------------------------------------------------------- set_direction

inline void
PointLight::set_location(Vector3D loc) {
	location = loc;
}


// ---------------------------------------------------------------------- set_direction 

inline void
PointLight::set_location(float x, float y, float z) {
	location.x = x; location.y = y; location.z = z;
}


