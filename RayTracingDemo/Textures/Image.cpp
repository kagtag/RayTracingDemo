// 	Copyright (C) Kevin Suffern 2000-2007.
// 	Copyright (C) Stefan Brumme 2005.
// 	Copyright (C) Sverre Kvaale 2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <iostream>
#include <stdio.h>

#include "Constants.h"   // defines red
#include "Image.h"

// ---------------------------------------------------- default constructor

Image::Image(void)
	:	hres(100),
		vres(100)
{}


// ---------------------------------------------------- copy constructor								

Image::Image(const Image& image)
	:	hres(image.hres),
		vres(image.vres),
		pixels(image.pixels)
{}		


// ---------------------------------------------------- assignment operator	

Image& 										
Image::operator= (const Image& rhs) {
	if (this == &rhs)
		return (*this);
	
	hres 		= rhs.hres;
	vres 		= rhs.vres;
	pixels 		= rhs.pixels;

	return (*this);
}		

// ---------------------------------------------------- destructor	

Image::~Image(void)	{}
	

// ---------------------------------------------------- read_ppm_file

void										
Image::read_ppm_file(const char* file_name) {

    // read-only binary sequential access
    
	FILE* file;

	if (fopen_s(&file, file_name, "rb") != 0)
	{
		cout << "could not open file" << endl;
		return;
	}
	else
	{
		cout << "file opened" << endl;

	}

    // PPM header
    
    unsigned char ppm_type;
    if (fscanf_s(file, "P%c\n", &ppm_type) != 1){
		cout << "Invalid PPM signature" << endl;
	}
	
    // only binary PPM supported
    
    if (ppm_type != '6'){
		cout << "Only binary PPM supported" << endl;
	}

    // skip comments
    
    unsigned char dummy;
    while (fscanf_s(file ,"#%c", &dummy)) 
        while (fgetc(file) != '\n');

    // read image size
    
    if (fscanf_s(file, "%d %d\n", &hres, &vres) != 2){
		cout << "Invalid image size" << endl;
	}

    if (hres <= 0)
		cout << "Invalid image width" << endl;
	else
		cout << "hres = " << hres << endl;

    
	if (vres <= 0)
		cout << "Invalid image height" << endl;
	else
		cout << "vres = " << vres << endl;


    // maximum value to be found in the PPM file (usually 255)
    
    unsigned int max_value;
    if (fscanf_s(file, "%d\n", &max_value) != 1){
		cout << "Invalid max value" << endl;
	}

	float inv_max_value = 1.0 / (float)max_value;

    // allocate memory
    
	pixels.reserve(hres * vres);

    // read pixel data
    
	unsigned char* red = new unsigned char;
	unsigned char* green = new unsigned char;
	unsigned char* blue = new unsigned char;

    for (unsigned int y = 0; y < vres; y++) {
        for (unsigned int x = 0; x < hres; x++) {

			// old fscanf is deprecated.
			// we have to specify how many bits to read for fscanf_s function.
			fscanf_s(file, "%c", red, sizeof(char));
			fscanf_s(file, "%c", green, sizeof(char));
			fscanf_s(file, "%c", blue, sizeof(char));

			float r = *red   * inv_max_value;
			float g = *green * inv_max_value;
			float b = *blue  * inv_max_value;

			pixels.push_back(RGBColor(r, g, b));
        }
    }

	delete red;
	delete green;
	delete blue;

    // close file
    
    fclose(file);
	
	cout << "finished reading PPM file" << endl;
}



// --------------------------------------------------------------------------------------------- get_color 

RGBColor									
Image::get_color(const int row, const int column) const {
	int index = column + hres * (vres - row - 1);
	int pixels_size = pixels.size();
	
	if (index < pixels_size)
		return (pixels[index]);
	else
		return (red);    // useful for debugging 
}

 
