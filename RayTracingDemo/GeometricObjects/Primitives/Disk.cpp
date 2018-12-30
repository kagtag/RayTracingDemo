#include "Disk.h"

const double Disk::kEpsilon = 0.001;

bool Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr)const
{
	// normal ray-plane intersection
	float t = (center - ray.o)* normal / (ray.d * normal);

	if (t <= kEpsilon)
		return false;

	// Check if the hit point is within the range of disk
	Point3D p = ray.o + t *ray.d;

	if (center.d_squared(p) < r_squared)
	{
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = p;
		return true;
	}
	else
		return false;
}