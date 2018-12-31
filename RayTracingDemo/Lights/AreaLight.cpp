// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "AreaLight.h"

// ---------------------------------------------------------------- default constructor
	
AreaLight::AreaLight(World& _world)
	: 	Light(),
		object_ptr(NULL),
		material_ptr(NULL),
		world(_world)
{}	


// ---------------------------------------------------------------- copy constructor 
	
AreaLight::AreaLight(const AreaLight& al)
	: 	Light(al),
		world(al.world)
	{
	if (al.object_ptr)
	{
		set_object(al.object_ptr->clone());

		world.add_object(object_ptr); //world.objects is responsible for the management of object_ptr
	}
	else
	{
		object_ptr = NULL;
		material_ptr = NULL;
	}

}


// ---------------------------------------------------------------- clone

Light* 
AreaLight::clone(void) const 
{
	return (new AreaLight(*this));
}					


// ---------------------------------------------------------------- destructor
 								
AreaLight::~AreaLight(void) {
	if (object_ptr) {
		//delete object_ptr; // this will be deleted by the final delete_objects(), then the GeometricObjects destructor will delete the material_ptr
		object_ptr = NULL;
	}
	
	if (material_ptr) {
		//delete material_ptr;
		material_ptr = NULL;
	}
}


// --------------------------------------------------------------- assignment operator

AreaLight&														
AreaLight::operator= (const AreaLight& rhs) {
	if (this == &rhs)
		return (*this);
		
	Light::operator=(rhs);
	
	world = rhs.world;

	if (object_ptr) {

		world.remove_object(object_ptr);// remove from the objects vector, otherwise it will be deleted twice

		delete object_ptr;
		object_ptr = NULL;
	}

	if (rhs.object_ptr)
	{
		set_object(rhs.object_ptr->clone());//set object_ptr as well as material_ptr
		world.add_object(object_ptr); // add the new object to World::objects vector
	}

	// GeometricObjects copy constructor will handle material_ptr clone

	//if (material_ptr) {
	//	delete material_ptr;
	//	material_ptr = NULL;
	//}

	//if (rhs.material_ptr)
	//	material_ptr = rhs.material_ptr->clone();

	return (*this);
}


// --------------------------------------------------------------- get_direction

Vector3D								
AreaLight::get_direction(ShadeRec& sr) {
	// compute and store data members used later
	sample_point = object_ptr->sample();    // used in the G function
	light_normal = object_ptr->get_normal(sample_point); 
	wi = sample_point - sr.hit_point;  		// used in the G function
	wi.normalize();
	
	return (wi);
}


// --------------------------------------------------------------- L

RGBColor								
AreaLight::L(ShadeRec& sr) {
	float ndotd = -light_normal * wi; 
	
	if (ndotd > 0.0)		
		return (material_ptr->get_Le(sr)); 
	else
		return (black);
}


// ---------------------------------------------------------------- in_shadow	

bool									
AreaLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	double t;
	int num_objects = sr.w.objects.size();


	float ts = (sample_point - ray.o) * ray.d; // ???? why use *?
	

	for (int j = 0; j < num_objects; j++)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < ts)
			return (true);
	}
	return (false);     
}


// ---------------------------------------------------------------- G
// G is part of the geometric factor

float
AreaLight::G(const ShadeRec& sr) const {
	float ndotd = -light_normal * wi;
	float d2 	= sample_point.d_squared(sr.hit_point);
		
	return (ndotd / d2);
}


// ---------------------------------------------------------------- pdf

float									
AreaLight::pdf(const ShadeRec& sr) const {
	return (object_ptr->pdf(sr));
}

