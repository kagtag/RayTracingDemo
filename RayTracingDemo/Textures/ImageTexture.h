#pragma once

#include "Texture.h"
#include "Image.h"
#include "Mapping.h"

class ImageTexture : public Texture
{
public:

	ImageTexture(void);

	ImageTexture(Image* _image_ptr);

	ImageTexture(const ImageTexture& it);

	ImageTexture&
		operator= (const ImageTexture& rhs);

	virtual ImageTexture*
		clone(void) const;

	virtual
		~ImageTexture(void);


	//

	virtual RGBColor
		get_color(const ShadeRec& sr)const;

	//

	void
		set_image(Image* _image_ptr);

	void
		set_mapping(Mapping* map_ptr);

private:

	int hres;			// horizontal image resolution
	int vres;			// vertical image resolution
	Image* image_ptr;	// the image
	Mapping* mapping_ptr;// mapping technique used, if any
};