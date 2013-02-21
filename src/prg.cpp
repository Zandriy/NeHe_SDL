/*
 * prg.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: Andrew Zhabura
 */

#include "OGLApplication.h"
#include "NeHeConfig.h"

#if __APPLE__
int SDL_main(int argc, char ** argv)
#else
int main(int argc, char ** argv)
#endif
{
    fprintf(stdout,"Version %d.%d\n",
            NeHe_VERSION_MAJOR,
            NeHe_VERSION_MINOR);

	OGL_Application app;

	app.init();

	return app.exec();
}
