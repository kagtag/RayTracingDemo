#pragma once


#include "Checker2D.h"
#include "RGBColor.h"



class PlaneChecker : public Checker2D {
public:

	PlaneChecker(void);

	PlaneChecker(const PlaneChecker& sc);

	PlaneChecker&
		operator= (const PlaneChecker& rhs);

	virtual PlaneChecker*
		clone(void) const;

	~PlaneChecker(void);

	virtual RGBColor
		get_color(const ShadeRec& sr) const;

	//
	void
		set_size(const float _size);

	void
		set_outline_width(const float _width);

	void
		set_outline_color(RGBColor _color);

private:

	float size;
									
};


// ---------------------------------------------------------------------------------------------------

// inlined access functions

inline void
PlaneChecker::set_size(const float _size)
{
	size = _size;
}

inline void
PlaneChecker::set_outline_width(const float _width)
{
	set_horizontal_line_width(_width);
	set_vertical_line_width(_width);
}

inline void
PlaneChecker::set_outline_color(RGBColor _color)
{
	set_line_color(_color);
}