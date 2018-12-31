#include"EnvironmentLight.h"

Vector3D
EnvironmentLight::get_direction(ShadeRec& sr)
{
	w = sr.normal;
	v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	u = v^w;
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x *u + sp.y *v + sp.z*w;

	return wi;
}

RGBColor
EnvironmentLight::L(ShadeRec& sr)
{
	return material_ptr->get_Le(sr);
}

void
EnvironmentLight::set_sampler(Sampler* s_ptr)
{
	// same as AmbientOccluder
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

bool
EnvironmentLight::in_shadow(const Ray& ray, const ShadeRec& sr)const
{
	// test if a shadow ray is blocked by an object

	// same as AmbientOccluder

	double t;
	int num_objects = sr.w.objects.size();

	for (int j = 0; j < num_objects; ++j)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t))
			return true;
	}

	return false;
}