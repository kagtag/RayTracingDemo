#pragma once

// base class for all 2D checkers

#include "Texture.h"
#include "RGBColor.h"

#include <math.h>

class Checker2D : public Texture {
public:

	Checker2D(void);

	Checker2D(const Checker2D& sc);

	Checker2D&
		operator= (const Checker2D& rhs);

	virtual Checker2D*
		clone(void) const = 0;

	virtual ~Checker2D(void);

	virtual RGBColor
		get_color(const ShadeRec& sr) const = 0;

	void
		set_horizontal_line_width(const float width);

	void
		set_vertical_line_width(const float width);

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
		set_line_color(const float r, const float g, const float b);

	void
		set_line_color(const float c);

	void
		set_line_color(const RGBColor& c);

protected:


	float		horizontal_line_width;		// width of the horizontal lines as a fraction of the checker width
	float		vertical_line_width;		// width of the vertical lines as a fraction of the checker width
	RGBColor	color1;						// checker color 1
	RGBColor	color2;						// checker color 2
	RGBColor	line_color;					// the line color									
};


// ---------------------------------------------------------------------------------------------------

// inlined access functions

inline void
Checker2D::set_horizontal_line_width(const float width) {
	horizontal_line_width = width;
}

inline void
Checker2D::set_vertical_line_width(const float width) {
	vertical_line_width = width;
}

inline void
Checker2D::set_color1(const float r, const float g, const float b) {
	color1.r = r; color1.g = g; color1.b = b;
}

inline void
Checker2D::set_color1(const float c) {
	color1.r = c; color1.g = c; color1.b = c;
}

inline void
Checker2D::set_color1(const RGBColor& c) {
	color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void
Checker2D::set_color2(const float r, const float g, const float b) {
	color2.r = r; color2.g = g; color2.b = b;
}

inline void
Checker2D::set_color2(const float c) {
	color2.r = c; color2.g = c; color2.b = c;
}

inline void
Checker2D::set_color2(const RGBColor& c) {
	color2.r = c.r; color2.g = c.g; color2.b = c.b;
}

inline void
Checker2D::set_line_color(const float r, const float g, const float b) {
	line_color.r = r; line_color.g = g; line_color.b = b;
}

inline void
Checker2D::set_line_color(const float c) {
	line_color.r = c; line_color.g = c; line_color.b = c;
}

inline void
Checker2D::set_line_color(const RGBColor& c) {
	line_color.r = c.r; line_color.g = c.g; line_color.b = c.b;
}
