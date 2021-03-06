#include "SolidCylinder.h"

#include "Disk.h"
#include "OpenCylinder.h"

SolidCylinder::SolidCylinder(void)
	:SolidCylinder(-1.0, 1.0, 1.0)
{
}

SolidCylinder::SolidCylinder(const SolidCylinder& sc)
	: Compound(sc),
	bbox(sc.bbox)
{}


SolidCylinder::~SolidCylinder(void) {}

SolidCylinder&
SolidCylinder::operator= (const SolidCylinder& rhs)
{
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs);

	bbox = rhs.bbox;

	return *this;
}

SolidCylinder*
SolidCylinder::clone(void) const
{
	return new SolidCylinder(*this);
}

SolidCylinder::SolidCylinder(const float bottom,
	const float top,
	const float radius)
	:Compound(),
	bbox(-radius, radius, bottom, top, -radius, radius)
{
	objects.push_back(new Disk(Point3D(0, bottom, 0),
		Normal(0, -1, 0),
		radius));

	objects.push_back(new Disk(Point3D(0, top, 0),
		Normal(0, 1, 0),
		radius));

	objects.push_back(new OpenCylinder(bottom, top, radius));
}

bool 
SolidCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr)const
{
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return false;
}

bool
SolidCylinder::shadow_hit(const Ray& ray, double& tmin)const
{
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return false;
}