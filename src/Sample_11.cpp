/*
 * Sample_11.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_11.h"
#include <cmath>

Sample_11::Sample_11()
:	m_xrot(0.0f)
,	m_yrot(0.0f)
,	m_zrot(0.0f)

,	m_wiggle_count(0)
,	m_hold(0.0f)

{
	glGenTextures(TEX_QTY, &m_texture[TEX_1]);                  // Create The Texture

	m_image.loadBMP( "data/tim.bmp" );

	// Loop Through The X Plane
	for(int x=0; x<45; x++)
	{
		// Loop Through The Y Plane
		for(int y=0; y<45; y++)
		{
			// Apply The Wave To Our Mesh
			m_points[x][y][0]=float((x/5.0f)-4.5f);
			m_points[x][y][1]=float((y/5.0f)-4.5f);
			m_points[x][y][2]=float(sin((((x/5.0f)*40.0f)/360.0f)*3.141592654*2.0f));
		}
	}
}

Sample_11::~Sample_11()
{
	delete [] m_texture;
}

void Sample_11::reshape(int width, int height)
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

void Sample_11::draw()
{
	int x, y;                       // Loop Variables
	float float_x, float_y, float_xb, float_yb;     // Used To Break The Flag Into Tiny Quads

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer
	glLoadIdentity();                           // Reset The Current Matrix
	glTranslatef(0.0f,0.0f,-12.0f);                      // Move Into The Screen 5 Units

	glRotatef(m_xrot,1.0f,0.0f,0.0f);                     // Rotate On The X Axis
	glRotatef(m_yrot,0.0f,1.0f,0.0f);                     // Rotate On The Y Axis
	glRotatef(m_zrot,0.0f,0.0f,1.0f);                     // Rotate On The Z Axis

	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);               // Select Our Texture

	glBegin(GL_QUADS);                  // Start Drawing Our Quads
	for( x = 0; x < 44; x++ )                // Loop Through The X Plane (44 Points)
	{
		for( y = 0; y < 44; y++ )            // Loop Through The Y Plane (44 Points)
		{
			float_x = float(x)/44.0f;       // Create A Floating Point X Value
			float_y = float(y)/44.0f;       // Create A Floating Point Y Value
			float_xb = float(x+1)/44.0f;        // Create A Floating Point Y Value+0.0227f
			float_yb = float(y+1)/44.0f;        // Create A Floating Point Y Value+0.0227f

			glTexCoord2f( float_x, float_y);    // First Texture Coordinate (Bottom Left)
			glVertex3f( m_points[x][y][0], m_points[x][y][1], m_points[x][y][2] );

			glTexCoord2f( float_x, float_yb );  // Second Texture Coordinate (Top Left)
			glVertex3f( m_points[x][y+1][0], m_points[x][y+1][1], m_points[x][y+1][2] );

			glTexCoord2f( float_xb, float_yb ); // Third Texture Coordinate (Top Right)
			glVertex3f( m_points[x+1][y+1][0], m_points[x+1][y+1][1], m_points[x+1][y+1][2] );

			glTexCoord2f( float_xb, float_y );  // Fourth Texture Coordinate (Bottom Right)
			glVertex3f( m_points[x+1][y][0], m_points[x+1][y][1], m_points[x+1][y][2] );
		}
	}
	glEnd();                        // Done Drawing Our Quads

	if( m_wiggle_count == 2 )                 // Used To Slow Down The Wave (Every 2nd Frame Only)
	{
		for( y = 0; y < 45; y++ )            // Loop Through The Y Plane
		{
			m_hold=m_points[0][y][2];           // Store Current Value One Left Side Of Wave
			for( x = 0; x < 44; x++)     // Loop Through The X Plane
			{
				// Current Wave Value Equals Value To The Right
				m_points[x][y][2] = m_points[x+1][y][2];
			}
			m_points[44][y][2]=m_hold;          // Last Value Becomes The Far Left Stored Value
		}
		m_wiggle_count = 0;               // Set Counter Back To Zero
	}
	m_wiggle_count++;                     // Increase The Counter

	m_xrot+=0.3f;                             // X Axis Rotation
	m_yrot+=0.2f;                             // Y Axis Rotation
	m_zrot+=0.4f;                             // Z Axis Rotation
}

void Sample_11::initGL()
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
	glPolygonMode( GL_BACK, GL_FILL );          // Back Face Is Filled In
	glPolygonMode( GL_FRONT, GL_LINE );         // Front Face Is Drawn With Lines

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);
	// Generate The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_11::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}
