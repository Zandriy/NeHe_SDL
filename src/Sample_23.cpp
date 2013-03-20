/*
 * Sample_23.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_23.h"

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
	m_image.loadBMP( "data/BG.bmp" );

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer

	glLoadIdentity();                   // Reset The View
	glTranslatef(0.0f,0.0f,m_z);              // Translate Into The Screen

	glRotatef(m_xrot,1.0f,0.0f,0.0f);             // Rotate On The X Axis
	glRotatef(m_yrot,0.0f,1.0f,0.0f);             // Rotate On The Y Axis

	glBindTexture(GL_TEXTURE_2D, m_texture[m_filter]);      // Select A Filtered Texture

	switch(m_object)                      // Check object To Find Out What To Draw
	{
	case 0:                         // Drawing Object 1
		glDrawCube();                   // Draw Our Cube
		break;                      // Done
	case 1:                         // Drawing Object 2
		glTranslatef(0.0f,0.0f,-1.5f);          // Center The Cylinder
		gluCylinder(m_quadratic,1.0f,1.0f,3.0f,32,32);    // Draw Our Cylinder
		break;                      // Done
	case 2:                         // Drawing Object 3
		gluDisk(m_quadratic,0.5f,1.5f,32,32);     // Draw A Disc (CD Shape)
		break;                      // Done
	case 3:                         // Drawing Object 4
		gluSphere(m_quadratic,1.3f,32,32);        // Draw A Sphere
		break;                      // Done
	case 4:                         // Drawing Object 5
		glTranslatef(0.0f,0.0f,-1.5f);          // Center The Cone
		gluCylinder(m_quadratic,1.0f,0.0f,3.0f,32,32);    // A Cone With A Bottom Radius Of .5 And A Height Of 2
		break;                      // Done
	case 5:                         // Drawing Object 6
		m_part1+=m_p1;                  // Increase Start Angle
		m_part2+=m_p2;                  // Increase Sweep Angle

		if(m_part1>359)                    // 360 Degrees
		{
			m_p1=0;                   // Stop Increasing Start Angle
			m_part1=0;                // Set Start Angle To Zero
			m_p2=1;                   // Start Increasing Sweep Angle
			m_part2=0;                // Start Sweep Angle At Zero
		}
		if(m_part2>359)                    // 360 Degrees
		{
			m_p1=1;                   // Start Increasing Start Angle
			m_p2=0;                   // Stop Increasing Sweep Angle
		}
		gluPartialDisk(m_quadratic,0.5f,1.5f,32,32,m_part1,m_part2-m_part1);    // A Disk Like The One Before
		break;                      // Done
	};

	m_xrot+=m_xspeed;                       // Increase Rotation On X Axis
	m_yrot+=m_yspeed;                       // Increase Rotation On Y Axis
}

void Sample_23::glDrawCube()
{
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
}

void Sample_23::initGL()
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
		if (m_filter>=TEX_QTY)                // Is Value Greater Than 2?
			m_filter=NEAREST_FILTER;           // If So, Set filter To 0
		if (m_filter == NEAREST_FILTER)
			printf("Nearest Filtered Texture\n");
		if (m_filter == LINEAR_FILTER)
			printf("Linear Filtered Texture\n");
		if (m_filter == MIPMAPPED_FILTER)
			printf("MipMapped Filtered Texture\n");
		break;
	case SDLK_SPACE:
		m_object++;       // Cycle Through The Objects
		if(m_object>5)     // Is object Greater Than 5?
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
