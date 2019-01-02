
#include "BeveledCylinder.h"
#include "Disk.h"
#include "OpenCylinder.h"
#include "Instance.h"
#include "Torus.h"

BeveledCylinder::BeveledCylinder()
{
	BeveledCylinder(-1.0, 1.0, 2.0, 1.0);
}


BeveledCylinder::BeveledCylinder(const float bottom,
	const float top,
	const float radius,
	const float bevel_radius)
	:Compound(),
	bottom(bottom),
	top(top),
	radius(radius),
	bevel_radius(bevel_radius),
	bbox(-radius, radius, bottom, top, -radius, radius)
{
	objects.push_back(new Disk(Point3D(0,bottom,0),
		Normal(0,-1,0),
		radius - bevel_radius));

	objects.push_back(new Disk(Point3D(0, top, 0),
		Normal(0, 1, 0),
		radius - bevel_radius));

	objects.push_back(new OpenCylinder(bottom + bevel_radius,
		top - bevel_radius,
		radius));

	Instance* bottom_bevel_ptr = new Instance(new Torus
	(radius - bevel_radius, bevel_radius));

	bottom_bevel_ptr->translate(0, bottom + bevel_radius, 0);
	objects.push_back(bottom_bevel_ptr);

	Instance* top_bevel_ptr = new Instance(new Torus(radius - bevel_radius,
		bevel_radius));
	top_bevel_ptr->translate(0, top - bevel_radius, 0);
	objects.push_back(top_bevel_ptr);
}

BeveledCylinder::BeveledCylinder(const BeveledCylinder& bc)
	:Compound(bc),
	bottom(bc.bottom),
	top(bc.top),
	radius(bc.radius),
	bevel_radius(bc.bevel_radius),
	bbox(bc.bbox)
{}

BeveledCylinder*
BeveledCylinder::clone(void) const
{
	return new BeveledCylinder(*this);
}

BeveledCylinder&
BeveledCylinder::operator= (const BeveledCylinder& rhs)
{
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs);

	bottom = rhs.bottom;
	top = rhs.top;
	radius = rhs.radius;
	bevel_radius = rhs.bevel_radius;
	bbox = rhs.bbox;

	return *this;
}

BeveledCylinder::~BeveledCylinder(void) {}

BBox
BeveledCylinder::get_bounding_box(void) {
	return(bbox);
}

// ------------------------------------------------------------------------------ shadow_hit

bool
BeveledCylinder::shadow_hit(const Ray& ray, double& tmin) const {
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}


// ------------------------------------------------------------------------------ hit

bool
BeveledCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}