/*
 * Sample_05.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_05_H_
#define Sample_05_H_

#include "Sample.h"

class Sample_05 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_05();
	virtual ~Sample_05();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "05. 3D Shapes";
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
	GLfloat     m_rtri;                       // Angle For The Pyramid
	GLfloat     m_rquad;                      // Angle For The Cube
};

#endif /* Sample_05_H_ */
