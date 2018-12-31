// this file contains the definition of the World class


#include "World.h"
#include "Constants.h"

#if !defined(GENERATE_PPM_DIRECTLY)
#include "wxraytracer.h"
#endif

// geometric objects

#include "Plane.h"
#include "Sphere.h"
#include "Box.h"
#include "Rectangle.h"

// tracers

#include "SingleSphere.h"
#include "MultipleObjects.h"
#include "RayCast.h"

// cameras

#include "Pinhole.h"

// lights

#include "Directional.h"
#include "PointLight.h"

#include "AreaLight.h"

// materials

#include "Matte.h"
#include "Phong.h"
#include "Emissive.h"

// utilities

#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"

#include "Point2D.h"

#include "MultiJittered.h"
#include "Regular.h"

#include "AmbientOccluder.h"



#include "AreaLighting.h"

//////////////////////////////////////////////
// build functions
///////////////////////////////////////////////
#include "..\BuildShadedObjects.cpp"

ofstream World::myfile{};
int World::s_chapter_number = 18;
int World::s_file_number = 4;

int World::s_file_quality = 0;
string World::s_file_sample = "";


void
World::build(void) {
	
	int num_samples = 1;   		// for Figure 18.4(a)
	//	int num_samples = 100;   	// for Figure 18.4(b) & (c)
	s_file_quality = num_samples;//

	Sampler* sampler_ptr = new MultiJittered(num_samples);
	s_file_sample = "MultiJittered";

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_sampler(sampler_ptr);

	background_color = RGBColor(0.5);

	tracer_ptr = new AreaLighting(this);

	Pinhole* camera = new Pinhole;
	camera->set_eye(-20, 10, 20);
	camera->set_lookat(0, 2, 0);
	camera->set_view_distance(1080);
	camera->compute_uvw();
	set_camera(camera);


	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(40.0);
	emissive_ptr->set_ce(white);


	// define a rectangle for the rectangular light

	float width = 4.0;				// for Figure 18.4(a) & (b)
	float height = 4.0;
	//	float width = 2.0;				// for Figure 18.4(c)
	//	float height = 2.0;
	Point3D center(0.0, 7.0, -7.0);	// center of each area light (rectangular, disk, and spherical)
	Point3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
	Vector3D a(width, 0.0, 0.0);
	Vector3D b(0.0, height, 0.0);
	Normal normal(0, 0, 1);

	

	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(sampler_ptr);
	rectangle_ptr->set_shadows(false);
	add_object(rectangle_ptr);  //

	
	AreaLight* area_light_ptr = new AreaLight(*this);
	area_light_ptr->set_object(rectangle_ptr);
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);


	// Four axis aligned boxes

	float box_width = 1.0; 		// x dimension
	float box_depth = 1.0; 		// z dimension
	float box_height = 4.5; 		// y dimension
	float gap = 3.0;

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.4, 0.7, 0.4);     // green

	Box* box_ptr0 = new Box(Point3D(-1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth),
		Point3D(-1.5 * gap - box_width, box_height, 0.5 * box_depth));
	box_ptr0->set_material(matte_ptr1);
	add_object(box_ptr0);

	Box* box_ptr1 = new Box(Point3D(-0.5 * gap - box_width, 0.0, -0.5 * box_depth),
		Point3D(-0.5 * gap, box_height, 0.5 * box_depth));
	box_ptr1->set_material(matte_ptr1->clone());
	add_object(box_ptr1);

	Box* box_ptr2 = new Box(Point3D(0.5 * gap, 0.0, -0.5 * box_depth),
		Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->set_material(matte_ptr1->clone());
	add_object(box_ptr2);

	Box* box_ptr3 = new Box(Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth),
		Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->set_material(matte_ptr1->clone());
	add_object(box_ptr3);


	// ground plane

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.1);
	matte_ptr2->set_kd(0.90);
	matte_ptr2->set_cd(white);

	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);



}
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

// -------------------------------------------------------------------- default constructor

// tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
// ambient_ptr is set to a default ambient light because this will do for most scenes
// camera_ptr is set to NULL because the build functions will always have to construct a camera
// and set its parameters

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		ambient_ptr(new Ambient),
		camera_ptr(NULL)
{}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
	
		
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
			
		
	if (camera_ptr) {
		delete camera_ptr;
		camera_ptr = NULL;
	}
	
	delete_objects();	
	delete_lights();				
}



//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis

// responsible for rendering the scene
void 												
World::render_scene(void) const {

	RGBColor	pixel_color;	 	
	//int 		hres 	= vp.hres;
	//int 		vres 	= vp.vres;
	//float		s		= vp.s;

	float		zw = 100.0;				// hardwired in

	
#if defined	GENERATE_PPM_DIRECTLY

	char filename[512];
	memset(filename, '\0', 512);
	snprintf(filename, 512, 
		"D:\\GameProject\\RaytracingResult\\Chapter%d\\pic%d.ppm", s_chapter_number, s_file_number);
	
	myfile.open(filename,ios::out);

	myfile << "P3\n" << vp.hres << " " << vp.vres << "\n255\n";
	for (int r = vp.vres - 1; r >= 0; r--)		// up
		for (int c = 0; c < vp.hres; c++)	// across
		 {	
			////regular_sample(pixel_color, zw, r, c);
			//random_sample(pixel_color, zw, r, c);

			display_pixel(r, c, pixel_color);
		}

	myfile.close();
#endif
}  


void World::regular_sample(RGBColor& pixel_color, float zw, int r, int c, bool jittered) const
{
	//Common Setup

	pixel_color = black;

	Ray			ray;
	ray.d = Vector3D(0, 0, -1);
	int 		hres = vp.hres;
	int 		vres = vp.vres;
	float		s = vp.s;


	int n = (int)sqrt((float)vp.num_samples);// Regular Sampling
	Point2D pp; // sample point on a pixel

	//Regular sampling n-by-n per pixel
	for (int p = 0; p < n; p++)
	{
		for (int q = 0; q < n; q++)
		{
			pp.x = s*(c - 0.5*hres + (q + (jittered ? rand_float() : 0.5)) / n);
			pp.y = s*(r - 0.5*vres + (p + (jittered ? rand_float() : 0.5)) / n);
			ray.o = Point3D(pp.x, pp.y, zw);
			pixel_color += tracer_ptr->trace_ray(ray);
		}
	}

	pixel_color /= vp.num_samples;
}

void World::jittered_sample(RGBColor& pixel_color, float zw, int r, int c) const
{
	regular_sample(pixel_color, zw, r, c, true);
}

void World::random_sample(RGBColor& pixel_color, float zw, int r, int c) const
{
	pixel_color = black;

	Ray			ray;
	ray.d = Vector3D(0, 0, -1);
	int 		hres = vp.hres;
	int 		vres = vp.vres;
	float		s = vp.s;


	Point2D pp; // sample point on a pixel

	for (int p = 0; p < vp.num_samples; p++)
	{
		pp.x = s *(c - 0.5*hres + rand_float());
		pp.y = s* (r - 0.5*vres + rand_float());
		ray.o = Point3D(pp.x, pp.y, zw);
		pixel_color += tracer_ptr->trace_ray(ray);
	}

	pixel_color /= vp.num_samples;
}

// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const  {
	float max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}


// ---------------------------------------------------------------------------display_pixel
// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function



void
World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);
	
#if !defined(GENERATE_PPM_DIRECTLY)
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = vp.vres - row - 1;

   paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
                             (int)(mapped_color.g * 255),
                             (int)(mapped_color.b * 255));
#else
	(void)row;
	(void)column;

	myfile << (int)(mapped_color.r * 255)<<" "
		<< (int)(mapped_color.g * 255)<<" "
		<< (int)(mapped_color.b * 255) << "\n";
#endif
}

// ----------------------------------------------------------------------------- hit_objects

ShadeRec									
World::hit_objects(const Ray& ray) {

	ShadeRec	sr(*this); 
	double		t;
	Normal normal;
	Point3D local_hit_point;
	double		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;
			sr.material_ptr     = objects[j]->get_material();
			//sr.color = objects[j]->get_color();
			sr.hit_point 		= ray.o + t * ray.d;
			normal 				= sr.normal;
			local_hit_point	 	= sr.local_hit_point;
		}
  
	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
		
	return(sr);   
}



//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}


//------------------------------------------------------------------ delete_lights

void
World::delete_lights(void) {
	int num_lights = lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		delete lights[j];
		lights[j] = NULL;
	}	
	
	lights.erase (lights.begin(), lights.end());
}


// Axis-aligned perspective viewing
// single ray per pixel.

void 
World::render_perspective(void) const
{
	//RGBColor pixel_color;
	//Ray ray;

	//int 		hres = vp.hres;
	//int 		vres = vp.vres;
	//float		s = vp.s;

	//ray.o = Point3D(0.0, 0.0, eye);

	//for (int r = vp.vres - 1; r >= 0; r--)		// up
	//	for (int c = 0; c < vp.hres; c++)	// across
	//	{
	//		ray.d = Vector3D(s*(c - 0.5 * (hres - 1.0)),
	//			s*(r - 0.5*(vres - 1.0)), -d);
	//		ray.d.normalize();
	//		pixel_color = tracer_ptr->trace_ray(ray);
	//		display_pixel(r, c, pixel_color);
	//	}
}


extern void createDir(char* filePath);

void
World::open_ppm()
{
	char filePath[512];
	char fileName[512];
	memset(filePath, '\0', 512);
	memset(fileName, '\0', 512);

	snprintf(filePath, 512, "D:\\GameProject\\RaytracingResult\\Chapter%d\\", s_chapter_number);
	snprintf(fileName, 512, "%spic%d_%s_%d.ppm", filePath, s_file_number,s_file_sample.c_str(), s_file_quality);

	
	createDir(filePath);

	myfile.open(fileName, ios::out);

	myfile << "P3\n" << vp.hres << " " << vp.vres << "\n255\n";
}

void
World::close_ppm()
{
	myfile.close();
}