


// <math.h> is # included in Texture.h 

#include "Maths.h"
#include "Checker2D.h"



// ---------------------------------------------------------------- default constructor

Checker2D::Checker2D(void)
	: Texture(),
	horizontal_line_width(0.0),
	vertical_line_width(0.0),
	color1(white),
	color2(0.5),
	line_color(black)
{}


// ---------------------------------------------------------------- copy constructor

Checker2D::Checker2D(const Checker2D& sc)
	: Texture(sc),
	horizontal_line_width(sc.horizontal_line_width),
	vertical_line_width(sc.vertical_line_width),
	color1(sc.color1),
	color2(sc.color2),
	line_color(sc.line_color)
{}


// ---------------------------------------------------------------- assignment operator

Checker2D&
Checker2D::operator= (const Checker2D& rhs)
{
	if (this == &rhs)
		return (*this);

	Texture::operator=(rhs);

	horizontal_line_width = rhs.horizontal_line_width;
	vertical_line_width = rhs.vertical_line_width;
	color1 = rhs.color1;
	color2 = rhs.color2;
	line_color = rhs.line_color;

	return (*this);
}



// ---------------------------------------------------------------- destructor

Checker2D::~Checker2D(void) {}








