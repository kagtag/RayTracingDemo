#pragma once

#include"Compound.h"

class SolidCylinder : public Compound
{
public:
	SolidCylinder(void);

	SolidCylinder(const float bottom, const float top, const float radius);

	SolidCylinder(const SolidCylinder& sc);

	
	~SolidCylinder(void);

	SolidCylinder&
		operator= (const SolidCylinder& c);

	virtual SolidCylinder*
		clone(void) const;

	bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr)const override;

	bool
		shadow_hit(const Ray& ray, double& tmin)const override;

	// TODO
	//void set_top_material(Material* mat_ptr);
	//void set_bottom_material(Material* mat_ptr);
	//void set_wall_material(Material* mat_ptr);

private:
	BBox		bbox;	// the bounding box

	// TODO
	//int top_index;		//index for the top disk in the objects vector
	//int bottom_index;
	//int wall_index;
};