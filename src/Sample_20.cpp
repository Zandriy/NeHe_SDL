/*
 * Sample_20.cpp
 *
 *  Created on: Mar 6, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_20.h"

#include <SDL/SDL.h>

Sample_20::Sample_20()
:	m_masking(true)
,	m_scene(0)
,	m_roll(0.0f)
{
	for (int i = 0; i < TEX_QTY; ++i)
	{
		m_texture[i] = 0;
	}
	m_image[TEX_IMG1].loadBMP( "data/image1.bmp" );
	m_image[TEX_IMG2].loadBMP( "data/image2.bmp" );
	m_image[TEX_LOGO].loadBMP( "data/logo.bmp" );
	m_image[TEX_MASK1].loadBMP( "data/mask1.bmp" );
	m_image[TEX_MASK2].loadBMP( "data/mask2.bmp" );
}

Sample_20::~Sample_20()
{
	delete [] m_texture;
	delete [] m_image;
}

void Sample_20::reshape(int width, int height)
{
	if (height==0)                      // Prevent A Divide By Zero By
	{
		height=1;                   // Making Height Equal One
	}

	glViewport(0, 0, width, height);            // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                // Select The Projection Matrix
	glLoadIdentity();                   // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);

	glMatrixMode(GL_MODELVIEW);             // Select The Modelview Matrix
	glLoadIdentity();                   // Reset The Modelview Matrix
}

void Sample_20::draw()
{
	int curImg = TEX_LOGO;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear The Screen And The Depth Buffer
	glLoadIdentity();                           // Reset The Modelview Matrix
	glTranslatef(0.0f,0.0f,-2.0f);                      // Move Into The Screen 2 Units

	glBindTexture(GL_TEXTURE_2D, m_texture[curImg]);               // Select Our Logo Texture
	glBegin(GL_QUADS);                          // Start Drawing A Textured Quad
	glTexCoord2f(0.0f, -m_roll+0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);    // Bottom Left
	glTexCoord2f(3.0f, -m_roll+0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);    // Bottom Right
	glTexCoord2f(3.0f, -m_roll+3.0f); glVertex3f( 1.1f,  1.1f,  0.0f);    // Top Right
	glTexCoord2f(0.0f, -m_roll+3.0f); glVertex3f(-1.1f,  1.1f,  0.0f);    // Top Left
	glEnd();

	glEnable(GL_BLEND);                         // Enable Blending
	glDisable(GL_DEPTH_TEST);                       // Disable Depth Testing

	if (m_masking)                                // Is Masking Enabled?
	{
		glBlendFunc(GL_DST_COLOR,GL_ZERO);              // Blend Screen Color With Zero (Black)
	}

	if (m_scene)                              // Are We Drawing The Second Scene?
	{
		glTranslatef(0.0f,0.0f,-1.0f);                  // Translate Into The Screen One Unit
		glRotatef(m_roll*360,0.0f,0.0f,1.0f);             // Rotate On The Z Axis 360 Degrees

		curImg = TEX_IMG1;


		if (m_masking)                            // Is Masking On?
		{
			glBindTexture(GL_TEXTURE_2D, m_texture[curImg+1]);       // Select The Second Mask Texture
			glBegin(GL_QUADS);                  // Start Drawing A Textured Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);  // Bottom Left
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);  // Bottom Right
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.1f,  1.1f,  0.0f);  // Top Right
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.1f,  1.1f,  0.0f);  // Top Left
			glEnd();                        // Done Drawing The Quad
		}

		glBlendFunc(GL_ONE, GL_ONE);                    // Copy Image 2 Color To The Screen
		glBindTexture(GL_TEXTURE_2D, m_texture[curImg]);           // Select The Second Image Texture
		glBegin(GL_QUADS);                      // Start Drawing A Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);  // Bottom Left
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);  // Bottom Right
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.1f,  1.1f,  0.0f);  // Top Right
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.1f,  1.1f,  0.0f);  // Top Left
		glEnd();                            // Done Drawing The Quad
	}
	else // Otherwise
	{
		curImg = TEX_IMG2;

		if (m_masking)                            // Is Masking On?
		{
		    glBindTexture(GL_TEXTURE_2D, m_texture[curImg+1]);       // Select The First Mask Texture
		    glBegin(GL_QUADS);                  // Start Drawing A Textured Quad
		        glTexCoord2f(m_roll+0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f); // Bottom Left
		        glTexCoord2f(m_roll+4.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f); // Bottom Right
		        glTexCoord2f(m_roll+4.0f, 4.0f); glVertex3f( 1.1f,  1.1f,  0.0f); // Top Right
		        glTexCoord2f(m_roll+0.0f, 4.0f); glVertex3f(-1.1f,  1.1f,  0.0f); // Top Left
		    glEnd();                        // Done Drawing The Quad
		}

	    glBlendFunc(GL_ONE, GL_ONE);                    // Copy Image 1 Color To The Screen
	    glBindTexture(GL_TEXTURE_2D, m_texture[curImg]);           // Select The First Image Texture
	    glBegin(GL_QUADS);                      // Start Drawing A Textured Quad
	        glTexCoord2f(m_roll+0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f); // Bottom Left
	        glTexCoord2f(m_roll+4.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f); // Bottom Right
	        glTexCoord2f(m_roll+4.0f, 4.0f); glVertex3f( 1.1f,  1.1f,  0.0f); // Top Right
	        glTexCoord2f(m_roll+0.0f, 4.0f); glVertex3f(-1.1f,  1.1f,  0.0f); // Top Left
	    glEnd();                            // Done Drawing The Quad
	}

	glEnable(GL_DEPTH_TEST);                        // Enable Depth Testing
	glDisable(GL_BLEND);                            // Disable Blending

	m_roll+=0.002f;                               // Increase Our Texture Roll Variable
    if (m_roll>1.0f)                               // Is Roll Greater Than One
    {
    	m_roll-=1.0f;                         // Subtract 1 From Roll
    }
}

void Sample_20::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if (m_texture[TEX_LOGO] == 0)
		glGenTextures(TEX_QTY, &m_texture[TEX_LOGO]);                  // Create The Texture

	for (int loop=0; loop<TEX_QTY; loop++)                 // Loop Through All 5 Textures
	{
		glBindTexture(GL_TEXTURE_2D, m_texture[loop]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image[loop].sizeY(), m_image[loop].sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image[loop].data() );
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                   // Clear The Background Color To Black
	glClearDepth(1.0);                          // Enables Clearing Of The Depth Buffer
	glEnable(GL_DEPTH_TEST);                        // Enable Depth Testing
	glShadeModel(GL_SMOOTH);                        // Enables Smooth Color Shading
	glEnable(GL_TEXTURE_2D);                        // Enable 2D Texture Mapping

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_20::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_20::sendMessage(int message, int mode, int x, int y)
{
	switch (message) {
	case SDLK_SPACE:
	    m_scene=!m_scene;               // Toggle From One Scene To The Other
		break;
	case SDLK_m:
		m_masking=!m_masking;           // Toggle Masking Mode OFF/ON
		break;
	default:
		return false;
		break;
	}

	return true;
}
