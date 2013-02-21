/*
 * Sample_05.cpp
 *
 *  Created on: Feb 21, 2053
 *      Author: Andrew Zhabura
 */


#include "Sample_05.h"

Sample_05::Sample_05()
:	m_rtri(0.0)
,	m_rquad(0.0)
{
}

Sample_05::~Sample_05()
{
}

void Sample_05::reshape(int width, int height)
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
	// Make sure we're chaning the model view and not the projection
	glMatrixMode( GL_MODELVIEW );
	// Reset The View
	glLoadIdentity( );
}

void Sample_05::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Clear The Screen And The Depth Buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Move Left 1.5 Units And Into The Screen 6.0
	glLoadIdentity();
	glTranslatef( -1.5f, 0.0f, -6.0f );
	glRotatef(m_rtri,0.0f,1.0f,0.0f);             // Rotate The Pyramid On The Y axis

	glBegin( GL_TRIANGLES );            // Drawing A Pyramid

	glColor3f(1.0f,0.0f,0.0f);          // Red
	glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Pyramid (Front)
	glColor3f(0.0f,1.0f,0.0f);          // Green
	glVertex3f(-1.0f,-1.0f, 1.0f);          // Left Of Pyramid (Front)
	glColor3f(0.0f,0.0f,1.0f);          // Blue
	glVertex3f( 1.0f,-1.0f, 1.0f);          // Right Of Pyramid (Front)

	glColor3f(1.0f,0.0f,0.0f);          // Red
	glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Right)
	glColor3f(0.0f,0.0f,1.0f);          // Blue
	glVertex3f( 1.0f,-1.0f, 1.0f);          // Left Of Triangle (Right)
	glColor3f(0.0f,1.0f,0.0f);          // Green
	glVertex3f( 1.0f,-1.0f, -1.0f);         // Right Of Triangle (Right)

	glColor3f(1.0f,0.0f,0.0f);          // Red
	glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Back)
	glColor3f(0.0f,1.0f,0.0f);          // Green
	glVertex3f( 1.0f,-1.0f, -1.0f);         // Left Of Triangle (Back)
	glColor3f(0.0f,0.0f,1.0f);          // Blue
	glVertex3f(-1.0f,-1.0f, -1.0f);         // Right Of Triangle (Back)

	glColor3f(1.0f,0.0f,0.0f);          // Red
	glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Left)
	glColor3f(0.0f,0.0f,1.0f);          // Blue
	glVertex3f(-1.0f,-1.0f,-1.0f);          // Left Of Triangle (Left)
	glColor3f(0.0f,1.0f,0.0f);          // Green
	glVertex3f(-1.0f,-1.0f, 1.0f);          // Right Of Triangle (Left)

	glEnd( );                           // Finished Drawing The Pyramid

	// Move Right 3 Units
	glTranslatef( 3.0f, 0.0f, 0.0f );
	glRotatef(m_rquad,1.0f,0.0f,0.0f);            // Rotate The Cube On The X axis

	glBegin( GL_QUADS );                // Draw A Cube

	glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Green
	glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
	glVertex3f( 1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)

	glColor3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
	glVertex3f( 1.0f,-1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
	glVertex3f(-1.0f,-1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
	glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Bottom)
	glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Bottom)

	glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
	glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
	glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
	glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Front)

	glColor3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
	glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Back)
	glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Back)
	glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Back)
	glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Back)

	glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
	glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Left)
	glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Left)
	glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Left)

	glColor3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
	glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Right)
	glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
	glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
	glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Right)

	glEnd( );                           // Done Drawing The Cube

	m_rtri+=0.2f;                     // Increase The Rotation Variable For The Pyramid
	m_rquad-=0.15f;                       // Decrease The Rotation Variable For The Cube
}

void Sample_05::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_05::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}
