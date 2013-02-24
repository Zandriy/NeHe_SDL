/*
 * Sample_08.h
 *
 *  Created on: Feb 23, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_08_H_
#define Sample_08_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_08 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_08();
	virtual ~Sample_08();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"08. Blending (b,f,l,PgUP,PgDOWN,arrows)";
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
	enum {
		NEAREST_FILTER,
		LINEAR_FILTER,
		MIPMAPPED_FILTER,
		TEX_QTY
	};

	bool	m_light;			// Lighting ON / OFF
	bool	m_blend;			// Blending ON / OFF

	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLfloat		m_xspeed;		// X Rotation Speed
	GLfloat		m_yspeed;		// Y Rotation Speed
	GLfloat		m_z;			// Depth Into The Screen
	GLuint		m_texture[TEX_QTY];	// Storage For Three Textures
	GLuint		m_filter;		// Which Filter To Use
	OGLImageRec	m_image;
};

#endif /* Sample_08_H_ */
