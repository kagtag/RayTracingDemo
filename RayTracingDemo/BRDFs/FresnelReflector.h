#pragma once


#include "BRDF.h"
#include "Normal.h"

class FresnelReflector : public BRDF
{
public:

	FresnelReflector(void);

	~FresnelReflector(void);

	virtual FresnelReflector*
		clone(void) const;

	void
		set_eta_in(const float eta);

	void
		set_eta_out(const float eta);



	void
		set_kr(const float k);

	void
		set_cr(const RGBColor& c);

	void
		set_cr(const float r, const float g, const float b);

	void
		set_cr(const float c);



	//virtual RGBColor
	//	f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	//virtual RGBColor
	//	rho(const ShadeRec& sr, const Vector3D& wo) const;

	float
		fresnel(const ShadeRec& sr)const;

private:

	float		kr;			// reflection coefficient
	RGBColor 	cr;			// the reflection colour

	// Compute Fresnel reflectance
	float eta_in;
	float eta_out;
};


inline void
FresnelReflector::set_eta_in(const float eta)
{
	eta_in = eta;
}

inline void
FresnelReflector::set_eta_out(const float eta)
{
	eta_out = eta;
}


// -------------------------------------------------------------- set_kr

inline void
FresnelReflector::set_kr(const float k) {
	kr = k;
}


// -------------------------------------------------------------- set_cr

inline void
FresnelReflector::set_cr(const RGBColor& c) {
	cr = c;
}


// ---------------------------------------------------------------- set_cr

inline void
FresnelReflector::set_cr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}


// ---------------------------------------------------------------- set_cr

inline void
FresnelReflector::set_cr(const float c) {
	cr.r = c; cr.g = c; cr.b = c;
}