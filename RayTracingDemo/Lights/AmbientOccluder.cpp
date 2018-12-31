#include "AmbientOccluder.h"
#include "MultiJittered.h"

AmbientOccluder::AmbientOccluder(void)
	:Light(),
	ls(1.0),
	color(1.0),
	min_amount(0.0),
	sampler_ptr(NULL)
{}

AmbientOccluder::AmbientOccluder(const AmbientOccluder& ao)
	:Light(ao),
	ls(ao.ls),
	color(ao.color),
	min_amount(ao.min_amount)
{
	if (ao.sampler_ptr)
		sampler_ptr = ao.sampler_ptr->clone();
	else
		sampler_ptr = NULL;
}

Light*
AmbientOccluder::clone(void)const
{
	return (new AmbientOccluder(*this));
}

AmbientOccluder&
AmbientOccluder::operator=(const AmbientOccluder& rhs)
{
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	ls = rhs.ls;
	color = rhs.color;
	min_amount = rhs.min_amount;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	return *this;
}

AmbientOccluder::~AmbientOccluder(void) 
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

////

void 
AmbientOccluder::set_sampler(Sampler* s_ptr)
{
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

void 
AmbientOccluder::set_samples(const int num_samples)
{
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(1); //Sample the whole hemisphere
}

Vector3D 
AmbientOccluder::get_direction(ShadeRec& sr)
{
	// direction of each shadow ray

	Point3D sp = sampler_ptr->sample_hemisphere();
	return (sp.x*u + sp.y *v + sp.z *w);
}

bool
AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr)const
{
	// test if a shadow ray is blocked by an object

	// same as that for a directional light

	double t;
	int num_objects = sr.w.objects.size();

	for (int j = 0; j < num_objects; ++j)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t))
			return true;
	}

	return false;
}

RGBColor
AmbientOccluder::L(ShadeRec& sr)
{
	w = sr.normal;
	
	//jitter up vector in case normal is vertical
	v = w^Vector3D(0.0072, 1.0, 0.0034);
	v.normalize();
	u = v^w; //set up u, v, w so the following get_direction() can use them

	Ray shadow_ray;
	shadow_ray.o = sr.hit_point;
	shadow_ray.d = get_direction(sr);

	if (in_shadow(shadow_ray, sr))
		return min_amount*ls*color;
	else
		return ls*color;
}

