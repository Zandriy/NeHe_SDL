/*
 * Sample_07.h
 *
 *  Created on: Feb 23, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_07_H_
#define Sample_07_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_07 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_07();
	virtual ~Sample_07();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"07. Texture Filters, Lighting & Keyboard Control (f,l,PgUP,PgDOWN,arrows)";
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
	enum texFilters {
		NEAREST_FILTER,
		LINEAR_FILTER,
		MIPMAPPED_FILTER,
		TEX_QTY
	};

	bool	m_light;			// Lighting ON / OFF

	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLfloat		m_xspeed;		// X Rotation Speed
	GLfloat		m_yspeed;		// Y Rotation Speed
	GLfloat		m_z;			// Depth Into The Screen
	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	GLuint		m_filter;			// Which Filter To Use
	OGLImageRec	m_image;
};

#endif /* Sample_07_H_ */
