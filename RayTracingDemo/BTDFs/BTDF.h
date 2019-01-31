#pragma once

#include "RGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"
#include "Sampler.h"

class BTDF {
public:

	BTDF(void);

	BTDF(const BTDF& brdf);

	virtual BTDF*
		clone(void)const = 0;

	BTDF&
		operator= (const BTDF& rhs);

	virtual
		~BTDF(void);


	virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt, float& pdf) const;

	virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;


	// check for total internal reflection
	virtual bool
		tir(const ShadeRec& sr)const = 0;



protected:

	float  kt;	    // transmission coefficient
	float ior;		// index of refraction
};
