#pragma once

#include "GeometricObject.h"

class Disk :public GeometricObject
{
public:

	Disk(void);   												// default constructor

	Disk(const Point3D& point, const Normal& normal);			// constructor	

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

private:

	Point3D 	center;   				// point through which plane passes 
	Normal 		normal;					// normal to the plane
	float		radius;
	float		r_squared;

	static const double kEpsilon;   // for shadows and secondary rays
};