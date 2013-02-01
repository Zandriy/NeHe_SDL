/*
 * prg.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: Andrew Zhabura
 */

#include <cstdio>

#include "NeHeConfig.h"

int main()
{
    fprintf(stdout,"Version %d.%d\n",
    		NeHe_VERSION_MAJOR,
    		NeHe_VERSION_MINOR);

	return 0;
}
