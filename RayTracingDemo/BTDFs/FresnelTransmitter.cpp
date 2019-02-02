#include "FresnelTransmitter.h"

FresnelTransmitter::FresnelTransmitter(void)
	:BTDF(),
	eta_in(1.0),
	eta_out(1.0)
{}

FresnelTransmitter::FresnelTransmitter(const FresnelTransmitter& pt)
	:BTDF(pt),
	eta_in(pt.eta_in),
	eta_out(pt.eta_out)
{}


FresnelTransmitter::~FresnelTransmitter(void)
{}

FresnelTransmitter&
FresnelTransmitter::operator= (const FresnelTransmitter& rhs)
{
	if (this == &rhs)
		return (*this);

	eta_in = rhs.eta_in;
	eta_out = rhs.eta_out;

	return (*this);
}

FresnelTransmitter*
FresnelTransmitter::clone(void)const
{
	return new FresnelTransmitter(*this);
}

RGBColor
FresnelTransmitter::sample_f(const ShadeRec& sr,
	const Vector3D& wo,
	Vector3D& wt) const
{
	Normal n(sr.normal);
	float cos_thetai = n*wo;
	float eta = eta_in / eta_out;

	if (cos_thetai < 0.0)
	{
		// hits from transparent object from inside
		cos_thetai = -cos_thetai;
		n = -n;
		eta = 1.0 / eta;
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta*eta);
	float cos_teta2 = sqrt(temp);
	wt = -wo / eta - (cos_teta2 - cos_thetai / eta)*n;

	return white;
	//return (kt / (eta*eta)* white / fabs(sr.normal*wt)) ;
}

bool
FresnelTransmitter::tir(const ShadeRec& sr)const
{
	Vector3D wo(-sr.ray.d);
	float cos_thetai = sr.normal*wo;
	float eta = eta_in / eta_out;

	// hits from transparent object from inside
	if (cos_thetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cos_thetai*cos_thetai) / (eta*eta) < 0.0);
}


float
FresnelTransmitter::fresnel(const ShadeRec& sr)const
{

}