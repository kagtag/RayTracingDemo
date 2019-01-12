#pragma once

#include "Phong.h"

class GlossyReflector : public Phong
{
public:

	GlossyReflector(void);

	GlossyReflector(const GlossyReflector& m);

	virtual Material*
		clone(void) const;

	GlossyReflector&
		operator= (const GlossyReflector& rhs);

	~GlossyReflector(void);


	void set_samples(const int num_samples, const float exp);

	void set_kr(const float k);

	void set_cr(const float r, const float g, const float b);

	void set_exponent(const float exp);

	virtual RGBColor
		area_light_shade(ShadeRec& sr);

private:

	GlossySpecular* glossy_specular_brdf;
};



inline void
GlossyReflector::set_samples(const int num_samples, const float exponent)
{
	glossy_specular_brdf->set_samples(num_samples, exponent);
}

inline void
GlossyReflector::set_kr(const float k)
{
	glossy_specular_brdf->set_ks(k);
}

inline void
GlossyReflector::set_exponent(const float exp)
{
	glossy_specular_brdf->set_exp(exp);
}

inline void
GlossyReflector::set_cr(const float r, const float g, const float b)
{
	glossy_specular_brdf->set_cs(r, g, b);
}