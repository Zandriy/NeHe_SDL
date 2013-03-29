/*
 * Sample_22.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: Andrew Zhabura
 */


#include "Sample_22.h"
#include "OGLInspector.h"
#include "OGLImageRec.h"

#include <SDL/SDL.h>
#include <cmath>

#define MAX_EMBOSS (GLfloat)0.01f                       // Maximum Emboss-Translate. Increase To Get Higher Immersion
#define __ARB_ENABLE true                           // Used To Disable ARB Extensions Entirely
#define EXT_INFO                             // Uncomment To See Your Extensions At Start-Up?
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
,	m_xspeed(0.0f)
,	m_yspeed(0.0f)
,	m_z(-5.0f)
,	m_multitextureSupported(false)
,	m_useMultitexture(false)
,	m_emboss(false)
,	m_bumps(true)
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
		printf("The GL_ARB_multitexture extension will be used.\n");
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
	if (m_bumps) {
		if (m_useMultitexture && m_maxTexelUnits>1)
			doMesh2TexelUnits();
		else doMesh1TexelUnits();
	}
	else doMeshNoBumps();

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

#ifdef EXT_INFO
	if (m_useMultitexture)
		printf("The GL_ARB_multitexture extension will be used.\n");
	else
		printf("The GL_ARB_multitexture extension won't be used.\n");
#endif
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
	OGLImageRec	img;
	img.loadBMP( "data/Base.bmp" );

	if (m_texture[TEX_1] == 0)
		glGenTextures(TEX_QTY, &m_texture[TEX_1]);                  // Create Textures

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	// Generate The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img.sizeX(), img.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	// Generate The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img.sizeX(), img.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	// Generate The Texture
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, img.sizeX(), img.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	// Load The Bumpmaps
	img.loadBMP( "data/Bump.bmp" );

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img.sizeX(), img.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_bump[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img.sizeX(), img.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_bump[TEX_3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, img.sizeX(), img.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	for (int i=0; i<3*img.sizeX()*img.sizeY(); i++)		// Invert The Bumpmap
		img.data()[i]=255-img.data()[i];

	if (m_invbump[TEX_1] == 0)
		glGenTextures(TEX_QTY, &m_invbump[TEX_1]);	// Create Three Textures

	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_invbump[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img.sizeX(), img.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, m_invbump[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img.sizeX(), img.sizeY(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, m_invbump[TEX_3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, img.sizeX(), img.sizeY(), GL_RGB, GL_UNSIGNED_BYTE, img.data() );

	glPixelTransferf(GL_RED_SCALE,1.0f);				// Scale RGB Back To 100% Again
	glPixelTransferf(GL_GREEN_SCALE,1.0f);
	glPixelTransferf(GL_BLUE_SCALE,1.0f);

	// Load The Logo-Bitmaps
	img.loadBMP( "data/OpenGL_Alpha.bmp" );

	alpha=new char[4*img.sizeX()*img.sizeY()];		// Create Memory For RGBA-Texture
	for (int a=0; a<img.sizeX()*img.sizeY(); ++a)
		alpha[4*a+3]=img.data()[a*3];					// Pick Only Red Value As Alpha!

	img.loadBMP( "data/OpenGL.bmp");
	for (int a=0; a<img.sizeX()*img.sizeY(); a++) {
		alpha[4*a]=img.data()[a*3];					// R
		alpha[4*a+1]=img.data()[a*3+1];				// G
		alpha[4*a+2]=img.data()[a*3+2];				// B
	}

	if (m_glLogo == 0)
		glGenTextures(1, &m_glLogo);				// Create One Textures

	// Create Linear Filtered RGBA-Texture
	glBindTexture(GL_TEXTURE_2D, m_glLogo);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.sizeX(), img.sizeY(), 0, GL_RGBA, GL_UNSIGNED_BYTE, alpha );
	delete alpha;

	// Load The "Extension Enabled"-Logo
	img.loadBMP( "data/Multi_On_Alpha.bmp" );
	alpha=new char[4*img.sizeX()*img.sizeY()];		// Create Memory For RGBA-Texture
	for (int a=0; a<img.sizeX()*img.sizeY(); a++)
		alpha[4*a+3]=img.data()[a*3];					// Pick Only Red Value As Alpha!

	img.loadBMP( "data/Multi_On.bmp" );
	for (int a=0; a<img.sizeX()*img.sizeY(); a++) {
		alpha[4*a]=img.data()[a*3];					// R
		alpha[4*a+1]=img.data()[a*3+1];				// G
		alpha[4*a+2]=img.data()[a*3+2];				// B
	}

	if (m_multiLogo == 0)
		glGenTextures(1, &m_multiLogo);						// Create One Textures

	// Create Linear Filtered RGBA-Texture
	glBindTexture(GL_TEXTURE_2D, m_multiLogo);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.sizeX(), img.sizeY(), 0, GL_RGBA, GL_UNSIGNED_BYTE, alpha);
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

// Calculates v=vM, M Is 4x4 In Column-Major, v Is 4dim. Row (i.e. "Transposed")
void Sample_22::VMatMult(GLfloat *M, GLfloat *v) {
	GLfloat res[3];
	res[0]=M[ 0]*v[0]+M[ 1]*v[1]+M[ 2]*v[2]+M[ 3]*v[3];
	res[1]=M[ 4]*v[0]+M[ 5]*v[1]+M[ 6]*v[2]+M[ 7]*v[3];
	res[2]=M[ 8]*v[0]+M[ 9]*v[1]+M[10]*v[2]+M[11]*v[3];;
	v[0]=res[0];
	v[1]=res[1];
	v[2]=res[2];
	v[3]=M[15];											// Homogenous Coordinate
}

/*	Okay, Here Comes The Important Stuff:

	On http://www.nvidia.com/marketing/Developer/DevRel.nsf/TechnicalDemosFrame?OpenPage
	You Can Find A Demo Called GL_BUMP That Is A Little Bit More Complicated.
	GL_BUMP:   Copyright Diego T�rtara, 1999.
		     -  diego_tartara@ciudad.com.ar  -

	The Idea Behind GL_BUMP Is, That You Compute The Texture-Coordinate Offset As Follows:
		0) All Coordinates Either In Object Or In World Space.
		1) Calculate Vertex v From Actual Position (The Vertex You're At) To The Lightposition
		2) Normalize v
		3) Project This v Into Tangent Space.
			Tangent Space Is The Plane "Touching" The Object In Our Current Position On It.
			Typically, If You're Working With Flat Surfaces, This Is The Surface Itself.
		4) Offset s,t-Texture-Coordinates By The Projected v's x And y-Component.

	* This Would Be Called Once Per Vertex In Our Geometry, If Done Correctly.
	* This Might Lead To Incoherencies In Our Texture Coordinates, But Is Ok As Long As You Did Not
	* Wrap The Bumpmap.

	Basically, We Do It The Same Way With Some Exceptions:
		ad 0) We'll Work In Object Space All Time. This Has The Advantage That We'll Only
		      Have To Transform The Lightposition From Frame To Frame. This Position Obviously
			  Has To Be Transformed Using The Inversion Of The Modelview Matrix. This Is, However,
			  A Considerable Drawback, If You Don't Know How Your Modelview Matrix Was Built, Since
			  Inverting A Matrix Is Costly And Complicated.
		ad 1) Do It Exactly That Way.
		ad 2) Do It Exactly That Way.
		ad 3) To Project The Lightvector Into Tangent Space, We'll Support The Setup-Routine
			  With Two Directions: One Of Increasing s-Texture-Coordinate Axis, The Other In
			  Increasing t-Texture-Coordinate Axis. The Projection Simply Is (Assumed Both
			  texCoord Vectors And The Lightvector Are Normalized) The Dotproduct Between The
			  Respective texCoord Vector And The Lightvector.
		ad 4) The Offset Is Computed By Taking The Result Of Step 3 And Multiplying The Two
			  Numbers With MAX_EMBOSS, A Constant That Specifies How Much Quality We're Willing To
			  Trade For Stronger Bump-Effects. Just Temper A Little Bit With MAX_EMBOSS!

	WHY THIS IS COOL:
		* Have A Look!
		* Very Cheap To Implement (About One Squareroot And A Couple Of MULs)!
		* Can Even Be Further Optimized!
		* SetUpBump Doesn't Disturb glBegin()/glEnd()
		* THIS DOES ALWAYS WORK - Not Only With XY-Tangent Spaces!!

	DRAWBACKS:
		* Must Know "Structure" Of Modelview-Matrix Or Invert It. Possible To Do The Whole Thing
		* In World Space, But This Involves One Transformation For Each Vertex!
*/

void Sample_22::SetUpBumps(GLfloat *n, GLfloat *c, GLfloat *l, GLfloat *s, GLfloat *t)
{
	GLfloat v[3];							// Vertex From Current Position To Light
	GLfloat lenQ;							// Used To Normalize

	// Calculate v From Current Vector c To Lightposition And Normalize v
	v[0]=l[0]-c[0];
	v[1]=l[1]-c[1];
	v[2]=l[2]-c[2];
	lenQ=(GLfloat) sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0]/=lenQ;		v[1]/=lenQ;		v[2]/=lenQ;
	// Project v Such That We Get Two Values Along Each Texture-Coordinat Axis.
	c[0]=(s[0]*v[0]+s[1]*v[1]+s[2]*v[2])*MAX_EMBOSS;
	c[1]=(t[0]*v[0]+t[1]*v[1]+t[2]*v[2])*MAX_EMBOSS;
}

void Sample_22::doLogo()
{			// MUST CALL THIS LAST!!!, Billboards The Two Logos.
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D,m_glLogo);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);	glVertex3f(0.23f, -0.4f,-1.0f);
		glTexCoord2f(1.0f,0.0f);	glVertex3f(0.53f, -0.4f,-1.0f);
		glTexCoord2f(1.0f,1.0f);	glVertex3f(0.53f, -0.25f,-1.0f);
		glTexCoord2f(0.0f,1.0f);	glVertex3f(0.23f, -0.25f,-1.0f);
	glEnd();
	if (m_useMultitexture) {
		glBindTexture(GL_TEXTURE_2D,m_multiLogo);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);	glVertex3f(-0.53f, -0.4f,-1.0f);
			glTexCoord2f(1.0f,0.0f);	glVertex3f(-0.33f, -0.4f,-1.0f);
			glTexCoord2f(1.0f,1.0f);	glVertex3f(-0.33f, -0.3f,-1.0f);
			glTexCoord2f(0.0f,1.0f);	glVertex3f(-0.53f, -0.3f,-1.0f);
		glEnd();
	}
	glDepthFunc(GL_LEQUAL);
}

bool Sample_22::doMesh1TexelUnits()
{
	GLfloat c[4]={0.0f,0.0f,0.0f,1.0f};					// Holds Current Vertex
	GLfloat n[4]={0.0f,0.0f,0.0f,1.0f};					// Normalized Normal Of Current Surface
	GLfloat s[4]={0.0f,0.0f,0.0f,1.0f};					// s-Texture Coordinate Direction, Normalized
	GLfloat t[4]={0.0f,0.0f,0.0f,1.0f};					// t-Texture Coordinate Direction, Normalized
	GLfloat l[4];										// Holds Our Lightposition To Be Transformed Into Object Space
	GLfloat Minv[16];									// Holds The Inverted Modelview Matrix To Do So.
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

	// Build Inverse Modelview Matrix First. This Substitutes One Push/Pop With One glLoadIdentity();
	// Simply Build It By Doing All Transformations Negated And In Reverse Order.
	glLoadIdentity();
	glRotatef(-m_yrot,0.0f,1.0f,0.0f);
	glRotatef(-m_xrot,1.0f,0.0f,0.0f);
	glTranslatef(0.0f,0.0f,-m_z);
	glGetFloatv(GL_MODELVIEW_MATRIX,Minv);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,m_z);

	glRotatef(m_xrot,1.0f,0.0f,0.0f);
	glRotatef(m_yrot,0.0f,1.0f,0.0f);

	// Transform The Lightposition Into Object Coordinates:
	l[0]=s_LightPosition[0];
	l[1]=s_LightPosition[1];
	l[2]=s_LightPosition[2];
	l[3]=1.0f;											// Homogenous Coordinate
	VMatMult(Minv,l);

/*	PASS#1: Use Texture "Bump"
			No Blend
			No Lighting
			No Offset Texture-Coordinates */
	glBindTexture(GL_TEXTURE_2D, m_bump[m_filter]);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	doCube();

/* PASS#2:	Use Texture "Invbump"
			Blend GL_ONE To GL_ONE
			No Lighting
			Offset Texture Coordinates
			*/
	glBindTexture(GL_TEXTURE_2D,m_invbump[m_filter]);
	glBlendFunc(GL_ONE,GL_ONE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
		// Front Face
		n[0]=0.0f;		n[1]=0.0f;		n[2]=1.0f;
		s[0]=1.0f;		s[1]=0.0f;		s[2]=0.0f;
		t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
		for (i=0; i<4; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glTexCoord2f(s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Back Face
		n[0]=0.0f;		n[1]=0.0f;		n[2]=-1.0f;
		s[0]=-1.0f;		s[1]=0.0f;		s[2]=0.0f;
		t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
		for (i=4; i<8; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glTexCoord2f(s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Top Face
		n[0]=0.0f;		n[1]=1.0f;		n[2]=0.0f;
		s[0]=1.0f;		s[1]=0.0f;		s[2]=0.0f;
		t[0]=0.0f;		t[1]=0.0f;		t[2]=-1.0f;
		for (i=8; i<12; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glTexCoord2f(s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Bottom Face
		n[0]=0.0f;		n[1]=-1.0f;		n[2]=0.0f;
		s[0]=-1.0f;		s[1]=0.0f;		s[2]=0.0f;
		t[0]=0.0f;		t[1]=0.0f;		t[2]=-1.0f;
		for (i=12; i<16; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glTexCoord2f(s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Right Face
		n[0]=1.0f;		n[1]=0.0f;		n[2]=0.0f;
		s[0]=0.0f;		s[1]=0.0f;		s[2]=-1.0f;
		t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
		for (i=16; i<20; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glTexCoord2f(s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Left Face
		n[0]=-1.0f;		n[1]=0.0f;		n[2]=0.0f;
		s[0]=0.0f;		s[1]=0.0f;		s[2]=1.0f;
		t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
		for (i=20; i<24; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glTexCoord2f(s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
	glEnd();

/* PASS#3:	Use Texture "Base"
			Blend GL_DST_COLOR To GL_SRC_COLOR (Multiplies By 2)
			Lighting Enabled
			No Offset Texture-Coordinates
			*/
	if (!m_emboss) {
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D,m_texture[m_filter]);
		glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);
		glEnable(GL_LIGHTING);
		doCube();
	}

	m_xrot+=m_xspeed;
	m_yrot+=m_yspeed;
	if (m_xrot>360.0f) m_xrot-=360.0f;
	if (m_xrot<0.0f) m_xrot+=360.0f;
	if (m_yrot>360.0f) m_yrot-=360.0f;
	if (m_yrot<0.0f) m_yrot+=360.0f;

/*	LAST PASS:	Do The Logos! */
	doLogo();

	return true;										// Keep Going
}

bool Sample_22::doMesh2TexelUnits()
{

	GLfloat c[4]={0.0f,0.0f,0.0f,1.0f};					// holds current vertex
	GLfloat n[4]={0.0f,0.0f,0.0f,1.0f};					// normalized normal of current surface
	GLfloat s[4]={0.0f,0.0f,0.0f,1.0f};					// s-texture coordinate direction, normalized
	GLfloat t[4]={0.0f,0.0f,0.0f,1.0f};					// t-texture coordinate direction, normalized
	GLfloat l[4];										// holds our lightposition to be transformed into object space
	GLfloat Minv[16];									// holds the inverted modelview matrix to do so.
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

	// Build Inverse Modelview Matrix First. This Substitutes One Push/Pop With One glLoadIdentity();
	// Simply Build It By Doing All Transformations Negated And In Reverse Order.
	glLoadIdentity();
	glRotatef(-m_yrot,0.0f,1.0f,0.0f);
	glRotatef(-m_xrot,1.0f,0.0f,0.0f);
	glTranslatef(0.0f,0.0f,-m_z);
	glGetFloatv(GL_MODELVIEW_MATRIX,Minv);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,m_z);

	glRotatef(m_xrot,1.0f,0.0f,0.0f);
	glRotatef(m_yrot,0.0f,1.0f,0.0f);

	// Transform The Lightposition Into Object Coordinates:
	l[0]=s_LightPosition[0];
	l[1]=s_LightPosition[1];
	l[2]=s_LightPosition[2];
	l[3]=1.0f;											// Homogenous Coordinate
	VMatMult(Minv,l);

/*	PASS#1: Texel-Unit 0:	Use Texture "Bump"
							No Blend
							No Lighting
							No Offset Texture-Coordinates
							Texture-Operation "Replace"
			Texel-Unit 1:	Use Texture "Invbump"
							No Lighting
							Offset Texture Coordinates
							Texture-Operation "Replace"
*/
	// TEXTURE-UNIT #0
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_bump[m_filter]);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
	// TEXTURE-UNIT #1:
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_invbump[m_filter]);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD);
	// General Switches:
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
		// Front Face
		n[0]=0.0f;		n[1]=0.0f;		n[2]=1.0f;
		s[0]=1.0f;		s[1]=0.0f;		s[2]=0.0f;
		t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
		for (i=0; i<4; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,s_data[5*i]     , s_data[5*i+1]);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Back Face
		n[0]=0.0f;		n[1]=0.0f;		n[2]=-1.0f;
		s[0]=-1.0f;		s[1]=0.0f;		s[2]=0.0f;
		t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
		for (i=4; i<8; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,s_data[5*i]     , s_data[5*i+1]);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Top Face
		n[0]=0.0f;		n[1]=1.0f;		n[2]=0.0f;
		s[0]=1.0f;		s[1]=0.0f;		s[2]=0.0f;
		t[0]=0.0f;		t[1]=0.0f;		t[2]=-1.0f;
		for (i=8; i<12; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,s_data[5*i]     , s_data[5*i+1]     );
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Bottom Face
		n[0]=0.0f;		n[1]=-1.0f;		n[2]=0.0f;
		s[0]=-1.0f;		s[1]=0.0f;		s[2]=0.0f;
		t[0]=0.0f;		t[1]=0.0f;		t[2]=-1.0f;
		for (i=12; i<16; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,s_data[5*i]     , s_data[5*i+1]     );
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Right Face
		n[0]=1.0f;		n[1]=0.0f;		n[2]=0.0f;
		s[0]=0.0f;		s[1]=0.0f;		s[2]=-1.0f;
		t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
		for (i=16; i<20; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,s_data[5*i]     , s_data[5*i+1]     );
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
		// Left Face
		n[0]=-1.0f;		n[1]=0.0f;		n[2]=0.0f;
		s[0]=0.0f;		s[1]=0.0f;		s[2]=1.0f;
		t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
		for (i=20; i<24; i++) {
			c[0]=s_data[5*i+2];
			c[1]=s_data[5*i+3];
			c[2]=s_data[5*i+4];
			SetUpBumps(n,c,l,s,t);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,s_data[5*i]     , s_data[5*i+1]     );
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,s_data[5*i]+c[0], s_data[5*i+1]+c[1]);
			glVertex3f(s_data[5*i+2], s_data[5*i+3], s_data[5*i+4]);
		}
	glEnd();

/* PASS#2	Use Texture "Base"
			Blend GL_DST_COLOR To GL_SRC_COLOR (Multiplies By 2)
			Lighting Enabled
			No Offset Texture-Coordinates
			*/
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	if (!m_emboss) {
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D,m_texture[m_filter]);
		glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);
		glEnable(GL_BLEND);
		glEnable(GL_LIGHTING);
		doCube();
	}

	m_xrot+=m_xspeed;
	m_yrot+=m_yspeed;
	if (m_xrot>360.0f) m_xrot-=360.0f;
	if (m_xrot<0.0f) m_xrot+=360.0f;
	if (m_yrot>360.0f) m_yrot-=360.0f;
	if (m_yrot<0.0f) m_yrot+=360.0f;

/* LAST PASS:	Do The Logos! */
	doLogo();

	return true;										// Keep Going
}

bool Sample_22::doMeshNoBumps()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glTranslatef(0.0f,0.0f,m_z);

	glRotatef(m_xrot,1.0f,0.0f,0.0f);
	glRotatef(m_yrot,0.0f,1.0f,0.0f);
	if (m_useMultitexture) {
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE0_ARB);
	}
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,m_texture[m_filter]);
	glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);
	glEnable(GL_LIGHTING);
	doCube();

	m_xrot+=m_xspeed;
	m_yrot+=m_yspeed;
	if (m_xrot>360.0f) m_xrot-=360.0f;
	if (m_xrot<0.0f) m_xrot+=360.0f;
	if (m_yrot>360.0f) m_yrot-=360.0f;
	if (m_yrot<0.0f) m_yrot+=360.0f;

/* LAST PASS:	Do The Logos! */
	doLogo();

	return true;										// Keep Going
}

bool Sample_22::sendMessage(int message, int mode, int x, int y)
{
	switch (message) {
	case SDLK_e:
		m_emboss=!m_emboss;
		break;
	case SDLK_m:
		m_useMultitexture=((!m_useMultitexture) && m_multitextureSupported);
		break;
	case SDLK_b:
		m_bumps=!m_bumps;
		break;
	case SDLK_f:
		m_filter++;
		m_filter%=3;
		break;
	case SDLK_PAGEUP:
		m_z-=0.02f;
		break;
	case SDLK_PAGEDOWN:
		m_z+=0.02f;
		break;
	case SDLK_UP:
		m_xspeed-=0.01f;
		break;
	case SDLK_DOWN:
		m_xspeed+=0.01f;
		break;
	case SDLK_RIGHT:
		m_yspeed+=0.01f;
		break;
	case SDLK_LEFT:
		m_yspeed-=0.01f;
		break;
	default:
		return false;
		break;
	}

	return true;
}
