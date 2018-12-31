#include "PointLight.h"

// ---------------------------------------------------------------------- default constructor

PointLight::PointLight(void)
	: Light(),
	ls(1.0),
	color(1.0),
	location(0, 1, 0)
{}


// ---------------------------------------------------------------------- dopy constructor

PointLight::PointLight(const PointLight& dl)
	: Light(dl),
	ls(dl.ls),
	color(dl.color),
	location(dl.location)
{}


// ---------------------------------------------------------------------- clone

Light*
PointLight::clone(void) const {
	return (new PointLight(*this));
}


// ---------------------------------------------------------------------- assignment operator

PointLight&
PointLight::operator= (const PointLight& rhs)
{
	if (this == &rhs)
		return (*this);

	Light::operator= (rhs);

	ls = rhs.ls;
	color = rhs.color;
	location = rhs.location;

	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

PointLight::~PointLight(void) {}


// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

Vector3D
PointLight::get_direction(ShadeRec& sr) {
	return (location - sr.hit_point).hat();
}

// ------------------------------------------------------------------------------  L

RGBColor
PointLight::L(ShadeRec& s) {
	return (ls * color); // no distance attenuation
}

bool 
PointLight::in_shadow(const Ray& ray, const ShadeRec& sr)const
{
	double t;
	int num_objects = sr.w.objects.size();
	float d = location.distance(ray.o);

	for (int j = 0; j < num_objects; ++j)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return true;
	}

	return false;
}