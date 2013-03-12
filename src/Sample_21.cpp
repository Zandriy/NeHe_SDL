/*
 * Sample_21.cpp
 *
 *  Created on: Mar 12, 2013
 *      Author: Andrew Zhabura
 */

#include "Sample_21.h"

int	Sample_21::s_steps[STEPS]={ 1, 2, 4, 5, 10, 20 };                // Stepping Values For Slow Video Adjustment

Sample_21::Sample_21()
:	m_filled(false)
,	m_gameover(false)
,	m_anti(false)
,	m_delay(0)
,	m_adjust(3)
,	m_lives(5)
,	m_level(1)
,	m_level2(m_level)
,	m_stage(1)
,	m_base(0)
{
}

Sample_21::~Sample_21()
{
}

void Sample_21::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Sample_21::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Sample_21::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_21::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}
