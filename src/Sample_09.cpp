/*
 * Sample_09.cpp
 *
 *  Created on: Feb 23, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_09.h"

Sample_09::Sample_09()
:	m_twinkle(false)
,	m_zoom(-15.0f)
,	m_tilt(90.0f)
,	m_spin(0.0f)
,	m_loop(0.0f)
{
	m_texture[0] = 0;
	m_image = SDL_LoadBMP( "data/star.bmp" );
}

Sample_09::~Sample_09()
{
	delete [] m_texture;
}

void Sample_09::reshape(int width, int height)
{
	// Height / width ration
	GLfloat ratio;
	// Protect against a divide by zero
	if ( height == 0 )
		height = 1;
	ratio = ( GLfloat )width / ( GLfloat )height;
	// Setup our viewport.
	glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
	// change to the projection matrix and set our viewing volume.
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	// Set our perspective
	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
	// Make sure we're changing the model view and not the projection
	glMatrixMode( GL_MODELVIEW );
	// Reset The View
	glLoadIdentity( );
}

void Sample_09::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer

	for (m_loop=0; m_loop<NUM; m_loop++)						// Loop Through All The Stars
	{
		glLoadIdentity();								// Reset The View Before We Draw Each Star
		glTranslatef(0.0f,0.0f,m_zoom);					// Zoom Into The Screen (Using The Value In 'zoom')
		glRotatef(m_tilt,1.0f,0.0f,0.0f);					// Tilt The View (Using The Value In 'tilt')
		glRotatef(m_star[m_loop].angle,0.0f,1.0f,0.0f);		// Rotate To The Current Stars Angle
		glTranslatef(m_star[m_loop].dist,0.0f,0.0f);		// Move Forward On The X Plane
		glRotatef(-m_star[m_loop].angle,0.0f,1.0f,0.0f);	// Cancel The Current Stars Angle
		glRotatef(-m_tilt,1.0f,0.0f,0.0f);				// Cancel The Screen Tilt

		if (m_twinkle)
		{
			glColor4ub(m_star[(NUM-m_loop)-1].r,m_star[(NUM-m_loop)-1].g,m_star[(NUM-m_loop)-1].b,255);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();
		}

		glRotatef(m_spin,0.0f,0.0f,1.0f);
		glColor4ub(m_star[m_loop].r,m_star[m_loop].g,m_star[m_loop].b,255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();

		m_spin+=0.01f;
		m_star[m_loop].angle+=float(m_loop)/NUM;
		m_star[m_loop].dist-=0.01f;
		if (m_star[m_loop].dist<0.0f)
		{
			m_star[m_loop].dist+=5.0f;
			m_star[m_loop].r=rand()%256;
			m_star[m_loop].g=rand()%256;
			m_star[m_loop].b=rand()%256;
		}
	}
}

void Sample_09::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Transparency
	glEnable(GL_BLEND);

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)

	if (m_texture[0] == 0)
	{
		glGenTextures(1, &m_texture[0]);                // Create The Texture
		for (m_loop=0; m_loop<NUM; m_loop++)
		{
			m_star[m_loop].angle=0.0f;
			m_star[m_loop].dist=(float(m_loop)/NUM)*5.0f;
			m_star[m_loop].r=rand()%256;
			m_star[m_loop].g=rand()%256;
			m_star[m_loop].b=rand()%256;
		}
	}

	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image->w, m_image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_image->pixels);

}

void Sample_09::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_09::sendMessage(int message, int mode, int x, int y)
{
	switch (message) {
	case SDLK_t:
		m_twinkle=!m_twinkle;
		break;
	case SDLK_PAGEUP:
		m_zoom-=0.2f;
		break;
	case SDLK_PAGEDOWN:
		m_zoom+=0.2f;
		break;
	case SDLK_UP:
		m_tilt-=0.5f;
		break;
	case SDLK_DOWN:
		m_tilt+=0.5f;
		break;
	default:
		return false;
		break;
	}

	drawGLScene();
	return true;
}
