#pragma once

#include "Texture.h"
#include "LatticeNoise.h"

// standard FBm texture with scaling

class FBmTexture : public Texture
{
public:
	FBmTexture(void);

	FBmTexture(LatticeNoise* n_ptr);

	~FBmTexture(void);

	FBmTexture&
		operator= (const FBmTexture& rhs);

	virtual FBmTexture*
		clone(void) const;

	// constructors, etc

	virtual RGBColor
		get_color(const ShadeRec& sr)const;


	// access functions:

	void
		set_noise(LatticeNoise* n_ptr);

	void
		set_color(const RGBColor& c);

	void 
		set_max_value(const float _max);

	void
		set_min_value(const float _min);


private:

	LatticeNoise* noise_ptr;
	RGBColor color;
	float min_value, max_value; //scaling factors

};

inline void
FBmTexture::set_noise(LatticeNoise* n_ptr)
{
	if (noise_ptr)
	{
		delete noise_ptr;
		noise_ptr = nullptr;
	}
	noise_ptr = n_ptr;
}

inline void
FBmTexture::set_color(const RGBColor& c)
{
	color = c;
}

inline void
FBmTexture::set_max_value(const float _max)
{
	max_value = _max;
}

inline void
FBmTexture::set_min_value(const float _min)
{
	min_value = _min;
}