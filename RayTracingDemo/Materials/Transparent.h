#pragma once

#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"

class Transparent : public Phong
{
public:

	//constructors. etc


	virtual RGBColor
		shade(ShadeRec& sr);

private:
	PerfectSpecular* reflective_brdf;
	PerfectTransmitter* specular_btdf;
};