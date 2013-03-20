/*
 * Sample_23.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_23.h"
#include "OGLImageRec.h"

#include <SDL/SDL.h>

Sample_23::Sample_23()
:	m_xrot(0.0f)
,	m_yrot(0.0f)
,	m_xspeed(0.1f)
,	m_yspeed(0.1f)
,	m_z(-5.0f)
,	m_filter(0)
,	m_light(false)
,	m_part1(0)
,	m_part2(0)
,	m_p1(0)
,	m_p2(1)
,	m_quadratic(NULL)
,	m_object(0)
{
	for (int i = 0; i < TEX_QTY; ++i)
	{
		m_texture[i] = 0;
	}

	m_quadratic=gluNewQuadric();          // Create A Pointer To The Quadric Object
	gluQuadricNormals(m_quadratic, GLU_SMOOTH);   // Create Smooth Normals
	gluQuadricTexture(m_quadratic, GL_TRUE);      // Create Texture Coords
}

Sample_23::~Sample_23()
{
	delete [] m_texture;

	gluDeleteQuadric(m_quadratic);                // Delete Quadratic - Free Resources
}

void Sample_23::reshape(int width, int height)
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

void Sample_23::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear The Screen And The Depth Buffer
	glLoadIdentity();                           // Reset The View

	glTranslatef(0.0f,0.0f,m_z);

	glEnable(GL_TEXTURE_GEN_S);                     // Enable Texture Coord Generation For S ( NEW )
	glEnable(GL_TEXTURE_GEN_T);                     // Enable Texture Coord Generation For T ( NEW )

	glBindTexture(GL_TEXTURE_2D, m_texture[m_filter+(m_filter+1)]);       // This Will Select A Sphere Map
	glPushMatrix();
	glRotatef(m_xrot,1.0f,0.0f,0.0f);
	glRotatef(m_yrot,0.0f,1.0f,0.0f);
	switch(m_object)
	{
	case 0:
		glDrawCube();
		break;
	case 1:
		glTranslatef(0.0f,0.0f,-1.5f);                  // Center The Cylinder
		gluCylinder(m_quadratic,1.0f,1.0f,3.0f,32,32);            // A Cylinder With A Radius Of 0.5 And A Height Of 2
		break;
	case 2:
		gluSphere(m_quadratic,1.3f,32,32);                // Sphere With A Radius Of 1 And 16 Longitude/Latitude Segments
		break;
	case 3:
		glTranslatef(0.0f,0.0f,-1.5f);                  // Center The Cone
		gluCylinder(m_quadratic,1.0f,0.0f,3.0f,32,32);            // Cone With A Bottom Radius Of .5 And Height Of 2
		break;
	};

	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);                        // Disable Texture Coord Generation
	glDisable(GL_TEXTURE_GEN_T);                        // Disable Texture Coord Generation

	glBindTexture(GL_TEXTURE_2D, m_texture[m_filter*2]);            // This Will Select The BG Texture
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -24.0f);
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-13.3f, -10.0f,  10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 13.3f, -10.0f,  10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 13.3f,  10.0f,  10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-13.3f,  10.0f,  10.0f);
	glEnd();

	glPopMatrix();

	m_xrot+=m_xspeed;
	m_yrot+=m_yspeed;
}

void Sample_23::glDrawCube()
{
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f( 0.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	// Back Face
	glNormal3f( 0.0f, 0.0f,-0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	// Top Face
	glNormal3f( 0.0f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	// Bottom Face
	glNormal3f( 0.0f,-0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	// Right Face
	glNormal3f( 0.5f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	// Left Face
	glNormal3f(-0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}

void Sample_23::initGL()
{
	GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };                 // Ambient Light Values
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };              // Diffuse Light Values
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };                 // Light Position

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	LoadGLTextures();

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

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);            // Set The Texture Generation Mode For S To Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);            // Set The Texture Generation Mode For T To Sphere Mapping

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_23::LoadGLTextures()                                // Load Bitmaps And Convert To Textures
{
	OGLImageRec	*img[2];

	for (int i = 0; i < 2; ++i)
		img[i] = new OGLImageRec;

	img[0]->loadBMP( "data/BG.bmp" );			// Background Texture
	img[0]->loadBMP( "data/Reflect.bmp" );		// Reflection Texture (Spheremap)

	if (!m_texture[TEX_1])
		glGenTextures(TEX_QTY, &m_texture[TEX_1]);                  // Create Three Textures (For Two Images)

	for (int loop=0; loop<2; loop++)
	{
		// Create Nearest Filtered Texture
		glBindTexture(GL_TEXTURE_2D, m_texture[loop]);        // Gen Tex 0 And 1
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, img[loop]->sizeX(), img[loop]->sizeY(),
				0, GL_RGB, GL_UNSIGNED_BYTE, img[loop]->data());

		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, m_texture[loop+2]);      // Gen Tex 2, 3 And 4
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, img[loop]->sizeX(), img[loop]->sizeY(),
				0, GL_RGB, GL_UNSIGNED_BYTE, img[loop]->data());

		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, m_texture[loop+4]);      // Gen Tex 4 and 5
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img[loop]->sizeX(), img[loop]->sizeY(),
				GL_RGB, GL_UNSIGNED_BYTE, img[loop]->data());
	}
}

void Sample_23::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_23::sendMessage(int message, int mode, int x, int y)
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
		if (m_filter>=TEX_QTY)                // Is Value Greater Than 6?
			m_filter=TEX_1;           // If So, Set filter To 0
		break;
	case SDLK_SPACE:
		m_object++;       // Cycle Through The Objects
		if(m_object>3)     // Is object Greater Than 5?
			m_object=0;   // If So, Set To Zero
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

	return true;
}
