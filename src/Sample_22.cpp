/*
 * Sample_22.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_22.h"
#include "OGLInspector.h"

#define MAX_EMBOSS (GLfloat)0.01f                       // Maximum Emboss-Translate. Increase To Get Higher Immersion
#define __ARB_ENABLE true                           // Used To Disable ARB Extensions Entirely
// #define EXT_INFO                             // Uncomment To See Your Extensions At Start-Up?
#define MAX_EXTENSION_SPACE 10240                       // Characters For Extension-Strings
#define MAX_EXTENSION_LENGTH 256                        // Maximum Characters In One Extension-String


GLfloat Sample_22::s_LightAmbient[]  = { 0.2f, 0.2f, 0.2f};
GLfloat Sample_22::s_LightDiffuse[]  = { 1.0f, 1.0f, 1.0f};
GLfloat Sample_22::s_LightPosition[] = { 0.0f, 0.0f, 2.0f};
GLfloat Sample_22::s_Gray[]      = { 0.5f, 0.5f, 0.5f, 1.0f};

// Data Contains The Faces Of The Cube In Format 2xTexCoord, 3xVertex.
// Note That The Tesselation Of The Cube Is Only Absolute Minimum.
GLfloat Sample_22::s_data[]= {
		// FRONT FACE
		0.0f, 0.0f,     -1.0f, -1.0f, +1.0f,
		1.0f, 0.0f,     +1.0f, -1.0f, +1.0f,
		1.0f, 1.0f,     +1.0f, +1.0f, +1.0f,
		0.0f, 1.0f,     -1.0f, +1.0f, +1.0f,
		// BACK FACE
		1.0f, 0.0f,     -1.0f, -1.0f, -1.0f,
		1.0f, 1.0f,     -1.0f, +1.0f, -1.0f,
		0.0f, 1.0f,     +1.0f, +1.0f, -1.0f,
		0.0f, 0.0f,     +1.0f, -1.0f, -1.0f,
		// Top Face
		0.0f, 1.0f,     -1.0f, +1.0f, -1.0f,
		0.0f, 0.0f,     -1.0f, +1.0f, +1.0f,
		1.0f, 0.0f,     +1.0f, +1.0f, +1.0f,
		1.0f, 1.0f,     +1.0f, +1.0f, -1.0f,
		// Bottom Face
		1.0f, 1.0f,     -1.0f, -1.0f, -1.0f,
		0.0f, 1.0f,     +1.0f, -1.0f, -1.0f,
		0.0f, 0.0f,     +1.0f, -1.0f, +1.0f,
		1.0f, 0.0f,     -1.0f, -1.0f, +1.0f,
		// Right Face
		1.0f, 0.0f,     +1.0f, -1.0f, -1.0f,
		1.0f, 1.0f,     +1.0f, +1.0f, -1.0f,
		0.0f, 1.0f,     +1.0f, +1.0f, +1.0f,
		0.0f, 0.0f,     +1.0f, -1.0f, +1.0f,
		// Left Face
		0.0f, 0.0f,     -1.0f, -1.0f, -1.0f,
		1.0f, 0.0f,     -1.0f, -1.0f, +1.0f,
		1.0f, 1.0f,     -1.0f, +1.0f, +1.0f,
		0.0f, 1.0f,     -1.0f, +1.0f, -1.0f
};


Sample_22::Sample_22()
:	m_xrot(0.0f)
,	m_yrot(0.0f)
,	m_zrot(0.0f)
,	m_multitextureSupported(false)
,	m_useMultitexture(false)
,	m_maxTexelUnits(1)
,	m_filter(1)
,	m_glLogo(0)
,	m_multiLogo(0)
{
	m_texture[TEX_1] = 0;

	OGLInspector inspector;

	if (__ARB_ENABLE && inspector.MultiTexSupported() && inspector.TexCombineSupported())
	{
#ifdef EXT_INFO
		printf("The GL_ARB_multitexture extension will be used.");
#endif
		m_useMultitexture=true;
	}

}

Sample_22::~Sample_22()
{
	delete [] m_texture;
}

void Sample_22::reshape(int width, int height)
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

void Sample_22::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer
	glLoadIdentity();                           // Reset The Current Matrix
	glTranslatef(0.0f,0.0f,-5.0f);                      // Move Into The Screen 5 Units

	glRotatef(m_xrot,1.0f,0.0f,0.0f);                     // Rotate On The X Axis
	glRotatef(m_yrot,0.0f,1.0f,0.0f);                     // Rotate On The Y Axis
	glRotatef(m_zrot,0.0f,0.0f,1.0f);                     // Rotate On The Z Axis

	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);               // Select Our Texture

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glEnd();

	m_xrot+=0.3f;                             // X Axis Rotation
	m_yrot+=0.2f;                             // Y Axis Rotation
	m_zrot+=0.4f;                             // Z Axis Rotation
}

void Sample_22::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)
	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective

	loadGLTextures();

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_22::initLights()
{
	glLightfv(GL_LIGHT1, GL_AMBIENT, s_LightAmbient);              // Load Light-Parameters into GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, s_LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, s_LightPosition);
	glEnable(GL_LIGHT1);
}

int Sample_22::loadGLTextures()
{                              // Load Bitmaps And Convert To Textures
	bool status=true;                           // Status Indicator
	char *alpha=NULL;

	m_image.loadBMP( "data/Base.bmp" );

	if (m_texture[TEX_1] == 0)
		glGenTextures(TEX_QTY, &m_texture[TEX_1]);                  // Create Textures

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	// Generate The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	// Generate The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	// Generate The Texture
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_image.sizeY(), m_image.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );



}


void Sample_22::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}
