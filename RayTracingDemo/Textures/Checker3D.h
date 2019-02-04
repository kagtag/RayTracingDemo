#pragma once

#include "Texture.h"

class Checker3D : public Texture
{
public:
	Checker3D(void);

	Checker3D(const Checker3D& texture);


	virtual Checker3D*
		clone(void) const;

	virtual
		~Checker3D(void);

	Checker3D&
		operator= (const Checker3D& rhs);

	// constructors, etc

	// return an RGBColor given a ray-object hit point. 
	virtual RGBColor
		get_color(const ShadeRec& sr) const;


	//

	void
		set_color1(const float r, const float g, const float b);

	void
		set_color1(const float c);

	void
		set_color1(const RGBColor& c);

	void
		set_color2(const float r, const float g, const float b);

	void
		set_color2(const float c);

	void
		set_color2(const RGBColor& c);

	void
		set_size(const float _size);

private:
	float		size;						// checker size in all directions
	RGBColor	color1;						// checker color 1
	RGBColor	color2;						// checker color 2

};

inline void
Checker3D::set_color1(const float r, const float g, const float b) {
	color1.r = r; color1.g = g; color1.b = b;
}

inline void
Checker3D::set_color1(const float c) {
	color1.r = c; color1.g = c; color1.b = c;
}

inline void
Checker3D::set_color1(const RGBColor& c) {
	color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void
Checker3D::set_color2(const float r, const float g, const float b) {
	color2.r = r; color2.g = g; color2.b = b;
}

inline void
Checker3D::set_color2(const float c) {
	color2.r = c; color2.g = c; color2.b = c;
}

inline void
Checker3D::set_color2(const RGBColor& c) {
	color2.r = c.r; color2.g = c.g; color2.b = c.b;
}

inline void
Checker3D::set_size(const float _size)
{
	size = _size;
}