#pragma once

#include "Texture.h"
#include "LatticeNoise.h"

// used for produce wrapped colors

class WrappedFBmTexture : public Texture
{

public:
	WrappedFBmTexture(void);

	WrappedFBmTexture(LatticeNoise* n_ptr);

	~WrappedFBmTexture(void);

	WrappedFBmTexture&
		operator= (const WrappedFBmTexture& rhs);

	virtual WrappedFBmTexture*
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
		set_color(const float r, const float g, const float b);

	void
		set_expansion_number(const float _exp);


	// actually useless
	void
		set_max_value(const float _max);

	void
		set_min_value(const float _min);

private:

	LatticeNoise* noise_ptr;
	RGBColor color;

	float expansion_number;
};


inline void
WrappedFBmTexture::set_noise(LatticeNoise* n_ptr)
{
	if (noise_ptr)
	{
		delete noise_ptr;
		noise_ptr = nullptr;
	}
	noise_ptr = n_ptr;
}

inline void
WrappedFBmTexture::set_color(const RGBColor& c)
{
	color = c;
}

inline void
WrappedFBmTexture::set_color(const float r, const float g, const float b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

inline void
WrappedFBmTexture::set_expansion_number(const float _exp)
{
	expansion_number = _exp;
}

inline void
WrappedFBmTexture::set_max_value(const float _max)
{
}

inline void
WrappedFBmTexture::set_min_value(const float _min)
{
}