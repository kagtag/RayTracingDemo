#include "Emissive.h"

Emissive::Emissive(void)
	:Material(),
	ls(1.0),
	ce(white)
{}

Emissive::Emissive(const Emissive& e)
	: Material(e),
	ls(e.ls),
	ce(e.ce)
{}

Material*
Emissive::clone(void) const {
	return (new Emissive(*this));
}

Emissive&
Emissive::operator=(const Emissive& rhs)
{
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);

	ls = rhs.ls;
	ce = rhs.ce;

	return (*this);
}

Emissive::~Emissive(void)
{}

RGBColor
Emissive::area_light_shade(ShadeRec& sr)
{
	if (-sr.normal * sr.ray.d > 0.0)
		return ls*ce;
	else
		return black;
}

RGBColor
Emissive::shade(ShadeRec& sr)
{
	// allows us to use the emissive material with other tracers
	// like RayCast and thereby to render emissive objs in scenes
	// whiout shading on them.
	if (-sr.normal * sr.ray.d > 0.0)
		return ls*ce;
	else
		return black;
}

RGBColor
Emissive::get_Le(ShadeRec& sr)const
{
	return ls*ce;
}