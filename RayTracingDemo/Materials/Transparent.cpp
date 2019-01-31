
#include "Transparent.h"

RGBColor
Transparent::shade(ShadeRec& sr)
{
	RGBColor L(Phong::shade(sr));

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi); // computes wi
	Ray reflected_ray(sr.hit_point, wi);

	if (specular_btdf->tir(sr))
	{
		L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
		// acts like setting kr = 1.0
	}
	else
	{
		Vector3D wt;
		RGBColor ft = specular_btdf->sample_f(sr, wo, wt); // computes wt
		Ray transmitted_ray(sr.hit_point, wt);

		L += fr* sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)
			*fabs(sr.normal * wi);

		L += fr * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1)
			*fabs(sr.normal * wt);
	}
	
	return L;
}