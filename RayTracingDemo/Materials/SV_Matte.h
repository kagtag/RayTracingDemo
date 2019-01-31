#pragma once
#include "Material.h"
#include "SV_Lambertian.h"

class SV_Matte : public Material
{
public:

	SV_Matte(void);

	SV_Matte(const SV_Matte& m);

	virtual Material*
		clone(void) const;

	SV_Matte&
		operator= (const SV_Matte& rhs);

	~SV_Matte(void);

	// constructors, etc

	void
		set_cd(const Texture* t_ptr);

	virtual RGBColor
		shade(ShadeRec& sr);

	//
	
	void
		set_ka(const float k);

	void
		set_kd(const float k);


private:

	SV_Lambertian* ambient_brdf;
	SV_Lambertian* diffuse_brdf;

};

inline void
SV_Matte::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


inline void
SV_Matte::set_ka(const float k)
{
	ambient_brdf->set_ka(k);
}

// ---------------------------------------------------------------- set_kd

inline void
SV_Matte::set_kd(const float kd) {
	diffuse_brdf->set_kd(kd);
}


inline void
SV_Matte::set_cd(const Texture* t_ptr)
{
	ambient_brdf->set_cd(t_ptr);
	diffuse_brdf->set_cd(t_ptr->clone());
}