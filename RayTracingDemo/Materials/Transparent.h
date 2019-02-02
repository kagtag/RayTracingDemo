#pragma once

#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"

// Simple Transparency 
// Chapter 28

class Transparent : public Phong
{
public:

	//constructors. etc
	Transparent(void);

	Transparent(const Transparent& rm);

	Transparent&
		operator= (const Transparent& rhs);

	Transparent*
		clone(void) const override;

	virtual ~Transparent(void);

	RGBColor
		shade(ShadeRec& sr) override;

	void
		set_ior(const float _ior);

	void
		set_kr(const float _kr);
	
	void
		set_kt(const float _kt);

private:
	PerfectSpecular* reflective_brdf;
	PerfectTransmitter* specular_btdf;
};

inline void
Transparent::set_ior(const float _ior)
{
	specular_btdf->set_ior(_ior);
}

inline void
Transparent::set_kr(const float _kr)
{
	reflective_brdf->set_kr(_kr);
}

inline void
Transparent::set_kt(const float _kt)
{
	specular_btdf->set_kt(_kt);
}

