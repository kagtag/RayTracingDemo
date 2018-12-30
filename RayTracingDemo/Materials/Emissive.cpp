#include "Emissive.h"

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