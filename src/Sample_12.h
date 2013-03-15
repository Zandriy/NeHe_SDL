/*
 * Sample_12.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_12_H_
#define Sample_12_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_12 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_12();
	virtual ~Sample_12();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "12. Display Lists";
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
		TEX_QTY
	};

	enum theConsts {
		COORD_QTY = 3,
		COL_QTY = 5
	};

	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	OGLImageRec	m_image;

	GLuint	m_box;					// Storage For The Box Display List
	GLuint	m_top;					// Storage For The Top Display List
	GLuint	m_xloop;				// Loop For X Axis
	GLuint	m_yloop;				// Loop For Y Axis

	static GLfloat m_boxcol[COL_QTY][COORD_QTY];
	static GLfloat m_topcol[COL_QTY][COORD_QTY];

	GLvoid BuildLists();
};

#endif /* Sample_12_H_ */
