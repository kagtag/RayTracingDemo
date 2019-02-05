#pragma once
#include "Texture.h"
#include "Image.h"
#include "LatticeNoise.h"


class RampFBmTexture : public Texture
{
public:
	RampFBmTexture(void);

	RampFBmTexture(Image* n_ptr);

	RampFBmTexture(Image* n_ptr, int num_octaves, float fbm_amount);

	~RampFBmTexture(void);

	RampFBmTexture&
		operator= (const RampFBmTexture& rhs);

	virtual RampFBmTexture*
		clone(void) const;

	// constructors, etc

	virtual RGBColor
		get_color(const ShadeRec& sr)const;

	// access functions:

	void
		set_noise(LatticeNoise* n_ptr);

	void
		set_perturbation(const float pertub);

	void 
		set_image(Image* img_ptr);

private:
	Image* ramp_ptr;  // stores the ramp image
	LatticeNoise* noise_ptr; //supplies the value_fBm noise function
	float a;		// the amount of fBm

};

inline void
RampFBmTexture::set_image(Image* img_ptr)
{
	if (ramp_ptr)
	{
		delete ramp_ptr;
		ramp_ptr = nullptr;
	}
	ramp_ptr = img_ptr;
}


inline void
RampFBmTexture::set_noise(LatticeNoise* n_ptr)
{
	if (noise_ptr)
	{
		delete noise_ptr;
		noise_ptr = nullptr;
	}
	noise_ptr = n_ptr;
}

inline void
RampFBmTexture::set_perturbation(const float pertub)
{
	a = pertub;
}