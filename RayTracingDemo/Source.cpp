#include"World.h"

#include<Windows.h>
// Helper function, since adding <Windows.h> would have conflict with the
// Rectangle class
void createDir(char* filePath)
{
	CreateDirectory(filePath, NULL);
}

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

