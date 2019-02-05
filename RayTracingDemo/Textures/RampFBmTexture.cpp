#include "RampFBmTexture.h"

#include "CubicNoise.h"

RampFBmTexture::RampFBmTexture(void)
	:Texture(),
	a(0.0),
	ramp_ptr(nullptr),
	noise_ptr(nullptr)
{}

RampFBmTexture::RampFBmTexture(Image* n_ptr)
	:Texture(),
	a(0.0),
	ramp_ptr(n_ptr),
	noise_ptr(nullptr)
{}

RampFBmTexture::RampFBmTexture(Image* n_ptr, int num_octaves, float fbm_amount)
	:Texture(),
	a(fbm_amount),
	ramp_ptr(n_ptr),
	noise_ptr(new CubicNoise)
{
	noise_ptr->set_num_octaves(num_octaves);
}



RampFBmTexture::~RampFBmTexture(void)
{
	if (noise_ptr) {
		delete noise_ptr;
		noise_ptr = nullptr;
	}

	//if (ramp_ptr)
	//{
	//	delete ramp_ptr;
	//	ramp_ptr = nullptr;
	//}
}

RampFBmTexture&
RampFBmTexture::operator= (const RampFBmTexture& rhs)
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


	//if (ramp_ptr) {
	//	delete ramp_ptr;
	//	ramp_ptr = NULL;
	//}

	//if (rhs.ramp_ptr)
	//	ramp_ptr = rhs.ramp_ptr->clone();

	// since Image class does not have clone function, just transfer the pointer.
	if (rhs.ramp_ptr)
		ramp_ptr = rhs.ramp_ptr;
	else
		ramp_ptr = NULL;
	//

	a = rhs.a;

	return (*this);
}

RampFBmTexture*
RampFBmTexture::clone(void) const
{
	return new RampFBmTexture(*this);
}

RGBColor
RampFBmTexture::get_color(const ShadeRec& sr)const
{
	//// just reproduces the ramp

	// introduce noise 
	float noise = noise_ptr->value_fbm(sr.local_hit_point);


	//float y = sr.local_hit_point.y; // only need y coordinate
	float y = sr.local_hit_point.y + a*noise; //simulates the turbulent mixing of the layers

	float u = (1.0 + sin(y)) / 2.0; // equation 31.9
	int row = 0;					//use top row of ramp image
	int column = u*(ramp_ptr->get_hres() - 1);

	return (ramp_ptr->get_color(row, column));
}