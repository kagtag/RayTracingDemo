#include "ConstantColor.h"
#include "Constants.h"


ConstantColor::ConstantColor(void)
	:Texture(),
	color(red)
{

}

ConstantColor::ConstantColor(const ConstantColor& texture)
	:Texture(texture),
	color(texture.color)
{}



ConstantColor*
ConstantColor::clone(void) const
{
	return new ConstantColor(*this);
}


ConstantColor::~ConstantColor(void) {}

ConstantColor&
ConstantColor::operator= (const ConstantColor& rhs)
{
	if (this == &rhs)
		return (*this);

	//
	color = rhs.color;

	return (*this);
}

RGBColor 
ConstantColor::get_color(const ShadeRec & sr) const
{
	return color;
}
