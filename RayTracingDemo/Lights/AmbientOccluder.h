#pragma once

#include "World.h"

class AmbientOccluder : public Light
{
public:
	AmbientOccluder(void);


	AmbientOccluder(const AmbientOccluder& dl);

	virtual Light*
		clone(void) const;

	AmbientOccluder&
		operator= (const AmbientOccluder& rhs);

	virtual
		~AmbientOccluder(void);

	////
	void
		scale_radiance(const float b);

	void
		set_color(const float c);

	void
		set_color(const RGBColor& c);

	void
		set_color(const float r, const float g, const float b);

	void
		set_min_amount(const float min_a);

	////
	void set_sampler(Sampler* s_ptr);

	void set_samples(const int num_samples); // construct a default sampler object with the specified number of samples

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual bool
		in_shadow(const Ray& ray, const ShadeRec& sr)const;

	virtual RGBColor
		L(ShadeRec& sr);

private:

	float		ls;
	RGBColor	color;

	Vector3D u, v, w;
	Sampler* sampler_ptr;
	RGBColor min_amount;


};

inline void
AmbientOccluder::scale_radiance(const float b) {
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline void 
AmbientOccluder::set_min_amount(const float min_a)
{
	min_amount = min_a;
}