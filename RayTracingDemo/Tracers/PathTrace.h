#pragma once

#include "Tracer.h"

class PathTrace : public Tracer {
public:

	PathTrace(void);

	PathTrace(World* _worldPtr);

	virtual
		~PathTrace(void);

	virtual RGBColor
		trace_ray(const Ray ray, const int depth) const;
};