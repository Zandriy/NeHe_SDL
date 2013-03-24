/*
 * Sample_24.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Andrew Zhabura
 */

#include "Sample_24.h"

#include <SDL/SDL.h>

Sample_24::Sample_24()
:	m_base(0)
,	m_sWidth(0)
,	m_sHeight(0)
,	m_scroll(0)
,	m_maxtokens(0)
{
	m_imageFont.loadTGA( "data/font.tga" );
	glGenTextures(TEX_QTY, &m_texture[TEX_1]);

	/* Storage for 256 characters */
	m_base = glGenLists( LIST_SZ );

	buildFont();
}

Sample_24::~Sample_24()
{
	glDeleteLists( m_base, LIST_SZ );
}

void Sample_24::reshape(int w, int h)
{
	m_sWidth=w;                                   // Set Scissor Width To Window Width
	m_sHeight=h;                                 // Set Scissor Height To Window Height
	if (h==0)                                  // Prevent A Divide By Zero By
	{
		h=1;                               // Making Height Equal One
	}
	glViewport(0,0,w,h);                           // Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);                            // Select The Projection Matrix
	glLoadIdentity();                               // Reset The Projection Matrix
	glOrtho(0.0f,640,480,0.0f,-1.0f,1.0f);                      // Create Ortho 640x480 View (0,0 At Top Left)
	glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
	glLoadIdentity();                               // Reset The Modelview Matrix
}

void Sample_24::draw()
{
	char    *token;                                 // Storage For Our Token
	int cnt=0;                                  // Local Counter Variable

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);             // Clear Screen And Depth Buffer

	glColor3f(1.0f,0.5f,0.5f);                          // Set Color To Bright Red
	glPrint(50,16,1,"Renderer");                            // Display Renderer
	glPrint(80,48,1,"Vendor");                          // Display Vendor Name
	glPrint(66,80,1,"Version");                         // Display Version

	glColor3f(1.0f,0.7f,0.4f);                          // Set Color To Orange
	glPrint(200,16,1,(char *)glGetString(GL_RENDERER));             // Display Renderer
	glPrint(200,48,1,(char *)glGetString(GL_VENDOR));               // Display Vendor Name
	glPrint(200,80,1,(char *)glGetString(GL_VERSION));              // Display Version

	glColor3f(0.5f,0.5f,1.0f);                          // Set Color To Bright Blue
	glPrint(192,432,1,"NeHe Productions");                      // Write NeHe Productions At The Bottom Of The Screen

	glLoadIdentity();                               // Reset The ModelView Matrix
	glColor3f(1.0f,1.0f,1.0f);                          // Set The Color To White
	glBegin(GL_LINE_STRIP);                             // Start Drawing Line Strips (Something New)
	glVertex2d(639,417);                            // Top Right Of Bottom Box
	glVertex2d(  0,417);                            // Top Left Of Bottom Box
	glVertex2d(  0,480);                            // Lower Left Of Bottom Box
	glVertex2d(639,480);                            // Lower Right Of Bottom Box
	glVertex2d(639,128);                            // Up To Bottom Right Of Top Box
	glEnd();                                    // Done First Line Strip
	glBegin(GL_LINE_STRIP);                             // Start Drawing Another Line Strip
	glVertex2d(  0,128);                            // Bottom Left Of Top Box
	glVertex2d(639,128);                            // Bottom Right Of Top Box
	glVertex2d(639,  1);                            // Top Right Of Top Box
	glVertex2d(  0,  1);                            // Top Left Of Top Box
	glVertex2d(  0,417);                            // Down To Top Left Of Bottom Box
	glEnd();                                    // Done Second Line Strip

	glScissor(1 ,int(0.135416f*m_sHeight),m_sWidth-2,int(0.597916f*m_sHeight));   // Define Scissor Region
	glEnable(GL_SCISSOR_TEST);                          // Enable Scissor Testing

	char* text=(char*)malloc(strlen((char *)glGetString(GL_EXTENSIONS))+1);     // Allocate Memory For Our Extension String
	strcpy (text,(char *)glGetString(GL_EXTENSIONS));               // Grab The Extension List, Store In Text

	token=strtok(text," ");                             // Parse 'text' For Words, Seperated By " " (spaces)
	while(token!=NULL)                              // While The Token Isn't NULL
	{
		cnt++;                                  // Increase The Counter
		if (cnt>m_maxtokens)                           // Is 'maxtokens' Less Than 'cnt'
		{
			m_maxtokens=cnt;                          // If So, Set 'maxtokens' Equal To 'cnt'
		}
		glColor3f(0.5f,1.0f,0.5f);                      // Set Color To Bright Green
		glPrint(0,96+(cnt*32)-m_scroll,0,"%i",cnt);               // Print Current Extension Number
		glColor3f(1.0f,1.0f,0.5f);                      // Set Color To Yellow
		glPrint(50,96+(cnt*32)-m_scroll,0,token);                 // Print The Current Token (Parsed Extension Name)
		token=strtok(NULL," ");                         // Search For The Next Token
	}

	glDisable(GL_SCISSOR_TEST);                         // Disable Scissor Testing
	free (text);                                    // Free Allocated Memory
}

void Sample_24::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)

	loadTexture();
	buildFont();                                    // Build The Font

	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                       // Black Background
	glClearDepth(1.0f);                             // Depth Buffer Setup
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);                // Select Our Font Texture

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)
}

void Sample_24::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_24::loadTexture()
{
	GLuint   type=GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);                 // Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);       // Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);       // Linear Filtered

	if (m_imageFont.bpp()==24)                             // Was The TGA 24 Bits
	{
		type=GL_RGB;                                // If So Set The 'type' To GL_RGB
	}
	glTexImage2D(GL_TEXTURE_2D, 0, type, m_imageFont.sizeX(), m_imageFont.sizeY(), 0, type, GL_UNSIGNED_BYTE, m_imageFont.data() );
}

/* function to build our font list */
void Sample_24::buildFont()
{                               // Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);                // Select Our Font Texture
	for (int loop=0; loop<LIST_SZ; loop++)                        // Loop Through All 256 Lists
	{
		float cx=float(loop%16)/16.0f;                     // X Position Of Current Character
		float cy=float(loop/16)/16.0f;                     // Y Position Of Current Character

		glNewList(m_base+loop,GL_COMPILE);                   // Start Building A List
		glBegin(GL_QUADS);                      // Use A Quad For Each Character
		glTexCoord2f(cx,1.0f-cy-0.0625f);           // Texture Coord (Bottom Left)
		glVertex2d(0,16);                   // Vertex Coord (Bottom Left)
		glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);       // Texture Coord (Bottom Right)
		glVertex2i(16,16);                  // Vertex Coord (Bottom Right)
		glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);        // Texture Coord (Top Right)
		glVertex2i(16,0);                   // Vertex Coord (Top Right)
		glTexCoord2f(cx,1.0f-cy-0.001f);            // Texture Coord (Top Left)
		glVertex2i(0,0);                    // Vertex Coord (Top Left)
		glEnd();                            // Done Building Our Quad (Character)
		glTranslated(14,0,0);                       // Move To The Right Of The Character
		glEndList();                                // Done Building The Display List
	}                                       // Loop Until All 256 Are Built
}

void Sample_24::glPrint( GLint x, GLint y, int set, const char *fmt, ... )
{
	char    text[1024];                             // Holds Our String
	va_list ap;                                 // Pointer To List Of Arguments

	if (fmt == NULL)                                // If There's No Text
		return;                                 // Do Nothing

	va_start(ap, fmt);                              // Parses The String For Variables
	vsprintf(text, fmt, ap);                            // And Converts Symbols To Actual Numbers
	va_end(ap);                                 // Results Are Stored In Text

	if (set>1)                                   // Did User Choose An Invalid Character Set?
	{
		set=1;                                  // If So, Select Set 1 (Italic)
	}

	glEnable(GL_TEXTURE_2D);                            // Enable Texture Mapping
	glLoadIdentity();                               // Reset The Modelview Matrix
	glTranslated(x,y,0);                                // Position The Text (0,0 - Top Left)
	glListBase(m_base-FIRST_SYMBOL+(LIST_SZ/2*set));                          // Choose The Font Set (0 or 1)

	glScalef(1.0f,2.0f,1.0f);                           // Make The Text 2X Taller

	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);               // Write The Text To The Screen
	glDisable(GL_TEXTURE_2D);                           // Disable Texture Mapping
}

bool Sample_24::sendMessage(int message, int mode, int x, int y)
{
	switch (message) {
	case SDLK_UP:
		if (m_scroll > 0)
			m_scroll-=10;
		break;
	case SDLK_DOWN:
		if (m_scroll<32*(m_maxtokens-9))
			m_scroll+=10;
		break;
	default:
		return false;
		break;
	}

	return true;
}

