/*
 * Sample_20.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_20_H_
#define Sample_20_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_20 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};

	enum texNumbers {
		TEX_LOGO,
		TEX_IMG1,
		TEX_MASK1,
		TEX_IMG2,
		TEX_MASK2,
		TEX_QTY
	};

public:
	Sample_20();
	virtual ~Sample_20();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"20. Masking ( m,Space )";
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
	bool    m_masking;                               // Masking On/Off
	bool    m_scene;                                  // Which Scene To Draw
	GLuint	m_texture[TEX_QTY];						// Storage For Five Textures
	GLfloat m_roll;                                   // Rolling Texture
	OGLImageRec	m_image[TEX_QTY];
};

#endif /* Sample_20_H_ */
