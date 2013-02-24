/*
 * Sample_10.h
 *
 *  Created on: Feb 24, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_10_H_
#define Sample_10_H_

#include "Sample.h"
#include "OGLImageRec.h"

class SDL_Surface;

class Sample_10 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};

	enum {
		NEAREST_FILTER,
		LINEAR_FILTER,
		MIPMAPPED_FILTER,
		TEX_QTY
	};

	typedef struct tagVERTEX
	{
		float x, y, z;
		float u, v;
	} VERTEX;

	typedef struct tagTRIANGLE
	{
		VERTEX vertex[3];
	} TRIANGLE;

	typedef struct tagSECTOR
	{
		int numtriangles;
		TRIANGLE* triangle;
	} SECTOR;

public:
	Sample_10();
	virtual ~Sample_10();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"10. Loading And Moving Through A 3D World (b,f,s,PgUP,PgDOWN,arrows)";
	}
	virtual int width() const
	{
		return INIT_W;
	}
	virtual int height() const
	{
		return INIT_H;
	}

	virtual bool sendMessage(int message, int mode, int x, int y);

protected:
	void draw();
	void initGL();
	void restoreGL();

private:
	void readStr(FILE *f,char *string);
	void setupWorld();

	const float m_piover180;

	bool	m_blend;				// Blending ON/OFF

	float	m_heading;
	float	m_xpos;
	float	m_zpos;

	GLfloat	m_yrot;				// Y Rotation
	GLfloat	m_walkbias;
	GLfloat	m_walkbiasangle;
	GLfloat	m_lookupdown;
	GLfloat	m_z;				// Depth Into The Screen

	GLuint	m_filter;				// Which Filter To Use
	GLuint	m_texture[TEX_QTY];			// Storage For 3 Textures
	SDL_Surface *m_imageSDL;
	OGLImageRec	m_image;
	bool	m_useSDLImage;

	SECTOR m_sector;
};

#endif /* Sample_10_H_ */
