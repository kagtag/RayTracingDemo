#include "Checker3D.h"

#include<math.h>
#include "Constants.h"

Checker3D::Checker3D(void)
	:Texture(),
	size(1.0),
	color1(white),
	color2(white)
{}

Checker3D::Checker3D(const Checker3D& texture)
	: Texture(texture),
	size(texture.size),
	color1(texture.color1),
	color2(texture.color2)
{}


Checker3D*
Checker3D::clone(void) const
{
	return new Checker3D(*this);
}

Checker3D::~Checker3D(void)
{
}

Checker3D&
Checker3D::operator= (const Checker3D& rhs)
{
	if (this == &rhs)
		return (*this);

	Texture::operator=(rhs);

	size = rhs.size;
	color1 = rhs.color1;
	color2 = rhs.color2;

	return *this;
}


RGBColor
Checker3D::get_color(const ShadeRec& sr) const
{
	float eps = -0.000187453738;	// small random number
	float x = sr.local_hit_point.x + eps;
	float y = sr.local_hit_point.y + eps;
	float z = sr.local_hit_point.z + eps;

	if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)
		return color1;
	else
		return color2;
}