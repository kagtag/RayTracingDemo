#include "GlossyReflector.h"

GlossyReflector::GlossyReflector(void)
	:Phong(),
	glossy_specular_brdf(new GlossySpecular)
{
}

GlossyReflector::GlossyReflector(const GlossyReflector & m)
	:Phong(m)
{
	if (m.glossy_specular_brdf)
		glossy_specular_brdf = m.glossy_specular_brdf->clone();
	else
		glossy_specular_brdf = NULL;
}

Material*
GlossyReflector::clone(void)const
{
	return (new GlossyReflector(*this));
}

GlossyReflector&
GlossyReflector::operator=(const GlossyReflector& rhs)
{
	if (this == &rhs)
		return (*this);

	if (glossy_specular_brdf)
	{
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}

	if (rhs.glossy_specular_brdf)
		glossy_specular_brdf = rhs.glossy_specular_brdf->clone();

	return *this;
}

GlossyReflector::~GlossyReflector()
{
	if (glossy_specular_brdf)
	{
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}
}

RGBColor
GlossyReflector::area_light_shade(ShadeRec& sr)
{
	RGBColor L(Phong::area_light_shade(sr)); // direct illumination
	Vector3D wo(-sr.ray.d);
	Vector3D wi;
	float pdf;
	RGBColor fr(glossy_specular_brdf->sample_f(sr, wo, wi, pdf));
	Ray reflected_ray(sr.hit_point, wi);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)*
		(sr.normal*wi) / pdf;

	return L;
}