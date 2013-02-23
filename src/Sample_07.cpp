/*
 * Sample_07.cpp
 *
 *  Created on: Feb 23, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_07.h"

#include <SDL/SDL.h>

Sample_07::Sample_07()
:	m_xrot(0.0f)
,	m_yrot(0.0f)
,	m_xspeed(0.1f)
,	m_yspeed(0.1f)
,	m_z(-5.0f)
,	m_filter(0)
,	m_light(false)
{
	for (int i = 0; i < 3; ++i)
	{
		m_texture[i] = 0;
	}
	m_image.loadBMP( "data/crate.bmp" );
}

Sample_07::~Sample_07()
{
	delete [] m_texture;
}

void Sample_07::reshape(int width, int height)
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

void Sample_07::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer
	glLoadIdentity();                           // Reset The Current Matrix
	glTranslatef(0.0f,0.0f,m_z);                      // Translate Into/Out Of The Screen By z

	glRotatef(m_xrot,1.0f,0.0f,0.0f);                     // Rotate On The X Axis By xrot
	glRotatef(m_yrot,0.0f,1.0f,0.0f);                     // Rotate On The Y Axis By yrot

	glBindTexture(GL_TEXTURE_2D, m_texture[m_filter]);               // Select Our Texture

	glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 1 (Front)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 2 (Front)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Front)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 4 (Front)
		// Back Face
		glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Away From Viewer
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Back)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 2 (Back)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 3 (Back)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 4 (Back)
		// Top Face
		glNormal3f( 0.0f,-1.0f, 0.0f);                  // Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 1 (Top)
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 2 (Top)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Top)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 4 (Top)
		// Bottom Face
		glNormal3f( 0.0f, 1.0f, 0.0f);                  // Normal Pointing Down
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Bottom)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 2 (Bottom)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 3 (Bottom)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 4 (Bottom)
		// Right face
		glNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 1 (Right)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 2 (Right)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Right)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 4 (Right)
		// Left Face
		glNormal3f( 1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Left)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 2 (Left)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 3 (Left)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 4 (Left)
	glEnd();

	m_xrot+=m_xspeed;                               // Add xspeed To xrot
	m_yrot+=m_yspeed;                               // Add yspeed To yrot
}

void Sample_07::initGL()
{
	GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };                 // Ambient Light Values
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };              // Diffuse Light Values
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };                 // Light Position

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if (m_texture[0] == 0)
		glGenTextures(3, &m_texture[0]);                  // Create The Texture

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_image.sizeY(), m_image.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// set here server attributes (states)
	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping
	glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);             // Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);             // Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);            // Position The Light
	glEnable(GL_LIGHT1);                            // Enable Light One

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_07::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_07::sendMessage(int message, int mode, int x, int y)
{
	switch (message) {
	case SDLK_l:
		m_light = !m_light;
		if (!m_light)             // If Not Light
		{
			glDisable(GL_LIGHTING);     // Disable Lighting
			printf("Lighting is off\n");
		}
		else                    // Otherwise
		{
			glEnable(GL_LIGHTING);      // Enable Lighting
			printf("Lighting is on\n");
		}
		break;
	case SDLK_f:
		m_filter+=1;              // filter Value Increases By One
		if (m_filter>2)                // Is Value Greater Than 2?
			m_filter=0;           // If So, Set filter To 0
		if (m_filter == 0)
			printf("Nearest Filtered Texture\n");
		if (m_filter == 1)
			printf("Linear Filtered Texture\n");
		if (m_filter == 2)
			printf("MipMapped Filtered Texture\n");
		break;
	case SDLK_PAGEUP:
		m_z-=0.2f;               // If So, Move Into The Screen
		break;
	case SDLK_PAGEDOWN:
		m_z+=0.2f;               // If So, Move Towards The Viewer
		break;
	case SDLK_UP:
		m_xspeed-=0.1f;              // If So, Decrease xspeed
		break;
	case SDLK_DOWN:
		m_xspeed+=0.1f;              // If So, Increase xspeed
		break;
	case SDLK_RIGHT:
		m_yspeed+=0.1f;              // If So, Increase yspeed
		break;
	case SDLK_LEFT:
		m_yspeed-=0.1f;              // If So, Decrease yspeed
		break;
	default:
		return false;
		break;
	}

	drawGLScene();
	return true;
}
