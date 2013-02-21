/*
 * Sample_01.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#include "Sample_01.h"

Sample_01::Sample_01()
{
}

Sample_01::~Sample_01()
{
}

void Sample_01::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Sample_01::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Sample_01::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_01::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}
