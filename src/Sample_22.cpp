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
		m_multitextureSupported=true;
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

	doCube();

	m_xrot+=0.3f;                             // X Axis Rotation
	m_yrot+=0.2f;                             // Y Axis Rotation
	m_zrot+=0.4f;                             // Z Axis Rotation
}

void Sample_22::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)
	loadGLTextures();				// Jump To Texture Loading Routine

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	initLights();										// Initialize OpenGL Light

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_22::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

void Sample_22::initLights()
{
	glLightfv(GL_LIGHT1, GL_AMBIENT, s_LightAmbient);              // Load Light-Parameters into GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, s_LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, s_LightPosition);
	glEnable(GL_LIGHT1);
}

void Sample_22::loadGLTextures()
{                              // Load Bitmaps And Convert To Textures
	char *alpha=NULL;

	// Load The Tile-Bitmap For Base-Texture
	m_image.loadBMP( "data/Base.bmp" );

	if (m_texture[TEX_1] == 0)
		glGenTextures(TEX_QTY, &m_texture[TEX_1]);                  // Create Textures

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	// Generate The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	// Generate The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	// Generate The Texture
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, m_image.sizeY(), m_image.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Load The Bumpmaps
	m_image.loadBMP( "data/Bump.bmp" );

	glPixelTransferf(GL_RED_SCALE,0.5f);						// Scale RGB By 50%, So That We Have Only
	glPixelTransferf(GL_GREEN_SCALE,0.5f);						// Half Intenstity
	glPixelTransferf(GL_BLUE_SCALE,0.5f);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);	// No Wrapping, Please!
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,s_Gray);

	if (m_bump[TEX_1] == 0)
		glGenTextures(TEX_QTY, &m_bump[TEX_1]); 										// Create Three Textures

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_bump[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_bump[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_bump[TEX_3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, m_image.sizeY(), m_image.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	for (int i=0; i<3*m_image.sizeY()*m_image.sizeY(); i++)		// Invert The Bumpmap
		m_image.data()[i]=255-m_image.data()[i];

	if (m_invbump[TEX_1] == 0)
		glGenTextures(TEX_QTY, &m_invbump[TEX_1]);	// Create Three Textures

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_invbump[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_invbump[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_invbump[TEX_3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, m_image.sizeY(), m_image.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	glPixelTransferf(GL_RED_SCALE,1.0f);				// Scale RGB Back To 100% Again
	glPixelTransferf(GL_GREEN_SCALE,1.0f);
	glPixelTransferf(GL_BLUE_SCALE,1.0f);

	// Load The Logo-Bitmaps
	m_image.loadBMP( "data/OpenGL_ALPHA.bmp" );

	alpha=new char[4*m_image.sizeX()*m_image.sizeY()];		// Create Memory For RGBA8-Texture
	for (int a=0; a<m_image.sizeX()*m_image.sizeY(); a++)
		alpha[4*a+3]=m_image.data()[a*3];					// Pick Only Red Value As Alpha!

	m_image.loadBMP( "Data/OpenGL.bmp");
	for (int a=0; a<m_image.sizeX()*m_image.sizeY(); a++) {
		alpha[4*a]=m_image.data()[a*3];					// R
		alpha[4*a+1]=m_image.data()[a*3+1];				// G
		alpha[4*a+2]=m_image.data()[a*3+2];				// B
	}

	if (m_glLogo == 0)
		glGenTextures(1, &m_glLogo);				// Create One Textures

	// Create Linear Filtered RGBA8-Texture
	glBindTexture(GL_TEXTURE_2D, m_glLogo);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, alpha );
	delete alpha;

	// Load The "Extension Enabled"-Logo
	m_image.loadBMP( "Data/multi_on_alpha.bmp" );
	alpha=new char[4*m_image.sizeX()*m_image.sizeY()];		// Create Memory For RGBA8-Texture
	for (int a=0; a<m_image.sizeX()*m_image.sizeY(); a++)
		alpha[4*a+3]=m_image.data()[a*3];					// Pick Only Red Value As Alpha!

	m_image.loadBMP( "Data/multi_on.bmp" );
	for (int a=0; a<m_image.sizeX()*m_image.sizeY(); a++) {
		alpha[4*a]=m_image.data()[a*3];					// R
		alpha[4*a+1]=m_image.data()[a*3+1];				// G
		alpha[4*a+2]=m_image.data()[a*3+2];				// B
	}

	if (m_multiLogo == 0)
		glGenTextures(1, &m_multiLogo);						// Create One Textures

	// Create Linear Filtered RGBA8-Texture
	glBindTexture(GL_TEXTURE_2D, m_multiLogo);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_image.sizeX(), m_image.sizeY(), 0, GL_RGBA, GL_UNSIGNED_BYTE, alpha);
	delete alpha;
}

void Sample_22::doCube()
{
	int i;
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f( 0.0f, 0.0f, +1.0f);
	for (i=0; i<4; i++) {
		glTexCoord2f(s_data[5*i],s_data[5*i+1]);
		glVertex3f(s_data[5*i+2],s_data[5*i+3],s_data[5*i+4]);
	}
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);
	for (i=4; i<8; i++) {
		glTexCoord2f(s_data[5*i],s_data[5*i+1]);
		glVertex3f(s_data[5*i+2],s_data[5*i+3],s_data[5*i+4]);
	}
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	for (i=8; i<12; i++) {
		glTexCoord2f(s_data[5*i],s_data[5*i+1]);
		glVertex3f(s_data[5*i+2],s_data[5*i+3],s_data[5*i+4]);
	}
	// Bottom Face
	glNormal3f( 0.0f,-1.0f, 0.0f);
	for (i=12; i<16; i++) {
		glTexCoord2f(s_data[5*i],s_data[5*i+1]);
		glVertex3f(s_data[5*i+2],s_data[5*i+3],s_data[5*i+4]);
	}
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);
	for (i=16; i<20; i++) {
		glTexCoord2f(s_data[5*i],s_data[5*i+1]);
		glVertex3f(s_data[5*i+2],s_data[5*i+3],s_data[5*i+4]);
	}
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (i=20; i<24; i++) {
		glTexCoord2f(s_data[5*i],s_data[5*i+1]);
		glVertex3f(s_data[5*i+2],s_data[5*i+3],s_data[5*i+4]);
	}
	glEnd();
}
