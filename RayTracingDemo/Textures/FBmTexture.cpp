#include "FBmTexture.h"

FBmTexture::FBmTexture(void)
	:Texture(),
	color(),
	max_value(1.0),
	min_value(0.0),
	noise_ptr(nullptr)
{}

FBmTexture::FBmTexture(LatticeNoise* n_ptr)
	:Texture(),
	color(),
	max_value(1.0),
	min_value(0.0),
	noise_ptr(n_ptr)
{}

FBmTexture::~FBmTexture(void) 
{
	if (noise_ptr) {
		delete noise_ptr;
		noise_ptr = nullptr;
	}
}

FBmTexture&
FBmTexture::operator= (const FBmTexture& rhs)
{
	if (this == &rhs)
		return (*this);

	Texture::operator=(rhs);

	if (noise_ptr) {
		delete noise_ptr;
		noise_ptr = nullptr;
	}

	if (rhs.noise_ptr)
		noise_ptr = rhs.noise_ptr->clone();

	color = rhs.color;
	max_value = rhs.max_value;
	min_value = rhs.min_value;

	return (*this);
}

FBmTexture*
FBmTexture::clone(void) const
{
	return new FBmTexture(*this);
}

RGBColor
FBmTexture::get_color(const ShadeRec& sr) const
{
	float value = noise_ptr->value_fbm(sr.local_hit_point);
	value = min_value + (max_value - min_value) * value; // mapping from [0,1] to [min_value, max_value]

	if (value <0.0 || value >1.0)
		return RGBColor(1, 0, 0); //detect overflow
	else
		return value*color;
}