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
public:
	Sample_05();
	virtual ~Sample_05();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"05. 3D Shapes";
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
	GLfloat     m_rtri;                       // Angle For The Pyramid
	GLfloat     m_rquad;                      // Angle For The Cube
};

#endif /* Sample_05_H_ */