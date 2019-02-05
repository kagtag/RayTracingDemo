#include "WrappedFBmTexture.h"
#include <math.h>

WrappedFBmTexture::WrappedFBmTexture(void)
	:Texture(),
	color(),
	expansion_number(1.0),
	noise_ptr(nullptr)
{}

WrappedFBmTexture::WrappedFBmTexture(LatticeNoise* n_ptr)
	:Texture(),
	color(),
	expansion_number(1.0),
	noise_ptr(n_ptr)
{}

WrappedFBmTexture::~WrappedFBmTexture(void)
{
	if (noise_ptr) {
		delete noise_ptr;
		noise_ptr = nullptr;
	}
}

WrappedFBmTexture&
WrappedFBmTexture::operator= (const WrappedFBmTexture& rhs)
{
	if (this == &rhs)
		return (*this);

	Texture::operator=(rhs);

	if (noise_ptr) {
		delete noise_ptr;
		noise_ptr = NULL;
	}

	if (rhs.noise_ptr)
		noise_ptr = rhs.noise_ptr->clone();

	color = rhs.color;
	expansion_number = rhs.expansion_number;

	return (*this);
}

WrappedFBmTexture*
WrappedFBmTexture::clone(void) const
{
	return new WrappedFBmTexture(*this);
}

RGBColor
WrappedFBmTexture::get_color(const ShadeRec& sr)const
{
	float noise = expansion_number * noise_ptr->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise); // wrap values back into the range [0,1]

	return value*color;

}