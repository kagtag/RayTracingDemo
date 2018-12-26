#include"World.h"

int main(void)
{
	World w; //construct a default object
	w.build();
	//w.render_scene();

	w.open_ppm();

	w.camera_ptr->render_scene(w);

	w.close_ppm();

	return 0;
}