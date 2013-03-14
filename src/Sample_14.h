/*
 * Sample_14.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_14_H_
#define Sample_14_H_

#include "Sample.h"

class Sample_14 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480,
		LIST_SZ = 96,
		FIRST_SYMBOL = 32
	};
public:
	Sample_14();
	virtual ~Sample_14();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"14. Outline Fonts (Only Linux) !!! It's not finished";
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
	GLfloat m_rot;  // Used To Rotate The Text

	void buildFont();
	void glPrint( const char *fmt, ... );
};

#endif /* Sample_14_H_ */
