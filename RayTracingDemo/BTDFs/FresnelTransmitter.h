#pragma once
#include "BTDF.h"

class FresnelTransmitter : public BTDF
{
public:

	FresnelTransmitter(void);

	FresnelTransmitter(const FresnelTransmitter& pt);

	virtual FresnelTransmitter*
		clone(void)const;

	virtual ~FresnelTransmitter(void);

	FresnelTransmitter&
		operator= (const FresnelTransmitter& rhs);



	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	virtual bool
		tir(const ShadeRec& sr)const;

	float
		fresnel(const ShadeRec& sr)const;

	void
		set_eta_in(const float eta);

	void
		set_eta_out(const float eta);

private:

	// Compute Fresnel transmittance
	float eta_in;
	float eta_out;
};

inline void
FresnelTransmitter::set_eta_in(const float eta)
{
	eta_in = eta;
}

inline void
FresnelTransmitter::set_eta_out(const float eta)
{
	eta_out = eta;
}