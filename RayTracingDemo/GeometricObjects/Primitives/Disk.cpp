#include "Disk.h"



const double Disk::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

Disk::Disk(void)
	: GeometricObject(),
	center(0.0,0.0,0.0),
	n(0, 1, 0),
	r(1.0),
	r_squared(1.0),
	area(4.0),
	inv_area(0.25),
	sampler_ptr(NULL)
{
	compute_uvw();
}


// ----------------------------------------------------------------------  constructor

Disk::Disk(const Point3D& point, const Normal& normal, float radius)
	: GeometricObject(),
	center(point),
	n(normal),
	r(radius),
	r_squared(radius*radius),
	area(PI*r_squared),
	inv_area(1.0 / area),
	sampler_ptr(NULL)
{
	n.normalize();
	compute_uvw(); //
}


// ---------------------------------------------------------------- copy constructor

Disk::Disk(const Disk& disk)
	: GeometricObject(disk),
	center(disk.center),
	n(disk.n),
	r(disk.r),
	r_squared(disk.r_squared),
	area(disk.area),
	inv_area(disk.inv_area),
	u(disk.u),
	v(disk.v),
	w(disk.w)
{
	if (disk.sampler_ptr)
		sampler_ptr = disk.sampler_ptr->clone();
	else  sampler_ptr = NULL;
}


// ---------------------------------------------------------------- clone

Disk*
Disk::clone(void) const {
	return (new Disk(*this));
}


// ---------------------------------------------------------------- assignment operator

Disk&
Disk::operator= (const Disk& rhs) {

	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center = rhs.center;
	n = rhs.n;
	r = rhs.r;
	r_squared = rhs.r_squared;
	area = rhs.area;
	inv_area = rhs.inv_area;
	u = rhs.u;
	v = rhs.v;
	w = rhs.w;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	return (*this);
}


// ---------------------------------------------------------------- destructor

Disk::~Disk(void)
{
	if (sampler_ptr) 
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}



bool Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr)const
{
	// normal ray-plane intersection
	float t = (center - ray.o)* n / (ray.d * n);

	if (t <= kEpsilon)
		return false;

	// Check if the hit point is within the range of disk
	Point3D p = ray.o + t *ray.d;

	if (center.d_squared(p) < r_squared)
	{
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = p;
		return true;
	}
	else
		return false;
}

bool Disk::shadow_hit(const Ray& ray, double& tmin)const
{
	// normal ray-plane intersection
	float t = (center - ray.o)* n / (ray.d * n);

	if (t <= kEpsilon)
		return false;

	// Check if the hit point is within the range of disk
	Point3D p = ray.o + t *ray.d;

	if (center.d_squared(p) < r_squared)
	{
		tmin = t;

		return true;
	}
	else
		return false;
}


//------------------------Area Lighting 
void
Disk::set_sampler(Sampler* sampler)
{
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = sampler;
	sampler_ptr->map_samples_to_unit_disk();
}

void
Disk::compute_uvw(void)
{
	w = (Normal)n;
	u = Vector3D(0.00424, 1, 0.00764) ^ w;
	u.normalize();
	v = u ^ w;
}

Point3D
Disk::sample(void)
{
	Point2D sample_point = sampler_ptr->sample_unit_disk();
	return (center + sample_point.x *u + sample_point.y *v);
}

Normal
Disk::get_normal(const Point3D& p)
{
	return n;
}

float
Disk::pdf(const ShadeRec& sr)
{
	return inv_area;
}