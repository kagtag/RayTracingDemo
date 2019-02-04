#ifndef __SPHERE_CHECKER__
#define __SPHERE_CHECKER__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Checker2D.h"
#include "RGBColor.h"

// For checkers that are approximately square at the "equator" (polar angle theta = 90 degrees), there should be
// twice as many horizontal_checkers as vertical_checkers

//-----------------------------------------------------------------------------------class SphereChecker

class SphereChecker: public Checker2D {		
	public:
	
		SphereChecker(void);										
		
		SphereChecker(const SphereChecker& sc);
		
		SphereChecker& 												
		operator= (const SphereChecker& rhs);		

		virtual SphereChecker*							
		clone(void) const;				

		~SphereChecker(void);						
		
		virtual RGBColor																				
		get_color(const ShadeRec& sr) const;
				
		void													
		set_num_horizontal_checkers(const int num_horizontal);
		
		void													
		set_num_vertical_checkers(const int num_vertical);
		
		
		
	private:
	
		int			num_horizontal_checkers;	// number of checkers in the horizontal (azithum) direction
		int			num_vertical_checkers;		// number of checkers in the vertical (polar) direction									
};


// ---------------------------------------------------------------------------------------------------

// inlined access functions

inline void													
SphereChecker::set_num_horizontal_checkers(const int num_horizontal) {
	num_horizontal_checkers = num_horizontal;
}

inline void													
SphereChecker::set_num_vertical_checkers(const int num_vertical) {
	num_vertical_checkers = num_vertical;
}


#endif