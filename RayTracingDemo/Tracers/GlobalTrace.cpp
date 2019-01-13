#include "GlobalTrace.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

// -------------------------------------------------------------------- default constructor

GlobalTrace::GlobalTrace(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor

GlobalTrace::GlobalTrace(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

GlobalTrace::~GlobalTrace(void) {}


// -------------------------------------------------------------------- trace_ray

RGBColor
GlobalTrace::trace_ray(const Ray ray, const int depth) const
{
	if (depth > world_ptr->vp.max_depth)
		return black;
	else
	{
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object)
		{
			sr.depth = depth;
			sr.ray = ray;

			return sr.material_ptr->global_shade(sr);
		}
		else
		{
			return world_ptr->background_color;
		}
	}
}
