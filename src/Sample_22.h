/*
 * Sample_22.h
 *
 *  Created on: Mar 16, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_22_H_
#define Sample_22_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_22 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_22();
	virtual ~Sample_22();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "22. Bump-Mapping, Multi-Texturing & Extensions";
	}
	virtual int width() const
	{
		return INIT_W;
	}
	virtual int height() const
	{
		return INIT_H;
	}

protected:
	virtual void draw();
	virtual void initGL();
	virtual void restoreGL();

private:
	enum texFilters {
		TEX_1,
		TEX_2,
		TEX_3,
		TEX_QTY
	};

	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLfloat		m_zrot;			// Z Rotation
	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	OGLImageRec	m_image;

	bool		m_multitextureSupported;	// Flag Indicating Whether Multitexturing Is Supported
	bool		m_useMultitexture;			// Use It If It Is Supported?
	GLint		m_maxTexelUnits;			// Number Of Texel-Pipelines. This Is At Least 1.

	GLuint  m_filter;						// Which Filter To Use
	GLuint  m_bump[TEX_QTY];				// Our Bumpmappings
	GLuint  m_invbump[TEX_QTY];				// Inverted Bumpmaps
	GLuint  m_glLogo;						// Handle For OpenGL-Logo
	GLuint  m_multiLogo;					// Handle For Multitexture-Enabled-Logo
	static	GLfloat s_LightAmbient[];				// Ambient Light Is 20% White
	static	GLfloat s_LightDiffuse[];				// Diffuse Light Is White
	static	GLfloat s_LightPosition[];				// Position Is Somewhat In Front Of Screen
	static	GLfloat s_Gray[];
	static	GLfloat s_data[];

	void	initLights();
	int		loadGLTextures();
};

#endif /* Sample_22_H_ */
