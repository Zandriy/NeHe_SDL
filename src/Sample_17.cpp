/*
 * Sample_17.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: Andrew Zhabura
 */

#include "Sample_17.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cmath>

Sample_17::Sample_17()
:	m_base(0)
,	m_cnt1(0.0f)
,	m_cnt2(0.0f)
{
	m_imageFont.loadBMP( "data/font.bmp" );
	m_imagePict.loadBMP( "data/bumps.bmp" );

	glGenTextures(TEX_QTY, &m_texture[0]);                  // Create Two Texture

	/* Storage for 96 characters */
	m_base = glGenLists( LIST_SZ );
}

Sample_17::~Sample_17()
{
	glDeleteLists( m_base, LIST_SZ );
}

void Sample_17::reshape(int w, int h)
{
	/* w / width ration */
	GLfloat ratio;

	/* Protect against a divide by zero */
	if ( h == 0 )
		h = 1;

	ratio = ( GLfloat )w / ( GLfloat )h;

	/* Setup our viewport. */
	glViewport( 0, 0, ( GLint )w, ( GLint )h );

	/* change to the projection matrix and set our viewing volume. */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	/* Set our perspective */
	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode( GL_MODELVIEW );

	/* Reset The View */
	glLoadIdentity( );
}

void Sample_17::draw()
{
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLoadIdentity( );

    /* Select Our Second Texture */
    glBindTexture( GL_TEXTURE_2D, m_texture[1] );
    /* Move Into The Screen 5 Units */
    glTranslatef( 0.0f, 0.0f, -5.0f );
    /* Rotate On The Z Axis 45 Degrees (Clockwise) */
    glRotatef( 45.0f, 0.0f, 0.0f, 1.0f );
    /* Rotate On The X & Y Axis By cnt1 (Left To Right) */
    glRotatef( m_cnt1 * 30.0f, 1.0f, 1.0f, 0.0f );

    /* Disable Blending Before We Draw In 3D */
    glDisable( GL_BLEND );
    glColor3f( 1.0f, 1.0f, 1.0f ); /* Bright White                       */
    glBegin( GL_QUADS );           /* Draw Our First Texture Mapped Quad */
      glTexCoord2d( 0.0f,  0.0f ); /* First Texture Coord                */
      glVertex2f(  -1.0f,  1.0f ); /* First Vertex                       */
      glTexCoord2d( 1.0f,  0.0f ); /* Second Texture Coord               */
      glVertex2f(   1.0f,  1.0f ); /* Second Vertex                      */
      glTexCoord2d( 1.0f,  1.0f ); /* Third Texture Coord                */
      glVertex2f(   1.0f, -1.0f ); /* Third Vertex                       */
      glTexCoord2d( 0.0f,  1.0f ); /* Fourth Texture Coord               */
      glVertex2f(  -1.0f, -1.0f ); /* Fourth Vertex                      */
    glEnd( );

    /* Rotate On The X & Y Axis By 90 Degrees (Left To Right) */
    glRotatef( 90.0f, 1.0f, 1.0f, 0.0f );
    glBegin( GL_QUADS );           /* Draw Our Second Texture Mapped Quad */
      glTexCoord2d( 0.0f,  0.0f ); /* First Texture Coord                 */
      glVertex2f(  -1.0f,  1.0f ); /* First Vertex                        */
      glTexCoord2d( 1.0f,  0.0f ); /* Second Texture Coord                */
      glVertex2f(   1.0f,  1.0f ); /* Second Vertex                       */
      glTexCoord2d( 1.0f,  1.0f ); /* Third Texture Coord                 */
      glVertex2f(   1.0f, -1.0f ); /* Third Vertex                        */
      glTexCoord2d( 0.0f,  1.0f ); /* Fourth Texture Coord                */
      glVertex2f(  -1.0f, -1.0f ); /* Fourth Vertex                       */
    glEnd( );

    /* Re-enable Blending */
    glEnable( GL_BLEND );
    /* Reset the view */
    glLoadIdentity( );


    /* Pulsing Colors Based On Text Position */
    /* Print GL Text To The Screen */
    glColor3f( 1.0f * ( float )cos( m_cnt1 ),
	       1.0f * ( float )sin( m_cnt2 ),
	       1.0f - 0.5f * ( float )cos( m_cnt1 + m_cnt2 ) );
    glPrint( ( int )( 280 + 250 * cos( m_cnt1 ) ),
	     ( int )( 235 + 200 * sin( m_cnt2 ) ),
	     (char*)&"NeHe", 0 );
    glColor3f( 1.0f * ( float )sin( m_cnt2 ),
	       1.0f - 0.5f * ( float )cos( m_cnt1 + m_cnt2 ),
	       1.0f * ( float )cos( m_cnt1 ) );
    glPrint( ( int )( 280 + 230 * cos( m_cnt2 ) ),
	     ( int )( 235 + 200 * sin( m_cnt1 ) ),
	     (char*)&"OpenGL", 1 );

    /* Set Color to Red */
    glColor3f( 0.0f, 0.0f, 1.0f );
    /* Draw Text To The Screen */
    glPrint( ( int )( 240 + 200 * cos( ( m_cnt2 + m_cnt1 ) / 5 ) ), 2,
    		(char*)&"Giuseppe D'Agata", 0 );

    /* Set Color To White */
    glColor3f( 1.0f, 1.0f, 1.0f );
    /* Draw Offset Text To The Screen */
    glPrint( ( int )( 242 + 200 * cos( ( m_cnt2 + m_cnt1 ) / 5 ) ), 2,
    		(char*)&"Giuseppe D'Agata", 0 );

    m_cnt1 += 0.01f;   /* Increase The First Counter  */
    m_cnt2 += 0.0081f; /* Increase The Second Counter */

}

void Sample_17::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)

    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Select The Type Of Blending */
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    /* Enable 2D Texture Mapping */
    glEnable( GL_TEXTURE_2D );

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)

	// Build All The Textures
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_imageFont.sizeY(), m_imageFont.sizeY(), 0, GL_RGB,
			GL_UNSIGNED_BYTE, m_imageFont.data() );

	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_imagePict.sizeY(), m_imagePict.sizeY(), 0, GL_RGB,
			GL_UNSIGNED_BYTE, m_imagePict.data() );

	buildFont();
}

void Sample_17::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

/* function to build our font list */
void Sample_17::buildFont()
{
	GLuint loop; /* Loop variable               */
	float cx;    /* Holds Our X Character Coord */
	float cy;    /* Holds Our Y Character Coord */

	/* Select Our Font Texture */
	glBindTexture( GL_TEXTURE_2D, m_texture[0] );

	/* Loop Through All 256 Lists */
	for ( loop = 0; loop < LIST_SZ; loop++ )
	{
		/* NOTE:
		 *  BMPs are stored with the top-leftmost pixel being the
		 * last byte and the bottom-rightmost pixel being the first
		 * byte. So an image that is displayed as
		 *    1 0
		 *    0 0
		 * is represented data-wise like
		 *    0 0
		 *    0 1
		 * And because SDL_LoadBMP loads the raw data without
		 * translating to how it is thought of when viewed we need
		 * to start at the bottom-right corner of the data and work
		 * backwards to get everything properly. So the below code has
		 * been modified to reflect this. Examine how this is done and
		 * how the original tutorial is done to grasp the differences.
		 *
		 * As a side note BMPs are also stored as BGR instead of RGB
		 * and that is why we load the texture using GL_BGR. It's
		 * bass-ackwards I know but whattaya gonna do?
		 */

		/* X Position Of Current Character */
		cx = 1 - ( float )( loop % 16 ) / 16.0f;
		/* Y Position Of Current Character */
		cy = 1 - ( float )( loop / 16 ) / 16.0f;

		/* Start Building A List */
		glNewList( m_base + ( LIST_SZ - loop ), GL_COMPILE );
		/* Use A Quad For Each Character */
		glBegin( GL_QUADS );
		/* Texture Coord (Bottom Left) */
		glTexCoord2f( cx - 0.0625, cy );
		/* Vertex Coord (Bottom Left) */
		glVertex2i( 0, 0 );

		/* Texture Coord (Bottom Right) */
		glTexCoord2f( cx, cy );
		/* Vertex Coord (Bottom Right) */
		glVertex2i( 16, 0 );

		/* Texture Coord (Top Right) */
		glTexCoord2f( cx, cy - 0.0625f );
		/* Vertex Coord (Top Right) */
		glVertex2i( 16, 16 );

		/* Texture Coord (Top Left) */
		glTexCoord2f( cx - 0.0625f, cy - 0.0625f);
		/* Vertex Coord (Top Left) */
		glVertex2i( 0, 16 );
		glEnd( );

		/* Move To The Left Of The Character */
		glTranslated( 10, 0, 0 );
		glEndList( );
	}
}

/* Function to print the string */
void Sample_17::glPrint( GLint x, GLint y, char *string, int set )
{
    if ( set > 1 )
	set = 1;

    /* Select our texture */
    glBindTexture( GL_TEXTURE_2D, m_texture[0] );

    /* Disable depth testing */
    glDisable( GL_DEPTH_TEST );

    /* Select The Projection Matrix */
    glMatrixMode( GL_PROJECTION );
    /* Store The Projection Matrix */
    glPushMatrix( );

    /* Reset The Projection Matrix */
    glLoadIdentity( );
    /* Set Up An Ortho Screen */
    glOrtho( 0, 640, 0, 480, -1, 1 );

    /* Select The Modelview Matrix */
    glMatrixMode( GL_MODELVIEW );
    /* Store the Modelview Matrix */
    glPushMatrix( );
    /* Reset The Modelview Matrix */
    glLoadIdentity( );

    /* Position The Text (0,0 - Bottom Left) */
    glTranslated( x, y, 0 );

    /* Choose The Font Set (0 or 1) */
    glListBase( m_base - FIRST_SYMBOL + ( LIST_SZ/2 * set ) );

    /* Write The Text To The Screen */
    glCallLists( strlen( string ), GL_BYTE, string );

    /* Select The Projection Matrix */
    glMatrixMode( GL_PROJECTION );
    /* Restore The Old Projection Matrix */
    glPopMatrix( );

    /* Select the Modelview Matrix */
    glMatrixMode( GL_MODELVIEW );
    /* Restore the Old Projection Matrix */
    glPopMatrix( );

    /* Re-enable Depth Testing */
    glEnable( GL_DEPTH_TEST );
}
