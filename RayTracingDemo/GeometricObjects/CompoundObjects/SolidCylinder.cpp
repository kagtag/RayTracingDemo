#include "SolidCylinder.h"

#include "Disk.h"
#include "OpenCylinder.h"

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
SolidCylinder::hit(const Ray& ray, double tmin, ShadeRec& sr)const
{
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return false;
}