/*
 * Sample_17.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_17_H_
#define Sample_17_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_17 : public Sample
{
	enum theConsts {
		INIT_W = 640,
		INIT_H = 480,
		LIST_SZ = 256,
		FIRST_SYMBOL = 31
	};

	enum textures {
		TEX_1,
		TEX_2,
		TEX_QTY
	};
public:
	Sample_17();
	virtual ~Sample_17();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "17. 2D Texture Font";
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
	GLuint  m_base; // Base Display List For The Font Set
	GLfloat m_cnt1; // 1st Counter Used To Move Text & For Coloring
	GLfloat m_cnt2; // 2nd Counter Used To Move Text & For Coloring
	OGLImageRec	m_imageFont;
	OGLImageRec	m_imagePict;

	GLuint  m_texture[TEX_QTY];                             // Storage For Our Font Texture

	void buildFont();
	void glPrint( GLint x, GLint y, char *string, int set );
};

#endif /* Sample_17_H_ */
