/*
 * Sample_24.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_24_H_
#define Sample_24_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_24 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480,
		LIST_SZ = 256,
		FIRST_SYMBOL = 32
	};

	enum textures {
		TEX_1,
		TEX_QTY
	};
public:
	Sample_24();
	virtual ~Sample_24();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "24. Tokens, Extensions, Scissor Testing And TGA Loading";
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
	GLuint  m_base; // Base Display List For The Font Set
	GLuint	m_texture[TEX_QTY];                         // Font Texture Storage Space
	OGLImageRec	m_imageFont;
	int	m_sWidth;
	int	m_sHeight;
	int m_scroll;
	int	m_maxtokens;

	void buildFont();
	void glPrint( GLint x, GLint y, int set, const char *fmt, ... );
	bool loadTexture();
};

#endif /* Sample_24_H_ */
