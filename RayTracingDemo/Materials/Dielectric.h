#pragma once
#include "Phong.h"
#include "FresnelReflector.h"
#include "FresnelTransmitter.h"

class Dielectric : public Phong
{
public:

	Dielectric(void);

	Dielectric(const Dielectric& rm);

	Dielectric&
		operator= (const Dielectric& rhs);

	virtual Dielectric*
		clone(void) const;

	~Dielectric(void);

	//constructors. etc

	void
		set_eta_in(float eta);

	void
		set_eta_out(float eta);

	void
		set_cf_in(float cf);

	void
		set_cf_out(float cf);

	virtual RGBColor
		shade(ShadeRec& sr);

private:
	
	RGBColor cf_in;   //interior filter color
	RGBColor cf_out;  //exterior filter color

	FresnelReflector* fresnel_brdf;
	FresnelTransmitter* fresnel_btdf;
};

inline void
Dielectric::set_eta_in(float eta)
{
	fresnel_brdf->set_eta_in(eta);
	fresnel_btdf->set_eta_in(eta);
}

void
Dielectric::set_eta_out(float eta)
{
	fresnel_brdf->set_eta_out(eta);
	fresnel_btdf->set_eta_out(eta);
}

void
Dielectric::set_cf_in(float cf)
{
	cf_in = cf;
}

void
Dielectric::set_cf_out(float cf)
{
	cf_out = cf;
}