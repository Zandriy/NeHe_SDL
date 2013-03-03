/*
 * Sample_16.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_16.h"

#include <SDL/SDL.h>

GLuint Sample_16::m_fogMode[3]= { GL_EXP, GL_EXP2, GL_LINEAR };
GLfloat Sample_16::m_fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};

Sample_16::Sample_16()
:	m_xrot(0.0f)
,	m_yrot(0.0f)
,	m_xspeed(0.1f)
,	m_yspeed(0.1f)
,	m_z(-5.0f)
,	m_filter(0)
,	m_light(false)
,	m_fogfilter(0)
{
	for (int i = 0; i < TEX_QTY; ++i)
	{
		m_texture[i] = 0;
	}
	m_image.loadBMP( "data/crate.bmp" );
}

Sample_16::~Sample_16()
{
	delete [] m_texture;
}

void Sample_16::reshape(int width, int height)
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

void Sample_16::draw()
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

void Sample_16::initGL()
{
	GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };                 // Ambient Light Values
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };              // Diffuse Light Values
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };                 // Light Position

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if (m_texture[NEAREST_FILTER] == 0)
		glGenTextures(TEX_QTY, &m_texture[NEAREST_FILTER]);                  // Create The Texture

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[NEAREST_FILTER]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[LINEAR_FILTER]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[MIPMAPPED_FILTER]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_image.sizeY(), m_image.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// set here server attributes (states)
	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping
	glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading

	glClearColor(0.5f,0.5f,0.5f,1.0f);          // We'll Clear To The Color Of The Fog ( Modified )

	glFogi(GL_FOG_MODE, m_fogMode[m_fogfilter]);        // Fog Mode
	glFogfv(GL_FOG_COLOR, m_fogColor);            // Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.35f);              // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
	glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
	glFogf(GL_FOG_END, 5.0f);               // Fog End Depth
	glEnable(GL_FOG);                   // Enables GL_FOG

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

void Sample_16::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_16::sendMessage(int message, int mode, int x, int y)
{
	switch (message) {
	case SDLK_l:
		m_light = !m_light;
		if (!m_light)             // If Not Light
		{
			glDisable(GL_LIGHTING);     // Disable Lighting
			printf("Lighting is OFF\n");
		}
		else                    // Otherwise
		{
			glEnable(GL_LIGHTING);      // Enable Lighting
			printf("Lighting is ON\n");
		}
		break;
	case SDLK_f:
		m_filter+=1;              // filter Value Increases By One
		if (m_filter>=TEX_QTY)                // Is Value Greater Than 2?
			m_filter=NEAREST_FILTER;           // If So, Set filter To 0
		if (m_filter == NEAREST_FILTER)
			printf("Nearest Filtered Texture\n");
		if (m_filter == LINEAR_FILTER)
			printf("Linear Filtered Texture\n");
		if (m_filter == MIPMAPPED_FILTER)
			printf("MipMapped Filtered Texture\n");
		break;
	case SDLK_g:
	    m_fogfilter+=1;                   // Increase fogfilter By One
	    if (m_fogfilter>2)             // Is fogfilter Greater Than 2?
	    {
	        m_fogfilter=0;                // If So, Set fogfilter To Zero
	    }
		if (m_fogfilter == 0)
			printf("GL_EXP fog mode\n");
		if (m_fogfilter == 1)
			printf("GL_EXP2 fog mode\n");
		if (m_fogfilter == 2)
			printf("GL_LINEAR fog mode\n");
	    glFogi (GL_FOG_MODE, m_fogMode[m_fogfilter]);   // Fog Mode
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
