#pragma once

#include "Texture.h"

class TInstance : public Texture
{
public:
	TInstance(void);

	TInstance(Texture* obj_ptr);

	TInstance(const TInstance& instance);

	virtual TInstance*
		clone(void) const;

	virtual
		~TInstance(void);

	TInstance&
		operator= (const TInstance& rhs);
	// constructors, etc

	void
		set_texture(Texture* t_ptr);

	virtual RGBColor
		get_color(const ShadeRec& sr)const;

	// affine transformation functions



	void
		translate(const Vector3D& trans);

	void
		translate(const double dx, const double dy, const double dz);

	void
		scale(const Vector3D& s);

	void
		scale(const float sx, const float sy, const float sz);

	virtual void
		rotate_x(const double theta);

	virtual void
		rotate_y(const double theta);

	virtual void
		rotate_z(const double theta);

	void
		shear(const Matrix& m);

private:

	Texture* texture_ptr;		// texture being transformed
	Matrix inv_matrix;			// inverse transformation matrix

};

