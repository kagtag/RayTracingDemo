#pragma once

#include "Constants.h"
#include "Mapping.h"

enum mapping_type
{
	light_probe,
	panoramic
};

class LightProbe : public Mapping {
public:

	LightProbe(void);

	LightProbe(const LightProbe& sm);

	LightProbe&
		operator= (const LightProbe& rhs);

	virtual LightProbe*
		clone(void) const;

	~LightProbe(void);

	virtual void
		get_texel_coordinates(const 	Point3D& 	local_hit_point,
			const 	int 		xres,
			const 	int 		yres,
			int& 		row,
			int& 		column) const;

private:
	mapping_type map_type;
};