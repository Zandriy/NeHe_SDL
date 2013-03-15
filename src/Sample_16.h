/*
 * Sample_16.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_16_H_
#define Sample_16_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_16 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};

	enum texFilters {
		NEAREST_FILTER,
		LINEAR_FILTER,
		MIPMAPPED_FILTER,
		TEX_QTY
	};
public:
	Sample_16();
	virtual ~Sample_16();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "16. Cool Looking Fog (f,l,g,PgUP,PgDOWN,arrows)";
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
	virtual void draw();
	virtual void initGL();
	virtual void restoreGL();

private:
	bool	m_light;			// Lighting ON / OFF

	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLfloat		m_xspeed;		// X Rotation Speed
	GLfloat		m_yspeed;		// Y Rotation Speed
	GLfloat		m_z;			// Depth Into The Screen
	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	GLuint		m_filter;			// Which Filter To Use
	OGLImageRec	m_image;

	static GLuint m_fogMode[3];   // Storage For Three Types Of Fog
	GLuint m_fogfilter;    // Which Fog To Use
	static GLfloat m_fogColor[4];    // Fog Color
};

#endif /* Sample_16_H_ */
