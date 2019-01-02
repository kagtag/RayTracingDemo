#pragma once
#pragma once

#include "GeometricObject.h"
#include "Sampler.h"

class PartAnnulus :public GeometricObject
{
public:

	PartAnnulus(void);   												// default constructor

	PartAnnulus(const Point3D& point, const Normal& normal, 
		const double  r_in, const double r_out,
		const double 	azimuth_min,	// in degrees
		const double 	azimuth_max);			// constructor	

	PartAnnulus(const PartAnnulus& plane); 									// copy constructor

	virtual PartAnnulus* 												// virtual copy constructor
		clone(void) const;

	PartAnnulus& 														// assignment operator
		operator= (const PartAnnulus& rhs);

	virtual														// destructor
		~PartAnnulus(void);

	virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool
		shadow_hit(const Ray & ray, double& tmin) const;

	// Area Lighting
	//virtual void
	//	set_sampler(Sampler* sampler);

	//virtual Point3D
	//	sample(void);

	//virtual Normal
	//	get_normal(const Point3D& p);

	//virtual float
	//	pdf(const ShadeRec& sr);

	//void
	//	compute_uvw(void);

private:

	Point3D 	center;   				// point through which plane passes 
	Normal 		n;					// normal to the plane
	double		r_inner;				// inner radius
	double		r_outer;				// outer radius
	double		r_innerSquared;
	double		r_outerSquared;

	double		phi_min;
	double		phi_max;

	//float			area;			// for PartAnnulus lights
	//float			inv_area;		// for PartAnnulus lights
	//Sampler*		sampler_ptr;	// for PartAnnulus lights, provide sample point for Area lighting, Chap 18

	//Vector3D		u, v, w;

	static const double kEpsilon;   // for shadows and secondary rays
};