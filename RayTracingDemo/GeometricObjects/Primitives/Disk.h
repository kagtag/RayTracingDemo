#pragma once

#include "GeometricObject.h"
#include "Sampler.h"

class Disk :public GeometricObject
{
public:

	Disk(void);   												// default constructor

	Disk(const Point3D& point, const Normal& normal, float radius);			// constructor	

	Disk(const Disk& plane); 									// copy constructor

	virtual Disk* 												// virtual copy constructor
		clone(void) const;

	Disk& 														// assignment operator
		operator= (const Disk& rhs);

	virtual														// destructor
		~Disk(void);

	virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool
		shadow_hit(const Ray & ray, double& tmin) const;

	// Area Lighting
	virtual void
		set_sampler(Sampler* sampler);

	virtual Point3D
		sample(void);

	virtual Normal
		get_normal(const Point3D& p);

	virtual float
		pdf(const ShadeRec& sr);

	void
		compute_uvw(void);

private:

	Point3D 	center;   				// point through which plane passes 
	Normal 		n;					// normal to the plane
	float		r;					// Disk radius
	float		r_squared;

	float			area;			// for Disk lights
	float			inv_area;		// for Disk lights
	Sampler*		sampler_ptr;	// for Disk lights, provide sample point for Area lighting, Chap 18

	Vector3D		u, v, w;

	static const double kEpsilon;   // for shadows and secondary rays
};