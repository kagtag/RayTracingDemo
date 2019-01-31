#include"FresnelReflector.h"

FresnelReflector::FresnelReflector(void)
	:BRDF(),
	kr(0.0),
	cr(1.0),
	eta_in(1.0),
	eta_out(1.0)
{}

FresnelReflector::~FresnelReflector(void) {}

FresnelReflector*
FresnelReflector::clone(void) const
{
	return (new FresnelReflector(*this));
}

// computes the reflectance
float 
FresnelReflector::fresnel(const ShadeRec& sr)const
{
	Normal normal(sr.normal);
	float ndotd = -normal*sr.ray.d;
	float eta;

	if (ndotd < 0.0)
	{
		normal = -normal; // ray hits inside surface
		eta = eta_out / eta_in;
	}
	else
	{
		eta = eta_in / eta_out;
	}

	
	float cos_thetai = -normal * sr.ray.d;
	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta*eta);
	float cos_thetat = 
		sqrt(1.0 - (1.0 - cos_thetai*cos_thetai) / (eta*eta));
	
	// Equation 28.1
	float r_parallel = (eta*cos_thetai - cos_thetat) /
		(eta*cos_thetai + cos_thetat);
	
	// Equation 28.2
	float r_perpendicular = (cos_thetai - eta*cos_thetat) /
		(cos_thetai + eta*cos_thetat);

	// Equation 28.3 Fresnel reflectance
	float kr = 0.5*(r_parallel*r_parallel +
		r_perpendicular*r_perpendicular);

	return kr;
}


///////

RGBColor
FresnelReflector::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo;
	return (kr * cr / fabs(sr.normal * wi)); // why is this fabs? // kr would be a Fresnel term in a Fresnel reflector
}											 // for transparency when ray hits inside surface?, if so it should go in Chapter 24


// ---------------------------------------------------------- sample_f
// this version of sample_f is used with path tracing
// it returns ndotwi in the pdf

RGBColor
FresnelReflector::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo;
	pdf = fabs(sr.normal * wi);
	return (kr * cr);
}
