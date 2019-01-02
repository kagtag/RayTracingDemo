#include "Maths.h"	// for SolveQuartic
#include "PartTorus.h"

#include<cmath>


// ---------------------------------------------------------------- default constructor

PartTorus::PartTorus(void)
	: GeometricObject(),
	a(2.0),
	b(0.5),
	phi_min(0.0),			// in radians
	phi_max(TWO_PI),		// in radians	
	theta_min(0.0),			// in radians measured from top
	theta_max(PI),			// in radians measured from top
	cos_theta_min(1.0),
	cos_theta_max(-1.0)
{}

// ---------------------------------------------------------------- constructor

PartTorus::PartTorus(const double _a, const double _b,
	const double 	azimuth_min,	// in degrees
	const double 	azimuth_max,	// in degrees
	const double 	polar_min,		// in degrees measured from top
	const double 	polar_max)
	: GeometricObject(),
	a(_a),
	b(_b),
	phi_min(azimuth_min * PI_ON_180),			// in radians
	phi_max(azimuth_max * PI_ON_180),			// in radians
	theta_min(polar_min * PI_ON_180),			// in radians measured from top
	theta_max(polar_max * PI_ON_180),			// in radians measured from top
	cos_theta_min(cos(theta_min)),
	cos_theta_max(cos(theta_max))
{}

// ---------------------------------------------------------------- clone

PartTorus*
PartTorus::clone(void) const {
	return (new PartTorus(*this));
}


// ---------------------------------------------------------------- copy constructor																																											

PartTorus::PartTorus(const PartTorus& torus)
	: GeometricObject(torus),
	a(torus.a),
	b(torus.b)
{}


// ---------------------------------------------------------------- assignment operator	

PartTorus&
PartTorus::operator = (PartTorus& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	a = rhs.a;
	b = rhs.b;

	return (*this);
}


//------------------------------------------------------------------- destructor 	

PartTorus::~PartTorus(void) {}


//------------------------------------------------------------------ FindNormal
// Find the normal vector at the specified position
// This works because the torus is defined by a single implicit equation 

Normal
PartTorus::compute_normal(const Point3D& p) const {
	Normal normal;
	double param_squared = a * a + b * b;

	double x = p.x;
	double y = p.y;
	double z = p.z;
	double sum_squared = x * x + y * y + z * z;

	normal.x = 4.0 * x * (sum_squared - param_squared);
	normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
	normal.z = 4.0 * z * (sum_squared - param_squared);
	normal.normalize();

	return (normal);
}


//---------------------------------------------------------------- hit 

bool
PartTorus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

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

	// test for hitting from inside

	if (-ray.d * sr.normal < 0.0)
		sr.normal = -sr.normal;

	return (true);
}

bool
PartTorus::checkRange(const Point3D& hit)const
{
	// Check Phi
	double phi = atan2(hit.x, hit.z);
	if (phi < 0.0)
		phi += TWO_PI;

	if (phi < phi_min || phi > phi_max)
		return false;

	//Check Theta
	double theta_rad;

	if (std::abs(hit.x) >= a)
	{
		theta_rad = asin(hit.y);
		if (theta_rad < 0.0)
			theta_rad += TWO_PI;
	}
	else
	{
		theta_rad = asin(hit.y);
		if (theta_rad < 0.0)
			theta_rad += PI;
		else
			theta_rad += (PI / 2);
	}

	if (theta_rad < theta_min || theta_rad > theta_max)
		return false;

	return true;
}