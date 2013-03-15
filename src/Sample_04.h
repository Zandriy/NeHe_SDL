/*
 * Sample_04.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_04_H_
#define Sample_04_H_

#include "Sample.h"

class Sample_04 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_04();
	virtual ~Sample_04();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "04. Rotation";
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
	GLfloat     m_rtri;                       // Angle For The Triangle
	GLfloat     m_rquad;                      // Angle For The Quad
};

#endif /* Sample_04_H_ */
