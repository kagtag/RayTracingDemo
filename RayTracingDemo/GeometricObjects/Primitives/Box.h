#pragma once

#include"GeometricObject.h"

class Box : public GeometricObject
{
public:
	double x0, x1, y0, y1, z0, z1;

	Box(void);

	Box(const double x0, const double x1,
		const double y0, const double y1,
		const double z0, const double z1);

	Box(const Point3D p0, const Point3D p1);

	Box(const Box& bbox);

	virtual Box*
		clone(void) const;


	Box&
		operator= (const Box& rhs);

	virtual
	~Box(void);


	virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	Normal
		get_normal(const int face_hit) const;
};