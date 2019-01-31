#include "ConstantColor.h"

RGBColor 
ConstantColor::get_color(const ShadeRec & sr) const
{
	return color;
}
