#include "PartAnnulus.h"



const double PartAnnulus::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

PartAnnulus::PartAnnulus(void)
	: GeometricObject(),
	center(0.0, 0.0, 0.0),
	n(0, 1, 0),
	r_inner(1.0),
	r_outer(2.0),
	r_innerSquared(1.0),
	r_outerSquared(4.0),
	phi_min(0.0),
	phi_max(TWO_PI)
{}


// ----------------------------------------------------------------------  constructor

PartAnnulus::PartAnnulus(const Point3D& point, const Normal& normal,
	const double r_in, 
	const double r_out,
	const double 	azimuth_min,	// in degrees
	const double 	azimuth_max)
	: GeometricObject(),
	center(point),
	n(normal),
	r_inner(r_in),
	r_outer(r_out),
	phi_min(azimuth_min* PI_ON_180),
	phi_max(azimuth_max* PI_ON_180),
	r_innerSquared(r_inner*r_inner),
	r_outerSquared(r_outer*r_outer)
	
{
	n.normalize();
}


// ---------------------------------------------------------------- copy constructor

PartAnnulus::PartAnnulus(const PartAnnulus& pa)
	: GeometricObject(pa),
	center(pa.center),
	n(pa.n),
	r_inner(pa.r_inner),
	r_outer(pa.r_outer),
	phi_min(pa.phi_min),
	phi_max(pa.phi_max),
	r_innerSquared(pa.r_innerSquared),
	r_outerSquared(pa.r_outerSquared)
{}


// ---------------------------------------------------------------- clone

PartAnnulus*
PartAnnulus::clone(void) const {
	return (new PartAnnulus(*this));
}


// ---------------------------------------------------------------- assignment operator

PartAnnulus&
PartAnnulus::operator= (const PartAnnulus& rhs) {

	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center = rhs.center;
	n = rhs.n;
	r_inner = rhs.r_inner;
	r_outer = rhs.r_outer;
	phi_min = rhs.phi_min;
	phi_max = rhs.phi_max;
	r_innerSquared = rhs.r_innerSquared;
	r_outerSquared = rhs.r_outerSquared;

	return (*this);
}


// ---------------------------------------------------------------- destructor

PartAnnulus::~PartAnnulus(void)
{}



bool PartAnnulus::hit(const Ray& ray, double& tmin, ShadeRec& sr)const
{
	// normal ray-plane intersection
	float t = (center - ray.o)* n / (ray.d * n);

	if (t <= kEpsilon)
		return false;

	// Check if the hit point is within the range of annulus
	Point3D p = ray.o + t *ray.d;

	if (center.d_squared(p) < r_outerSquared && center.d_squared(p) > r_innerSquared)
	{
		double phi = atan2(p.x, p.z);
		if (phi < 0.0)
			phi += TWO_PI;

		if (phi >= phi_min && phi <= phi_max)
		{
			tmin = t;
			sr.normal = n;

			// mod : reverse normal when ray hits inside
			if (-ray.d * sr.normal < 0.0)
				sr.normal = -sr.normal;

			sr.local_hit_point = p;
			return true;
		}
	}
	else
		return false;
}

bool PartAnnulus::shadow_hit(const Ray& ray, double& tmin)const
{
	// normal ray-plane intersection
	float t = (center - ray.o)* n / (ray.d * n);

	if (t <= kEpsilon)
		return false;

	// Check if the hit point is within the range of disk
	Point3D p = ray.o + t *ray.d;

	if (center.d_squared(p) < r_outerSquared && center.d_squared(p) > r_innerSquared)
	{
		double phi = atan2(p.x, p.z);
		if (phi < 0.0)
			phi += TWO_PI;

		if (phi >= phi_min && phi <= phi_max)
		{
			tmin = t;

			return true;
		}
	}
	else
		return false;
}


