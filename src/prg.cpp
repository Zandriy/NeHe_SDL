/*
 * prg.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: Andrew Zhabura
 */

#include <cstdio>

#include <SDL/SDL.h>
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

	return 0;
}
