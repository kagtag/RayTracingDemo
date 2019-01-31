#include "Constants.h"
#include "BTDF.h"

// ---------------------------------------------------------- default constructor

BTDF::BTDF(void)
	:kt(0.0),
	ior(1.0)
{}


// ---------------------------------------------------------- copy constructor

BTDF::BTDF(const BTDF& btdf) 
	:kt(btdf.kt),
	ior(btdf.ior)
{

}



// --------------------------------------------------------------- assignment operator

BTDF&
BTDF::operator= (const BTDF& rhs) {
	if (this == &rhs)
		return (*this);

	kt = rhs.kt;
	ior = rhs.ior;

	return (*this);
}


// ---------------------------------------------------------- destructor

BTDF::~BTDF(void) 
{}

// ------------------------------------------------------------------------ f

RGBColor
BTDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}


// ------------------------------------------------------------------------ sample_f

RGBColor
BTDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {
	return (black);
}


// ------------------------------------------------------------------------ sample_f

RGBColor
BTDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
	return (black);
}


// ------------------------------------------------------------------------ rho	

RGBColor
BTDF::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}