#pragma once

#include "ShadeRec.h"

class Texture
{
public:
	Texture(void);

	Texture(const Texture& texture);



	virtual Texture*
		clone(void) const = 0;

	virtual
		~Texture(void);

	// constructors, etc

	// return an RGBColor given a ray-object hit point. 
	virtual RGBColor
		get_color(const ShadeRec& sr) const = 0;

protected:

	Texture&
		operator= (const Texture& rhs);

};