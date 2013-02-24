/*
 * Sample_10.cpp
 *
 *  Created on: Feb 24, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_10.h"

#include <SDL/SDL.h>
#include <cmath>

Sample_10::Sample_10()
:	m_blend(false)
,	m_heading(0.0f)
,	m_xpos(0.0f)
,	m_zpos(0.0f)
,	m_yrot(0.0f)
,	m_walkbias(0.0f)
,	m_walkbiasangle(0.0f)
,	m_lookupdown(0.0f)
,	m_z(0.0f)
,	m_filter(NEAREST_FILTER)
,	m_useSDLImage(false)
,	m_piover180 (0.0174532925f)
{
	for (int i = 0; i < TEX_QTY; ++i)
	{
		m_texture[i] = 0;
	}
	m_imageSDL = SDL_LoadBMP( "data/mud.bmp" );
	m_image.loadBMP( "data/mud.bmp" );
}

Sample_10::~Sample_10()
{
	delete [] m_texture;
	SDL_FreeSurface(m_imageSDL);
}

void Sample_10::reshape(int width, int height)
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
	// Make sure we're changing the model view and not the projection
	glMatrixMode( GL_MODELVIEW );
	// Reset The View
	glLoadIdentity( );
}

void Sample_10::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View

	GLfloat x_m, y_m, z_m, u_m, v_m;
	GLfloat xtrans = -m_xpos;
	GLfloat ztrans = -m_zpos;
	GLfloat ytrans = -m_walkbias-0.25f;
	GLfloat sceneroty = 360.0f - m_yrot;

	int numtriangles;

	glRotatef(m_lookupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);

	glTranslatef(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, m_texture[m_filter]);

	numtriangles = m_sector.numtriangles;

	// Process Each Triangle
	for (int loop_m = 0; loop_m < numtriangles; loop_m++)
	{
		glBegin(GL_TRIANGLES);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		x_m = m_sector.triangle[loop_m].vertex[0].x;
		y_m = m_sector.triangle[loop_m].vertex[0].y;
		z_m = m_sector.triangle[loop_m].vertex[0].z;
		u_m = m_sector.triangle[loop_m].vertex[0].u;
		v_m = m_sector.triangle[loop_m].vertex[0].v;
		glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);

		x_m = m_sector.triangle[loop_m].vertex[1].x;
		y_m = m_sector.triangle[loop_m].vertex[1].y;
		z_m = m_sector.triangle[loop_m].vertex[1].z;
		u_m = m_sector.triangle[loop_m].vertex[1].u;
		v_m = m_sector.triangle[loop_m].vertex[1].v;
		glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);

		x_m = m_sector.triangle[loop_m].vertex[2].x;
		y_m = m_sector.triangle[loop_m].vertex[2].y;
		z_m = m_sector.triangle[loop_m].vertex[2].z;
		u_m = m_sector.triangle[loop_m].vertex[2].u;
		v_m = m_sector.triangle[loop_m].vertex[2].v;
		glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
		glEnd();
	}
}

void Sample_10::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Transparency
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// This Will Clear The Background Color To Black
	glClearDepth(1.0);									// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glShadeModel(GL_SMOOTH);							// Enables Smooth Color Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)


	if (m_texture[NEAREST_FILTER] == 0)
	{
		glGenTextures(TEX_QTY, &m_texture[NEAREST_FILTER]);                  // Create The Textures
		setupWorld();
	}

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[NEAREST_FILTER]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	if (m_useSDLImage)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_imageSDL->w, m_imageSDL->h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageSDL->pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[LINEAR_FILTER]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	if (m_useSDLImage)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_imageSDL->w, m_imageSDL->h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageSDL->pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[MIPMAPPED_FILTER]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	if (m_useSDLImage)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_imageSDL->w, m_imageSDL->h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageSDL->pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_image.sizeY(), m_image.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data() );

}

void Sample_10::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_10::sendMessage(int message, int mode, int x, int y)
{
	switch (message) {
	case SDLK_b:
		m_blend=!m_blend;
		if (!m_blend)
		{
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
		}
		break;
	case SDLK_f:
		m_filter+=1;              // filter Value Increases By One
		if (m_filter>=TEX_QTY)    // Is Value Greater Than 2?
			m_filter=NEAREST_FILTER;           // If So, Set filter To 0
		if (m_filter == NEAREST_FILTER)
			printf("Nearest Filtered Texture\n");
		if (m_filter == LINEAR_FILTER)
			printf("Linear Filtered Texture\n");
		if (m_filter == MIPMAPPED_FILTER)
			printf("MipMapped Filtered Texture\n");
		break;
	case SDLK_s:
		m_useSDLImage=!m_useSDLImage;
		if (m_useSDLImage)
			printf("SDLImage is in use\n");
		else
			printf("OGLImageRec is in use\n");
		break;
	case SDLK_PAGEUP:
		m_z-=0.2f;
		m_lookupdown-= 1.0f;
		break;
	case SDLK_PAGEDOWN:
		m_z+=0.2f;
		m_lookupdown+= 1.0f;
		break;
	case SDLK_UP:
		m_xpos -= (float)sin(m_heading*m_piover180) * 0.05f;
		m_zpos -= (float)cos(m_heading*m_piover180) * 0.05f;
		if (m_walkbiasangle >= 359.0f)
		{
			m_walkbiasangle = 0.0f;
		}
		else
		{
			m_walkbiasangle+= 10;
		}
		m_walkbias = (float)sin(m_walkbiasangle * m_piover180)/20.0f;
		break;
	case SDLK_DOWN:
		m_xpos += (float)sin(m_heading*m_piover180) * 0.05f;
		m_zpos += (float)cos(m_heading*m_piover180) * 0.05f;
		if (m_walkbiasangle <= 1.0f)
		{
			m_walkbiasangle = 359.0f;
		}
		else
		{
			m_walkbiasangle-= 10;
		}
		m_walkbias = (float)sin(m_walkbiasangle * m_piover180)/20.0f;
		break;
	case SDLK_LEFT:
		m_heading += 1.0f;
		m_yrot = m_heading;
		break;
	case SDLK_RIGHT:
		m_heading -= 1.0f;
		m_yrot = m_heading;
		break;
	default:
		return false;
		break;
	}

	drawGLScene();
	return true;
}


void Sample_10::readStr(FILE *f,char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}

void Sample_10::setupWorld()
{
	float x, y, z, u, v;
	int numtriangles;
	FILE *filein;
	char oneline[255];
	filein = fopen("data/world.txt", "rt");				// File To Load World Data From

	readStr(filein,oneline);
	sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);

	m_sector.triangle = new TRIANGLE[numtriangles];
	m_sector.numtriangles = numtriangles;
	for (int loop = 0; loop < numtriangles; loop++)
	{
		for (int vert = 0; vert < 3; vert++)
		{
			readStr(filein,oneline);
			sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
			m_sector.triangle[loop].vertex[vert].x = x;
			m_sector.triangle[loop].vertex[vert].y = y;
			m_sector.triangle[loop].vertex[vert].z = z;
			m_sector.triangle[loop].vertex[vert].u = u;
			m_sector.triangle[loop].vertex[vert].v = v;
		}
	}
	fclose(filein);
	return;
}
