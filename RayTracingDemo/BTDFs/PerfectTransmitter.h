#pragma once

#include "BTDF.h"

class PerfectTransmitter : public BTDF
{
public:
	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;


	virtual bool
		tir(const ShadeRec& sr)const;

};