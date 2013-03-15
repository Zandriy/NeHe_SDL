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
		TEX_QTY
	};

	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLfloat		m_zrot;			// Z Rotation
	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	OGLImageRec	m_image;
};

#endif /* Sample_22_H_ */
