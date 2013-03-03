/*
 * Sample_13.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: Andrew Zhabura
 */

#include "Sample_13.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cmath>

Sample_13::Sample_13()
:	m_base(0)
,	m_cnt1(0.0f)
,	m_cnt2(0.0f)
{
	/* Sotrage for 96 characters */
	m_base = glGenLists( LIST_SZ );

	buildFont();
}

Sample_13::~Sample_13()
{
	glDeleteLists( m_base, LIST_SZ );
}

void Sample_13::reshape(int w, int h)
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

void Sample_13::draw()
{
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity( );

	/* Move into the screen 1 unit */
	glTranslatef( 0.0f, 0.0f, -1.0f );

	/* Pulsing Colors Based On Text Position */
	glColor3f( 1.0f *( float )cos( m_cnt1 ),
			1.0f *( float )sin( m_cnt2 ),
			1.0f - 0.5f * ( float )cos( m_cnt1 + m_cnt2 ) );

	/* Position The Text On The Screen */
	glRasterPos2f( -0.45f + 0.05f * ( float )cos( m_cnt1 ),
			0.35f * ( float )sin( m_cnt2 ) );

	/* Print text to the screen */
	glPrint( "Active OpenGL Text With NeHe - %7.2f", m_cnt1 );

	m_cnt1 += 0.051f; /* Increase the first counter */
	m_cnt2 += 0.005f; /* Increase the second counter */
}

void Sample_13::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)

	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the background black */
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	glClearDepth( 1.0f );

	/* Enables Depth Testing */
	glEnable( GL_DEPTH_TEST );

	/* The Type Of Depth Test To Do */
	glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_13::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

/* function to build our font list */
void Sample_13::buildFont()
{
	Display *dpy;          /* Our current X display */
	XFontStruct *fontInfo; /* Our font info */

	/* Get our current display long enough to get the fonts */
	dpy = XOpenDisplay( NULL );

	/* Get the font information */
	fontInfo = XLoadQueryFont( dpy, "-adobe-helvetica-medium-r-normal--18-*-*-*-p-*-iso8859-1" );

	/* If the above font didn't exist try one that should */
	if ( fontInfo == NULL )
	{
		fontInfo = XLoadQueryFont( dpy, "fixed" );
		/* If that font doesn't exist, something is wrong */
		if ( fontInfo == NULL )
		{
			fprintf( stderr, "no X font available?\n" );
		}
	}

	/* generate the list */
	glXUseXFont( fontInfo->fid, FIRST_SYMBOL, LIST_SZ, m_base );

	/* Recover some memory */
	XFreeFont( dpy, fontInfo );

	/* close the display now that we're done with it */
	XCloseDisplay( dpy );
}

void Sample_13::glPrint( const char *fmt, ... )
{
	char text[256]; /* Holds our string */
	va_list ap;     /* Pointer to our list of elements */

	/* If there's no text, do nothing */
	if ( fmt == NULL )
		return;

	/* Parses The String For Variables */
	va_start( ap, fmt );
	/* Converts Symbols To Actual Numbers */
	vsprintf( text, fmt, ap );
	va_end( ap );

	/* Pushes the Display List Bits */
	glPushAttrib( GL_LIST_BIT );

	/* Sets base character to 32 */
	glListBase( m_base - FIRST_SYMBOL );

	/* Draws the text */
	glCallLists( strlen( text ), GL_UNSIGNED_BYTE, text );

	/* Pops the Display List Bits */
	glPopAttrib( );
}
