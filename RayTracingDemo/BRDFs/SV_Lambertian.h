#pragma once

#include "BRDF.h"
#include "Texture.h"

class SV_Lambertian : public BRDF
{
public:

	SV_Lambertian(void);

	SV_Lambertian(const SV_Lambertian& lamb);

	SV_Lambertian&
		operator= (const SV_Lambertian& rhs);

	virtual
		~SV_Lambertian(void);

	virtual SV_Lambertian*
		clone(void) const;

	// constructors, etc

	virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo)const;

	virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, /*const*/ Vector3D& wi)const;

	void
		set_ka(const float ka);

	void
		set_kd(const float kd);

	void
		set_cd(const Texture* _cd);


private:

	float kd;
	Texture* cd;
};

// -------------------------------------------------------------- set_ka

inline void
SV_Lambertian::set_ka(const float k) {
	kd = k;
}



// -------------------------------------------------------------- set_kd

inline void
SV_Lambertian::set_kd(const float k) {
	kd = k;
}

void
SV_Lambertian::set_cd(const Texture* _cd)
{
	cd = _cd;
}