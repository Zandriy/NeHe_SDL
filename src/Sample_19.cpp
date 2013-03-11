/*
 * Sample_19.cpp
 *
 *  Created on: Mar 6, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_19.h"

#include <SDL/SDL.h>

GLfloat Sample_19::s_colors[COL_QTY][COL_RGB]=               // Rainbow Of Colors
{
    {1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
    {0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
    {0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

Sample_19::Sample_19()
:	m_rainbow(true)
,	m_slowdown(2.0f)
,	m_xspeed(0.0f)
,	m_yspeed(0.0f)
,	m_zoom(-40.0f)
,	m_col(0)
,	m_delay(0)
,	m_loop(0)
{
	for (int i = 0; i < TEX_QTY; ++i)
	{
		m_texture[i] = 0;
	}
	m_image.loadBMP( "data/particle.bmp" );

	for (;m_loop<MAX_PARTICLES;m_loop++)                   // Initialize All The Textures
	{
	    m_particle[m_loop].active=true;                 // Make All The Particles Active
	    m_particle[m_loop].life=1.0f;                   // Give All The Particles Full Life
	    m_particle[m_loop].fade=float(rand()%100)/1000.0f+0.003f;       // Random Fade Speed
	    m_particle[m_loop].r=s_colors[m_loop*(12/MAX_PARTICLES)][0];        // Select Red Rainbow Color
	    m_particle[m_loop].g=s_colors[m_loop*(12/MAX_PARTICLES)][1];        // Select Red Rainbow Color
	    m_particle[m_loop].b=s_colors[m_loop*(12/MAX_PARTICLES)][2];        // Select Red Rainbow Color
	    m_particle[m_loop].xi=float((rand()%50)-26.0f)*10.0f;       // Random Speed On X Axis
	    m_particle[m_loop].yi=float((rand()%50)-25.0f)*10.0f;       // Random Speed On Y Axis
	    m_particle[m_loop].zi=float((rand()%50)-25.0f)*10.0f;       // Random Speed On Z Axis
        m_particle[m_loop].xg=0.0f;                     // Set Horizontal Pull To Zero
        m_particle[m_loop].yg=-0.8f;                    // Set Vertical Pull Downward
        m_particle[m_loop].zg=0.0f;                     // Set Pull On Z Axis To Zero
    }                                // Initialization Went OK
}

Sample_19::~Sample_19()
{
	delete [] m_texture;
}

void Sample_19::reshape(int width, int height)
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

void Sample_19::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer
    glLoadIdentity();                           // Reset The ModelView Matrix

    for (m_loop=0;m_loop<MAX_PARTICLES;m_loop++)                   // Loop Through All The Particles
    {
    	if (m_particle[m_loop].active)                  // If The Particle Is Active
    	{
    		float x=m_particle[m_loop].x;               // Grab Our Particle X Position
    		float y=m_particle[m_loop].y;               // Grab Our Particle Y Position
    		float z=m_particle[m_loop].z+m_zoom;              // Particle Z Pos + Zoom

    		// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
    		glColor4f(m_particle[m_loop].r,m_particle[m_loop].g,m_particle[m_loop].b,m_particle[m_loop].life);

    		glBegin(GL_TRIANGLE_STRIP);             // Build Quad From A Triangle Strip
    		glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
    		glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
    		glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
    		glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
    		glEnd();                        // Done Building Triangle Strip

    		m_particle[m_loop].x+=m_particle[m_loop].xi/(m_slowdown*1000);    // Move On The X Axis By X Speed
    		m_particle[m_loop].y+=m_particle[m_loop].yi/(m_slowdown*1000);    // Move On The Y Axis By Y Speed
    		m_particle[m_loop].z+=m_particle[m_loop].zi/(m_slowdown*1000);    // Move On The Z Axis By Z Speed
    		m_particle[m_loop].xi+=m_particle[m_loop].xg;           // Take Pull On X Axis Into Account
    		m_particle[m_loop].yi+=m_particle[m_loop].yg;           // Take Pull On Y Axis Into Account
    		m_particle[m_loop].zi+=m_particle[m_loop].zg;           // Take Pull On Z Axis Into Account
    		m_particle[m_loop].life-=m_particle[m_loop].fade;       // Reduce Particles Life By 'Fade'

    		if (m_particle[m_loop].life<0.0f)                    // If Particle Is Burned Out
    		{
    			m_particle[m_loop].life=1.0f;               // Give It New Life
    			m_particle[m_loop].fade=float(rand()%100)/1000.0f+0.003f;   // Random Fade Value
    			m_particle[m_loop].x=0.0f;                  // Center On X Axis
    			m_particle[m_loop].y=0.0f;                  // Center On Y Axis
    			m_particle[m_loop].z=0.0f;                  // Center On Z Axis
    			m_particle[m_loop].xi=m_xspeed+float((rand()%60)-32.0f);  // X Axis Speed And Direction
    			m_particle[m_loop].yi=m_yspeed+float((rand()%60)-30.0f);  // Y Axis Speed And Direction
    			m_particle[m_loop].zi=float((rand()%60)-30.0f);     // Z Axis Speed And Direction
    		    m_particle[m_loop].r=s_colors[m_col][0];            // Select Red From Color Table
    		    m_particle[m_loop].g=s_colors[m_col][1];            // Select Green From Color Table
    		    m_particle[m_loop].b=s_colors[m_col][2];            // Select Blue From Color Table
    		}
    	}
    }

    if (m_rainbow && (m_delay>25))   // Rainbow Mode
    {
		m_delay=0;            // Reset The Rainbow Color Cycling Delay
		m_col++;              // Change The Particle Color
		if (m_col>11) m_col=0;       // If Color Is To High Reset It
    }
    m_delay++;
}

void Sample_19::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if (m_texture[TEX_1] == 0)
		glGenTextures(TEX_QTY, &m_texture[TEX_1]);                  // Create The Texture

	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	glShadeModel(GL_SMOOTH);                        // Enables Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);                  // Black Background
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);                       // Disables Depth Testing
	glEnable(GL_BLEND);                         // Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);                   // Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);           // Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);                 // Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_19::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_19::sendMessage(int message, int mode, int x, int y)
{
	switch (message) {
	case SDLK_UP:
		if (m_particle[m_loop].yg<1.5f)
			m_particle[m_loop].yg+=0.01f;
		if (m_yspeed<200)
			m_yspeed+=1.0f;
		else
			m_yspeed-=1.0f;
		break;
	case SDLK_DOWN:
		if (m_particle[m_loop].yg>-1.5f)
			m_particle[m_loop].yg-=0.01f;
		if (m_xspeed<200)
			m_xspeed+=1.0f;
		else
			m_xspeed-=1.0f;
		break;
	case SDLK_RIGHT:
		if (m_particle[m_loop].xg<1.5f)
			m_particle[m_loop].xg+=0.01f;
		break;
	case SDLK_LEFT:
		if (m_particle[m_loop].xg>-1.5f)
			m_particle[m_loop].xg-=0.01f;
		break;
	case SDLK_TAB:
		m_particle[m_loop].x=0.0f;                  // Center On X Axis
		m_particle[m_loop].y=0.0f;                  // Center On Y Axis
		m_particle[m_loop].z=0.0f;                  // Center On Z Axis
		m_particle[m_loop].xi=float((rand()%50)-26.0f)*10.0f;   // Random Speed On X Axis
		m_particle[m_loop].yi=float((rand()%50)-25.0f)*10.0f;   // Random Speed On Y Axis
		m_particle[m_loop].zi=float((rand()%50)-25.0f)*10.0f;   // Random Speed On Z Axis
		break;
	case SDLK_PLUS:
		if (m_slowdown>1.0f) m_slowdown-=0.01f;        // Speed Up Particles
		break;
	case SDLK_MINUS:
		if (m_slowdown<4.0f) m_slowdown+=0.01f;   		// Slow Down Particles
		break;
	case SDLK_PAGEUP:
		m_zoom+=0.1f;     // Zoom In
		break;
	case SDLK_PAGEDOWN:
		m_zoom-=0.1f;      // Zoom Out
		break;
	case SDLK_RETURN:
		m_rainbow=!m_rainbow;       // Toggle Rainbow Mode On / Off
		break;
	case SDLK_SPACE:
		m_rainbow=false;   // If Spacebar Is Pressed Disable Rainbow Mode
		m_delay=0;            // Reset The Rainbow Color Cycling Delay
		m_col++;              // Change The Particle Color
		if (m_col>11) m_col=0;       // If Color Is To High Reset It
		break;
	default:
		return false;
		break;
	}

	drawGLScene();
	return true;
}
