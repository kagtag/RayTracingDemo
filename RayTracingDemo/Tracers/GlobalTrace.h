#pragma once

#include "Tracer.h"

class GlobalTrace : public Tracer {
public:

	GlobalTrace(void);

	GlobalTrace(World* _worldPtr);

	virtual
		~GlobalTrace(void);

	virtual RGBColor
		trace_ray(const Ray ray, const int depth) const;
};