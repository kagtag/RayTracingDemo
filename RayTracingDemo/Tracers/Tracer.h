// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#ifndef __TRACER__
#define __TRACER__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"

class World;

class Tracer {
	public:
	
		Tracer(void);									
		
		Tracer(World* _world_ptr);						
				
		virtual											
		~Tracer(void);									

		virtual RGBColor			// only overridden in the tracers SingleSphere and MultipleObjects
		trace_ray(const Ray& ray) const;

		virtual RGBColor	
		trace_ray(const Ray ray, const int depth) const;

		//// color filtering with the Dielectric material in Chapter 28
		virtual RGBColor
		trace_ray(const Ray ray, float& tmin, const int depth) const;
				
	protected:
	
		World* world_ptr;
};

#endif

