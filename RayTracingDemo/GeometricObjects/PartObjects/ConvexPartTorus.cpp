#include "ConvexPartTorus.h"
#include "Maths.h"

ConvexPartTorus::ConvexPartTorus(const double _a, const double _b,
	const double 	azimuth_min,	// in degrees
	const double 	azimuth_max,	// in degrees
	const double 	polar_min,		// in degrees measured from top
	const double 	polar_max)
	:PartTorus(_a, _b, azimuth_min, azimuth_max,
		polar_min, polar_max)
{}

bool
ConvexPartTorus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;

	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation

						// define the coefficients of the quartic equation

	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd = 4.0 * a * a;

	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4

															// find roots of the quartic equation

	int num_real_roots = SolveQuartic(coeffs, roots);

	bool	intersected = false;
	double 	t = kHugeValue;

	if (num_real_roots == 0)  // ray misses the torus
		return(false);

	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted

	for (int j = 0; j < num_real_roots; j++)
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t)
				t = roots[j];
		}

	if (!intersected)
		return (false);

	// check theta and phi range
	Point3D hit = ray.o + t * ray.d;

	if (!checkRange(hit))
		return false;

	tmin = t;
	sr.local_hit_point = ray.o + t * ray.d;
	sr.normal = compute_normal(sr.local_hit_point);

	//// test for hitting from inside

	//if (-ray.d * sr.normal < 0.0)
	//	sr.normal = -sr.normal;

	return (true);
}