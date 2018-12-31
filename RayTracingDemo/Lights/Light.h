#ifndef __LIGHT__
#define __LIGHT__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec;


//-------------------------------------------------------------------- class Light

class Light {	
	public:
	
		Light(void);
								
		Light(const Light& ls);			

		Light& 								
		operator= (const Light& rhs); 

		virtual Light* 						
		clone(void) const = 0;
		
		virtual 							
		~Light(void);
		
		// return direction of the incoming light 
		// at a hit point
		virtual Vector3D								
		get_direction(ShadeRec& sr) = 0;				
		
		// returns the incident radiance at a hit point
		virtual RGBColor														
		L(ShadeRec& sr);

		virtual bool
			casts_shadows();

		virtual void
			set_shadows(bool _shadows);

		virtual bool
			in_shadow(const Ray& ray, const ShadeRec& sr)const;

		virtual float
			G(const ShadeRec& sr)const;

		virtual float
			pdf(const ShadeRec& sr)const;

protected:

	// Listing 14.1
	bool shadows;
};

#endif
