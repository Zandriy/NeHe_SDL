/*
 * Sample_06.h
 *
 *  Created on: Feb 23, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_06_H_
#define Sample_06_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_06 : public Sample
{
public:
	Sample_06();
	virtual ~Sample_06();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"06. Texture Mapping";
	}
	virtual int width() const
	{
		return 640;
	}
	virtual int height() const
	{
		return 480;
	}

protected:
	void draw();
	void initGL();
	void restoreGL();

private:
	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLfloat		m_zrot;			// Z Rotation
	GLuint		m_texture[1];	// Storage For One Texture
	OGLImageRec	m_image;
};

#endif /* Sample_06_H_ */
