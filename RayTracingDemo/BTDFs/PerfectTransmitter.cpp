#include "PerfectTransmitter.h"


RGBColor
PerfectTransmitter::sample_f(const ShadeRec& sr, 
	const Vector3D& wo,
	Vector3D& wt) const
{
	Normal n(sr.normal);
	float cos_thetai = n*wo;
	float eta = ior;

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

	return (kt / (eta*eta)*white / fabs(sr.normal*wt));
}

bool
PerfectTransmitter::tir(const ShadeRec& sr)const
{
	Vector3D wo(-sr.ray.d);
	float cos_thetai = sr.normal*wo;
	float eta = ior;

	// hits from transparent object from inside
	if (cos_thetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cos_thetai*cos_thetai) / (eta*eta) < 0.0);
}