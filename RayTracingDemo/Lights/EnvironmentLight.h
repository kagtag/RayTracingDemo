#pragma once

#include "Light.h"
#include "Sampler.h"
#include "Material.h"

// not define the G function for environment Light
// and forces the C++ compiler to use the G function
// defined in the Light base class

class EnvironmentLight : public Light
{
public:

	EnvironmentLight();

	EnvironmentLight(const EnvironmentLight& el);

	virtual Light*
		clone(void) const;

	virtual
		~EnvironmentLight(void);

	EnvironmentLight&
		operator= (const EnvironmentLight& rhs);

	void set_sampler(Sampler* sampler);

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual RGBColor
		L(ShadeRec& sr);

	virtual bool
		in_shadow(const Ray& ray, const ShadeRec& sr)const;


	virtual float
		pdf(const ShadeRec& sr)const;

	void
		set_material(Material* mPtr);

private:

	Sampler* sampler_ptr;
	Material* material_ptr;
	Vector3D u, v, w;
	Vector3D wi;

};