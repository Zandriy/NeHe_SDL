/*
 * Sample_13.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_13_H_
#define Sample_13_H_

#include "Sample.h"

class Sample_13 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480,
		LIST_SZ = 96,
		FIRST_SYMBOL = 32
	};
public:
	Sample_13();
	virtual ~Sample_13();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "13. Bitmap Fonts (Only Linux)";
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

	void buildFont();
	void glPrint( const char *fmt, ... );
};

#endif /* Sample_13_H_ */
