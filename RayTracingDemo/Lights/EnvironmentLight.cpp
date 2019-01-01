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

float
EnvironmentLight::pdf(const ShadeRec& sr)const
{
	//wi already precomputed in get_direction
	return wi * sr.normal *invPI;
}

RGBColor
EnvironmentLight::L(ShadeRec& sr)
{
	return material_ptr->get_Le(sr);
}

EnvironmentLight::EnvironmentLight()
	:Light(),
	sampler_ptr(NULL),
	material_ptr(NULL),
	u(1, 0, 0),
	v(0, 1, 0),
	w(0, 0, 1),
	wi(1, 0, 0)
{
	
}

EnvironmentLight::EnvironmentLight(const EnvironmentLight & el)
	:Light(el),
	u(el.u),
	v(el.v),
	w(el.w),
	wi(el.wi)
{
	if (el.sampler_ptr)
	{
		sampler_ptr = el.sampler_ptr->clone();
	}
	else
	{
		sampler_ptr = NULL;
	}

	if (el.material_ptr)
	{
		material_ptr = el.material_ptr->clone();
	}
	else
	{
		material_ptr = NULL;
	}

}

Light * EnvironmentLight::clone(void) const
{
	return new EnvironmentLight(*this);
}

EnvironmentLight::~EnvironmentLight(void)
{
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (material_ptr)
	{
		//delete material_ptr;
		material_ptr = NULL;
	}
}

EnvironmentLight & EnvironmentLight::operator=(const EnvironmentLight & rhs)
{
	if (this == &rhs)
		return *this;

	Light::operator=(rhs);

	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
	{
		sampler_ptr = rhs.sampler_ptr->clone();
	}

	if (material_ptr) {
		//delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();
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

void EnvironmentLight::set_material(Material * mPtr)
{

	if (material_ptr) {
		//delete material_ptr;
		material_ptr = NULL;
	}

	if (mPtr)
		material_ptr = mPtr->clone();
}
