// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "PartCylinder.h"

// This uses the value of kEpsilon defined in Constants.h

// ---------------------------------------------------------------- default constructor

PartCylinder::PartCylinder(void)
	: GeometricObject(),
	y0(-1.0),
	y1(1.0),
	radius(1.0),
	inv_radius(1.0),
	phi_min(0.0),
	phi_max(TWO_PI)
{}

// ---------------------------------------------------------------- constructor

PartCylinder::PartCylinder(const double bottom, const double top, const double r,
	const double azimuth_min,
	const double azimuth_max)
	: GeometricObject(),
	y0(bottom),
	y1(top),
	radius(r),
	inv_radius(1.0 / radius),
	phi_min(azimuth_min*PI_ON_180),
	phi_max(azimuth_max*PI_ON_180)
{}


// ---------------------------------------------------------------- copy constructor

PartCylinder::PartCylinder(const PartCylinder& c)
	: GeometricObject(c),
	y0(c.y0),
	y1(c.y1),
	radius(c.radius),
	inv_radius(c.inv_radius),
	phi_min(c.phi_min),
	phi_max(c.phi_max)
{}


// ---------------------------------------------------------------- clone

PartCylinder*
PartCylinder::clone(void) const {
	return (new PartCylinder(*this));
}


// ---------------------------------------------------------------- assignment operator

PartCylinder&
PartCylinder::operator= (const PartCylinder& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	y0 = rhs.y0;
	y1 = rhs.y1;
	radius = rhs.radius;
	inv_radius = rhs.inv_radius;
	phi_min = rhs.phi_min;
	phi_max = rhs.phi_max;

	return (*this);
}


// ---------------------------------------------------------------- destructor

PartCylinder::~PartCylinder(void) {}


// ----------------------------------------------------------------------------- hit
// The code reverses the normal when the ray hits the inside surface, allows both
// sides to be shaded, but completely messes up transparency.

bool
PartCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c;


	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > y0 && yhit < y1) {

				Vector3D hit = ray.o + t * ray.d;

				double phi = atan2(hit.x, hit.z);
				if (phi < 0.0)
					phi += TWO_PI;

				if (phi >= phi_min && phi <= phi_max)
				{
					tmin = t;
					sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);

					// test for hitting from inside

					if (-ray.d * sr.normal < 0.0)
						sr.normal = -sr.normal;

					sr.local_hit_point = ray.o + tmin * ray.d;

					return (true);
				}

			}
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > y0 && yhit < y1) {

				Vector3D hit = ray.o + t * ray.d;

				double phi = atan2(hit.x, hit.z);
				if (phi < 0.0)
					phi += TWO_PI;

				if (phi >= phi_min && phi <= phi_max)
				{
					tmin = t;
					sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);

					// test for hitting inside surface

					if (-ray.d * sr.normal < 0.0)
						sr.normal = -sr.normal;

					sr.local_hit_point = ray.o + tmin * ray.d;

					return (true);
				}

			}
		}
	}

	return (false);
}

bool
PartCylinder::shadow_hit(const Ray& ray, double& tmin)const
{
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c;


	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > y0 && yhit < y1) {

				Vector3D hit = ray.o + t * ray.d;

				double phi = atan2(hit.x, hit.z);
				if (phi < 0.0)
					phi += TWO_PI;

				if (phi >= phi_min && phi <= phi_max)
				{
					tmin = t;

					return (true);
				}
			}
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > y0 && yhit < y1) {

				Vector3D hit = ray.o + t * ray.d;

				double phi = atan2(hit.x, hit.z);
				if (phi < 0.0)
					phi += TWO_PI;

				if (phi >= phi_min && phi <= phi_max)
				{
					tmin = t;

					return (true);
				}
			}
		}
	}

	return (false);
}

