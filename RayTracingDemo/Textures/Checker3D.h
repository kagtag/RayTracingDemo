#pragma once

#include "Texture.h"

class Checker3D : public Texture
{
public:
	Checker3D(void);

	Checker3D(const Checker3D& texture);


	virtual Checker3D*
		clone(void) const;


	// constructors, etc

	// return an RGBColor given a ray-object hit point. 
	virtual RGBColor
		get_color(const ShadeRec& sr) const;

private:
	float		size;						// checker size in all directions
	RGBColor	color1;						// checker color 1
	RGBColor	color2;						// checker color 2

};