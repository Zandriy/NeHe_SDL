/*
 * Sample_03.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_03.h"

Sample_03::Sample_03()
{
}

Sample_03::~Sample_03()
{
}

void Sample_03::reshape(int width, int height)
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

void Sample_03::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Clear The Screen And The Depth Buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Move Left 1.5 Units And Into The Screen 6.0
	glLoadIdentity();
	glTranslatef( -1.5f, 0.0f, -6.0f );

	glBegin( GL_TRIANGLES );            // Drawing Using Triangles
	glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
	glVertex3f(  0.0f,  1.0f, 0.0f ); // Top
	glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Green
	glVertex3f( -1.0f, -1.0f, 0.0f ); // Bottom Left
	glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
	glVertex3f(  1.0f, -1.0f, 0.0f ); // Bottom Right
	glEnd( );                           // Finished Drawing The Triangle

	// Move Right 3 Units
	glTranslatef( 3.0f, 0.0f, 0.0f );

	glColor3f(0.5f,0.5f,1.0f);              // Set The Color To Blue One Time Only
	glBegin( GL_QUADS );                // Draw A Quad
	glVertex3f( -1.0f,  1.0f, 0.0f ); // Top Left
	glVertex3f(  1.0f,  1.0f, 0.0f ); // Top Right
	glVertex3f(  1.0f, -1.0f, 0.0f ); // Bottom Right
	glVertex3f( -1.0f, -1.0f, 0.0f ); // Bottom Left
	glEnd( );                           // Done Drawing The Quad
}

void Sample_03::initGL()
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

void Sample_03::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}
