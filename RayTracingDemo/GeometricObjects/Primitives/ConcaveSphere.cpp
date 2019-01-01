#include "ConcaveSphere.h"

bool
ConcaveSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3D	temp = ray.o - center;
	double 		a = ray.d * ray.d;
	double 		b = 2.0 * temp * ray.d;
	double 		c = temp * temp - radius * radius;
	double 		disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal = - (temp + t * ray.d) / radius; // point inwards

			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal = - (temp + t * ray.d) / radius; //point inwards

			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		}
	}

	return (false);
}