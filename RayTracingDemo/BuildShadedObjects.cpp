//void
//World::build(void) {
//	int num_samples = 1;
//
//	// view plane  
//
//	vp.set_hres(400);
//	vp.set_vres(400);
//	vp.set_pixel_size(0.5);
//	vp.set_samples(num_samples);
//
//	// the ambient light here is the same as the default set in the World
//	// constructor, and can therefore be left out
//
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(1.0);
//	set_ambient_light(ambient_ptr);
//
//	background_color = black;			// default color - this can be left out
//
//	tracer_ptr = new RayCast(this);
//
//
//	// camera
//
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(0, 0, 500);
//	pinhole_ptr->set_lookat(0.0);
//	pinhole_ptr->set_view_distance(600.0);
//	pinhole_ptr->compute_uvw();
//	set_camera(pinhole_ptr);
//
//
//	// light
//
//	Directional* light_ptr1 = new Directional;
//	light_ptr1->set_direction(100, 100, 200);
//	light_ptr1->scale_radiance(3.0);
//	add_light(light_ptr1);
//
//
//	// colors
//
//	RGBColor yellow(1, 1, 0);										// yellow
//	RGBColor brown(0.71, 0.40, 0.16);								// brown
//	RGBColor darkGreen(0.0, 0.41, 0.41);							// darkGreen
//	RGBColor orange(1, 0.75, 0);									// orange
//	RGBColor green(0, 0.6, 0.3);									// green
//	RGBColor lightGreen(0.65, 1, 0.30);								// light green
//	RGBColor darkYellow(0.61, 0.61, 0);								// dark yellow
//	RGBColor lightPurple(0.65, 0.3, 1);								// light purple
//	RGBColor darkPurple(0.5, 0, 1);									// dark purple
//	RGBColor grey(0.25);											// grey
//
//
//																	// Matte material reflection coefficients - common to all materials
//
//	float ka = 0.25;
//	float kd = 0.75;
//}